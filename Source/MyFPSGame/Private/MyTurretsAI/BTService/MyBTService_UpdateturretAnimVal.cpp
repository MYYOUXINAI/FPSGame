// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTurretsAI/BTService/MyBTService_UpdateturretAnimVal.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "MyAnim/MyTurretsBaseAnimInstance.h"

void UMyBTService_UpdateturretAnimVal::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                                float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIC = OwnerComp.GetAIOwner();
	if(ensure(AIC))
	{
		AActor* TargetActor = Cast<AActor>(AIC->GetBlackboardComponent()->GetValueAsObject(TargetActorKey.SelectedKeyName));
		bool bEnterAttackState = TargetActor == nullptr ? false : true;

		ACharacter* Character = Cast<ACharacter>(AIC->GetPawn());
		if(ensure(Character))
		{
			UMyTurretsBaseAnimInstance* MyAnimInstance = Cast<UMyTurretsBaseAnimInstance>(Character->GetMesh()->GetAnimInstance());

			if(ensure(MyAnimInstance))
			{
				MyAnimInstance->EnterAttackState(bEnterAttackState);
			}
		}
	}
}
