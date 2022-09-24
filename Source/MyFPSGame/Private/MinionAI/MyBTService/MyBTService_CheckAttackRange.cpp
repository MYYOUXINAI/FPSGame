// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionAI/MyBTService/MyBTService_CheckAttackRange.h"

UMyBTService_CheckAttackRange::UMyBTService_CheckAttackRange()
{
	MaxAttackRange = 50.0f;
}

void UMyBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

}

