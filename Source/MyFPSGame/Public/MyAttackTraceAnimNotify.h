// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MyAttackTraceAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class MYFPSGAME_API UMyAttackTraceAnimNotify : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	/* Attribute and Data */

	UPROPERTY(EditDefaultsOnly, Category = "AttackTrace")
		TArray<FHitResult>HitResults;

	UPROPERTY(EditDefaultsOnly, Category = "AttackTrace")
		TArray<AActor*>HitActors;

	UPROPERTY(EditDefaultsOnly, Category = "AttackTrace")
		TArray<FVector>LastLocations;

	UPROPERTY(EditDefaultsOnly, Category = "AttackTrace")
		TArray<FName>SocketNames;

	UPROPERTY(EditDefaultsOnly, Category = "AttackTrace")
		TArray<AActor*>ActorsToIgnore;

	UPROPERTY(EditDefaultsOnly, Category = "AttackTrace")
		TEnumAsByte<ETraceTypeQuery>TraceType;

	UPROPERTY(EditDefaultsOnly, Category = "AttackTrace")
		AActor* Player;

	UPROPERTY(EditDefaultsOnly, Category = "AttackTrace")
		float DamageValue;



	/* override function */

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;;

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;;


	UMyAttackTraceAnimNotify();
};
