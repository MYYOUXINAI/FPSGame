// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionAI/MyBTTaskNode/MyBTTask_RangedAttack.h"
#include "AIController.h"
#include "MyActionComponent.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type UMyBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIC = OwnerComp.GetAIOwner();
	ACharacter* OwnerCharacter = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if(OwnerCharacter)
	{
		const bool bFlag = UMyActionComponent::GetActionComponent(OwnerCharacter)->StartActionByName(OwnerCharacter, ActionName);
		if(bFlag)
		{
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}


