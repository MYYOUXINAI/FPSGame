// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAttributeComponent.h"

#include "MyGameModeBase.h"
#include "MyUserWidget.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values for this component's properties
UMyAttributeComponent::UMyAttributeComponent()
{
	SprintDeltaSpeed = 600.f;

	MaxHealth = 200.f;
	CurrentHealth = MaxHealth;

	MaxMagicPoint = 200.f;
	CurrentMagicPoint = MaxMagicPoint;

	bIsHit = false;
	HitAngle = 0.0f;
	HitDelay = 0.85;
}

UMyAttributeComponent* UMyAttributeComponent::GetAttributes(AActor* InstigatorActor)
{
	if(ensure(InstigatorActor))
	{
		UMyAttributeComponent* AttributeComp = Cast<UMyAttributeComponent>(InstigatorActor->GetComponentByClass(UMyAttributeComponent::StaticClass()));
		if(AttributeComp)
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
		UMyUserWidget* DamagePopUI = CreateWidget<UMyUserWidget>(GetWorld(), DamagePopUIClass);
		if(DamagePopUI)
		{
			DamagePopUI->AttachedActor = GetOwner();
			DamagePopUI->AddToViewport();
		}

		OnHealthChanged.Broadcast(InstigatorActor, this, NewHealthValue, ActualDelta);
	}

	//die
	if (ActualDelta < 0.0f && CurrentHealth == 0.0f)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Has Died!"), true);
		
		AMyGameModeBase* GM = GetWorld()->GetAuthGameMode<AMyGameModeBase>();
		if(GM)
		{
			GM->OnActorKilled(this->GetOwner(), InstigatorActor);
		}
	}


	return ActualDelta != 0;
}


void UMyAttributeComponent::MyHitReact(const FVector HitLocation)
{
	const ACharacter* MyCharacter = Cast<ACharacter>(GetOwner());
	if(ensure(MyCharacter))
	{
		MyCharacter->GetCharacterMovement()->StopMovementImmediately();
		bIsHit = true;
		FTimerHandle TimerHandleDelay;
		GetWorld()->GetTimerManager().SetTimer(TimerHandleDelay, this, &UMyAttributeComponent::MyRecoveryFromHit, HitDelay);

		/* Get HitAngle */
		{
			FVector ActorLocation = FVector(MyCharacter->GetActorLocation().X, MyCharacter->GetActorLocation().Y, HitLocation.Z);
			FRotator rotator = UKismetMathLibrary::FindLookAtRotation(ActorLocation, HitLocation);
			float temp;
			UKismetMathLibrary::BreakRotator(rotator, temp, temp, HitAngle);
		}
	}
}

bool UMyAttributeComponent::IsAlive() const
{
	return this->CurrentHealth > 0.0f;
}

void UMyAttributeComponent::MyRecoveryFromHit()
{
	bIsHit = false;
}
