// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyBTTask_UpdateTargetLocation.generated.h"

/**
 * 
 */
UCLASS()
class MYFPSGAME_API UMyBTTask_UpdateTargetLocation : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "TargetLocationArray")/* change it when improve the program struct */
		TArray<FVector> TargetLocations;

	UPROPERTY(EditAnywhere, Category = "CurrentLocationIndex")
		FBlackboardKeySelector LocationIndexKey;

	UPROPERTY(EditAnywhere, Category = "CurrentTargetLocation")
		FBlackboardKeySelector CurrentTargetLocationKey;

	UPROPERTY(EditAnywhere, Category = "bHasArrivedEndLocation")
		FBlackboardKeySelector bNotHasArrivedEndLocationKey;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
};
