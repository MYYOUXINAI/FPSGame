// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActions/MyAction.h"
#include "MyActionComponent.h"
#include "Net/UnrealNetwork.h"

UMyActionComponent* UMyAction::GetOwningComponent() const
{
	return ActionComp;
}


void UMyAction::Initialize(UMyActionComponent* NewActionComp)
{
	ActionComp = NewActionComp;
}

bool UMyAction::IsRunning() const
{
	return RepData.bIsRunning;
}

bool UMyAction::CanStart_Implementation(AActor* InstigatorActor)
{
	if(IsRunning())
	{
		return false;
	}

	const UMyActionComponent* Comp = GetOwningComponent();

	if(Comp->ActiveGameplayTags.HasAny(BlockedTags))
	{
		return false;
	}

	return true;
}

void UMyAction::StartAction_Implementation(AActor* InstigatorActor)
{
	UMyActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.AppendTags(GrantsTags);

	RepData.bIsRunning = true;
	RepData.InstigatorActor = InstigatorActor;

	if(GetOwningComponent()->GetOwnerRole()==ROLE_Authority)
	{
		TimeStarted = GetWorld()->TimeSeconds;
	}
	GetOwningComponent()->OnActionStarted.Broadcast(GetOwningComponent(), this);
}

void UMyAction::StopAction_Implementation(AActor* InstigatorActor)
{
	UMyActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.RemoveTags(GrantsTags);

	RepData.bIsRunning = false;
	RepData.InstigatorActor = InstigatorActor;

	GetOwningComponent()->OnActionStopped.Broadcast(GetOwningComponent(), this);
}

UWorld* UMyAction::GetWorld() const
{
	const AActor* Actor = Cast<AActor>(GetOuter());
	if(ensure(Actor))
	{
		return Actor->GetWorld();
	}

	return nullptr;
}

bool UMyAction::IsSupportedForNetworking() const
{
	return true;
}


void UMyAction::OnRep_RepData()
{
	if(RepData.bIsRunning)
	{
		StartAction(RepData.InstigatorActor);
	}
	else
	{
		StopAction(RepData.InstigatorActor);
	}
}

void UMyAction::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMyAction, RepData);
	DOREPLIFETIME(UMyAction, TimeStarted);
	DOREPLIFETIME(UMyAction, ActionComp);
}