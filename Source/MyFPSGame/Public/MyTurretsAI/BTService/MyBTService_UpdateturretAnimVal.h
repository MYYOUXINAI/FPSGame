// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MyBTService_UpdateturretAnimVal.generated.h"

/**
 * 
 */
UCLASS()
class MYFPSGAME_API UMyBTService_UpdateturretAnimVal : public UBTService
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "AI")
		FBlackboardKeySelector TargetActorKey;


public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
