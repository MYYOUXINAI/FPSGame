// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MyBTServic_CheckTargetActorRange.generated.h"

/**
 * 
 */
UCLASS()
class MYFPSGAME_API UMyBTServic_CheckTargetActorRange : public UBTService
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditAnywhere, Category = "TargetActor")
		FBlackboardKeySelector TargetActorKey;

	UPROPERTY(EditAnywhere, Category = "MaxRange")
		float MaxRange;

	UPROPERTY(EditAnywhere, Category = "TargetActorRange")
		FBlackboardKeySelector TargetActorRangeKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	UMyBTServic_CheckTargetActorRange();
};
