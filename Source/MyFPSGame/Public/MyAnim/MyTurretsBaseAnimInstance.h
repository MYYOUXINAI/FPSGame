// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyTurretsBaseAnimInstance.generated.h"

class AMyTurretBase;
/**
 * 
 */
UCLASS()
class MYFPSGAME_API UMyTurretsBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
		
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MyAnimation")
		bool bIsAttackState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyAnimation")
		float Yaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyAnimation")
		FVector LookAtLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyAnimation")
		bool OpenPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyAnimation")
		float DistanceToTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyAnimation")
		int Tower_Variation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyAnimation")
		bool Aiming;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyAnimation")
		bool OpenShield;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyAnimation")
		bool IsHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyAnimation")
		int HitVariation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyAnimation")
		float TurretDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyAnimation")
		bool isFiring;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyAnimation")
		AMyTurretBase* OwningActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyAnimation")
		float RotateDelta;


public:

	virtual void NativeInitializeAnimation() override;

	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void FocusToTargetActorSmooth(float Delta, float NewYaw);

	void EnterAttackState(bool bHasTargetActor);

	void Fire(bool bEnterFireState);
	
};
