// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyTask_SpawnProjectileAttack.generated.h"

/**
 * 
 */
UCLASS()
class MYFPSGAME_API UMyTask_SpawnProjectileAttack : public UBTTaskNode
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "AI")
		FBlackboardKeySelector TargetActorKey;

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};
