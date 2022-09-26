// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionAI/MyBTService/MyBTService_CheckAttackRange.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"

UMyBTService_CheckAttackRange::UMyBTService_CheckAttackRange()
{
	MaxAttackRange = 50.0f;
}

void UMyBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if(ensure(BlackboardComp))
	{
		AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TargetActorKey.SelectedKeyName));
		if(TargetActor)
		{
			AAIController* AIC = OwnerComp.GetAIOwner();
			if(AIC)
			{
				AActor* OwnerActor = AIC->GetPawn();
				if(OwnerActor)
				{
					float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(), OwnerActor->GetActorLocation());
					bool bWithinRange = DistanceTo < MaxAttackRange;
					bool bHasLOS = false;
					if(bWithinRange)
					{
						bHasLOS = AIC->LineOfSightTo(TargetActor);
					}
					if(bWithinRange && bHasLOS)	BlackboardComp->SetValueAsInt(AttackRangeKey.SelectedKeyName, 1);
					else
					{
						BlackboardComp->SetValueAsInt(AttackRangeKey.SelectedKeyName, -1);
					}
				}
			}
		}
	}
}

