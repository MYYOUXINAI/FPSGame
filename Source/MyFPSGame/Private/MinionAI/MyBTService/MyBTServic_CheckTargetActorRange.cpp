// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionAI/MyBTService/MyBTServic_CheckTargetActorRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UMyBTServic_CheckTargetActorRange::UMyBTServic_CheckTargetActorRange()
{
	MaxRange = 1000.f;
}

void UMyBTServic_CheckTargetActorRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIC = OwnerComp.GetAIOwner();
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	if(ensure(AIC)&&ensure(BlackboardComp))
	{
		AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TargetActorKey.SelectedKeyName));
		if(TargetActor!=nullptr)/* fix it latter */
		{
			AActor* OwnerActor = AIC->GetPawn();
			if(ensure(OwnerActor))
			{
				float distance = FVector::Distance(TargetActor->GetActorLocation(), OwnerActor->GetActorLocation());
				if(distance>MaxRange)
				{
					BlackboardComp->SetValueAsObject(TargetActorRangeKey.SelectedKeyName, nullptr);
					return;
				}
				else
				{
					return;
				}
			}
		}
	}
	BlackboardComp->SetValueAsObject(TargetActorRangeKey.SelectedKeyName, nullptr);
}


