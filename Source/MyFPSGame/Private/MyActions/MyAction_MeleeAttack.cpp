// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActions/MyAction_MeleeAttack.h"
#include "GameFramework/Character.h"

UMyAction_MeleeAttack::UMyAction_MeleeAttack()
{
	AttackInterval = 1.0f;
}

void UMyAction_MeleeAttack::StartAction_Implementation(AActor* InstigatorActor)
{
	Super::StartAction_Implementation(InstigatorActor);

	ACharacter* Character = Cast<ACharacter>(InstigatorActor);

	if(ensure(Character))
	{
		Character->PlayAnimMontage(AttackAnim);

		FTimerHandle TimerHandle_AttackIntervalDelay;
		FTimerDelegate AttackInterval_Delegate;
		AttackInterval_Delegate.BindUFunction(this, "AttackInterval_Elapsed", Character);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackIntervalDelay, AttackInterval_Delegate, AttackInterval, false);
	}
}


inline void UMyAction_MeleeAttack::AttackInterval_Elapsed(ACharacter* InstigatorActor)
{
	StopAction(InstigatorActor);
}