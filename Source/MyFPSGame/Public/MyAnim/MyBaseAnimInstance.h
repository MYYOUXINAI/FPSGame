// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyBaseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYFPSGAME_API UMyBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
		bool IsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
		float Pitch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
		float Roll;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
		float Yaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
		FRotator RotationLastTick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
		float YawDelta;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
		bool IsAccelerating;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
		UObject* Character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
		bool isAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
		int CurrentAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
		bool FullBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
		float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
		bool bIsHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
		float HitAngle;
	
};
