// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MyBTService_CheckAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class MYFPSGAME_API UMyBTService_CheckAttackRange : public UBTService
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "AI")
		FBlackboardKeySelector AttackRangeKey;

	UPROPERTY(EditAnywhere, Category = "AI")
		float MaxAttackRange;


	UPROPERTY(EditAnywhere, Category = "AI")
		FBlackboardKeySelector TargetActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


public:

	UMyBTService_CheckAttackRange();
};
