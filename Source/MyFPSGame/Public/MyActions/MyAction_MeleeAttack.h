// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyActions/MyAction.h"
#include "MyAction_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class MYFPSGAME_API UMyAction_MeleeAttack : public UMyAction
{
	GENERATED_BODY()

public:

	UMyAction_MeleeAttack();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Attack")
		UAnimMontage* AttackAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
		float AttackInterval;

	UFUNCTION()
		void AttackInterval_Elapsed(ACharacter* InstigatorActor);

public:

	virtual void StartAction_Implementation(AActor* InstigatorActor) override;


};

