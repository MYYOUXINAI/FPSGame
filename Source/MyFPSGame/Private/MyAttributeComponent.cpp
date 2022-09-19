// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAttributeComponent.h"

// Sets default values for this component's properties
UMyAttributeComponent::UMyAttributeComponent()
{
	SprintDeltaSpeed = 600.f;

	MaxHealth = 200.f;
	CurrentHealth = MaxHealth;

	MaxMagicPoint = 200.f;
	CurrentMagicPoint = MaxMagicPoint;
}

UMyAttributeComponent* UMyAttributeComponent::GetAttributes(AActor* InstigatorActor)
{
	if(ensure(InstigatorActor))
	{
		UMyAttributeComponent* AttributeComp = Cast<UMyAttributeComponent>(InstigatorActor->GetComponentByClass(UMyAttributeComponent::StaticClass()));
		if(ensure(AttributeComp))
		{
			return AttributeComp;
		}
	}
	return nullptr;
}

bool UMyAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float DamageValue)
{
	if (!GetOwner()->CanBeDamaged() && DamageValue < 0.0f)	return false;

	
	float OldHealthValue = this->CurrentHealth;
	float NewHealthValue = FMath::Clamp(CurrentHealth + DamageValue, 0.0f, MaxHealth);

	float ActualDelta = NewHealthValue - OldHealthValue;

	this->CurrentHealth = NewHealthValue;
	if(ActualDelta!=0.0f)
	{
		OnHealthChanged.Broadcast(InstigatorActor, this, NewHealthValue, ActualDelta);
	}

	//die
	if(ActualDelta<0.0f && CurrentHealth==0.0f)
	{

		//add event call in there
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Has Died!"), true);
	}


	return ActualDelta != 0;
}


