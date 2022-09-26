// Fill out your copyright notice in the Description page of Project Settings.


#include "MinionAI/MyBaseMinionController.h"
#include "BehaviorTree/BlackboardComponent.h"


void AMyBaseMinionController::BeginPlay()
{
	Super::BeginPlay();

	if(ensureMsgf(BehaviorTree,TEXT("Behavior Tree is nullptr! Please assign BehaviorTree in your AI Controller!" )))
	{
		RunBehaviorTree(BehaviorTree);
		UBlackboardComponent* BlackboardComp = this->GetBlackboardComponent();
		if(ensure(BlackboardComp))
		{
			BlackboardComp->SetValueAsBool(bNotHasArrivedEndLocationName, true);
			BlackboardComp->SetValueAsInt(LocationIndexName, -1);
		}
	}
}


