// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionAI/MyBTTaskNode/MyBTTask_RangedAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type UMyBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIC = OwnerComp.GetAIOwner();
	ACharacter* OwnerCharacter = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if(OwnerCharacter)
	{
		if(ensureMsgf(PrimaryAttackMontage,TEXT("The Minion Range Attack AI ,havn't assign attack animMontage !!!")))
		{
			OwnerCharacter->PlayAnimMontage(PrimaryAttackMontage);
			return EBTNodeResult::Succeeded;
		}
		else
		{
			return EBTNodeResult::Failed;
		}
	}
	else
	{
		return EBTNodeResult::Failed;
	}

}


