// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionAI/MyBTTaskNode/MyBTTask_UpdateTargetLocation.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UMyBTTask_UpdateTargetLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	AAIController* AIC = OwnerComp.GetAIOwner();

	if (ensure(BlackboardComp) && ensure(AIC))
	{
		int OldIndex = BlackboardComp->GetValueAsInt(LocationIndexKey.SelectedKeyName);
		int NewIndex = OldIndex + 1;
		BlackboardComp->SetValueAsInt(LocationIndexKey.SelectedKeyName, NewIndex);
		if (NewIndex >= TargetLocations.Num())
		{
			BlackboardComp->SetValueAsInt(bNotHasArrivedEndLocationKey.SelectedKeyName, -1);
			return EBTNodeResult::Failed;
		}
		else
		{
			BlackboardComp->SetValueAsInt(bNotHasArrivedEndLocationKey.SelectedKeyName, 1);
			BlackboardComp->SetValueAsVector(CurrentTargetLocationKey.SelectedKeyName, TargetLocations[NewIndex]);
			return EBTNodeResult::Succeeded;
		}

	}

	return EBTNodeResult::Failed;
}

