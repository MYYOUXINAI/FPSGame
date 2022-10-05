// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyActions/MyAction.h"
#include "MyAction_TurretProjectileAttack.generated.h"

/**
 * 
 */
UCLASS()
class MYFPSGAME_API UMyAction_TurretProjectileAttack : public UMyAction
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Attack")
		TSubclassOf<AActor>ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
		FName HandSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		UParticleSystem* CastingEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
		float AttackAnimDelay;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
		float AttackInterval;

	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
		AActor* TargetActor;


	UFUNCTION()
		void AttackDelay_Elapsed(ACharacter* InstigatorActor);

	UFUNCTION()
		void AttackInterval_Elapsed(ACharacter* InstigatorActor);

public:
	virtual void StartAction_Implementation(AActor* InstigatorActor) override;

	UFUNCTION(BlueprintCallable)
		void SetTargetActor(AActor* _TargetActor);

	UMyAction_TurretProjectileAttack();
};
