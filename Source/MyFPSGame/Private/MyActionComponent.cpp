// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActionComponent.h"

#include "Engine/ActorChannel.h"
#include "MyActions/MyAction.h"
#include "Net/UnrealNetwork.h"



UMyActionComponent::UMyActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);
}

void UMyActionComponent::AddAction(AActor* InstigatorActor, TSubclassOf<UMyAction> ActionClass)
{
	if(!ensure(ActionClass))
	{
		return;
	}

	if(!GetOwner()->HasAuthority())
	{
		return;
	}

	UMyAction* NewAction = NewObject<UMyAction>(GetOwner(), ActionClass);

	if(ensure(NewAction))
	{
		NewAction->Initialize(this);
		Actions.Add(NewAction);

		if(NewAction->bAutoStart && ensure(NewAction->CanStart(InstigatorActor)))
		{
			NewAction->StartAction(InstigatorActor);
		}
	}

}

void UMyActionComponent::RemoveAction(UMyAction* ActionToRemove)
{
	if(!ensure(ActionToRemove) && !ActionToRemove->IsRunning())
	{
		return;
	}

	Actions.Remove(ActionToRemove);
}

UMyAction* UMyActionComponent::GetAction(TSubclassOf<UMyAction> ActionClass) const
{
	for(UMyAction* Action:Actions)
	{
		if(Action && Action->IsA(ActionClass))
		{
			return Action;
		}
	}
	return nullptr;
}

UMyAction* UMyActionComponent::GetActionByName(FName ActionName) const
{
	for(UMyAction* Action:Actions)
	{
		if(Action && Action->ActionName==ActionName)
		{
			return Action;
		}
	}

	return nullptr;
}

bool UMyActionComponent::StartActionByName(AActor* InstigatorActor, FName ActionName)
{
	for(UMyAction* Action:Actions)
	{
		if(Action && Action->ActionName==ActionName)
		{
			if(!Action->CanStart(InstigatorActor))
			{
				/*FString FailedMsg = FString::Printf(TEXT("Failed to run : %s"), *ActionName.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FailedMsg);*/
				continue;
			}

			if(!GetOwner()->HasAuthority())
			{
				ServerStartAction(InstigatorActor, ActionName);
			}

			Action->StartAction(InstigatorActor);
			return true;
		}
	}
	return false;
}

bool UMyActionComponent::StopActionByName(AActor* InstigatorActor, FName ActionName)
{
	for(UMyAction* Action:Actions)
	{
		if(Action && Action->ActionName==ActionName)
		{
			if(Action->IsRunning())
			{
				if(!GetOwner()->HasAuthority())
				{
					ServerStopAction(InstigatorActor, ActionName);
				}
				Action->StopAction(InstigatorActor);
				return true;
			}
		}
	}

	return false;
}

void UMyActionComponent::BeginPlay()
{
	Super::BeginPlay();

	if(GetOwner()->HasAuthority())
	{
		for(const TSubclassOf<UMyAction> ActionClass:DefaultsActions)
		{
			AddAction(GetOwner(), ActionClass);
		}
	}
}

void UMyActionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	TArray<UMyAction*>ActionsCopy = Actions;
	for(UMyAction* Action:ActionsCopy)
	{
		if(Action && Action->IsRunning())
		{
			Action->StopAction(GetOwner());
		}
	}

	Super::EndPlay(EndPlayReason);
}

UMyActionComponent* UMyActionComponent::GetActionComponent(AActor* InstigatorActor)
{
	if(ensure(InstigatorActor))
	{
		UMyActionComponent* ActionComponent = Cast<UMyActionComponent>(InstigatorActor->GetComponentByClass(UMyActionComponent::StaticClass()));
		if(ActionComponent)
		{
			return ActionComponent;
		}
	}
	return nullptr;
}

bool UMyActionComponent::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);
	for(UMyAction* Action:Actions)
	{
		if(Action)
		{
			WroteSomething |= Channel->ReplicateSubobject(Action, *Bunch, *RepFlags);
		}
	}

	return WroteSomething;
}

void UMyActionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UMyActionComponent::ServerStopAction_Implementation(AActor* InstigatorActor, FName ActionName)
{
	StartActionByName(InstigatorActor, ActionName);
}

void UMyActionComponent::ServerStartAction_Implementation(AActor* InstigatorActor, FName ActionName)
{
	StopActionByName(InstigatorActor, ActionName);
}

void UMyActionComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMyActionComponent, Actions);
}