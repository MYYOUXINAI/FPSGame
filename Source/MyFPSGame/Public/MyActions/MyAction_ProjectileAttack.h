// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyActions/MyAction.h"
#include "MyAction_ProjectileAttack.generated.h"

/**
 * 
 */
UCLASS()
class MYFPSGAME_API UMyAction_ProjectileAttack : public UMyAction
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Targeting")
		float SweepRadius;

	UPROPERTY(EditAnywhere, Category = "Targeting")
		float SweepDistanceFallback;

	UPROPERTY(EditAnywhere, Category = "Attack")
		TSubclassOf<AActor>ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
		FName HandSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
		float AttackAnimDelay;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
		float AttackInterval;

	UPROPERTY(EditAnywhere, Category = "Attack")
		UAnimMontage* AttackAnim;


	UFUNCTION()
		void AttackDelay_Elapsed(ACharacter* InstigatorActor);

	UFUNCTION()
		void AttackInterval_Elapsed(ACharacter* InstigatorActor);

public:
	virtual void StartAction_Implementation(AActor* InstigatorActor) override;

	UMyAction_ProjectileAttack();

};
