// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTurretsAI/BTTask/MyTask_SpawnProjectileAttack.h"

#include "AIController.h"
#include "MyActionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "MyActions/MyAction.h"
#include "MyActions/MyAction_TurretProjectileAttack.h"


class UMyActionComponent;

EBTNodeResult::Type UMyTask_SpawnProjectileAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIC = OwnerComp.GetAIOwner();
	if (ensure(AIC))
	{
		ACharacter* OwningCharacter = Cast<ACharacter>(AIC->GetPawn());
		if (ensure(OwningCharacter))
		{
			AActor* TargetActor = Cast<AActor>(AIC->GetBlackboardComponent()->GetValueAsObject(TargetActorKey.SelectedKeyName));
			if(ensure(TargetActor))
			{
				UMyAction_TurretProjectileAttack* _Action = Cast<UMyAction_TurretProjectileAttack>(UMyActionComponent::GetActionComponent(OwningCharacter)->GetActionByName("MyTurretsPrimaryAttack"));
				if(ensure(_Action))
				{
					_Action->SetTargetActor(TargetActor);
					const bool bFlag = UMyActionComponent::GetActionComponent(OwningCharacter)->StartActionByName(OwningCharacter, "MyTurretsPrimaryAttack");
					if(bFlag)
					{
						return EBTNodeResult::Succeeded;
					}
				}
			}
		}
	}

	return EBTNodeResult::Failed;
}
