// Fill out your copyright notice in the Description page of Project Settings.


#include "WildsAI/MyBaseWildsController.h"

void AMyBaseWildsController::BeginPlay()
{
	Super::BeginPlay();

	if(ensureMsgf(BehaviorTree,TEXT("Wilds Behavior Tree is nullptr! Please Assign BehaviorTree in Your Wilds AI Controller")))
	{
		RunBehaviorTree(BehaviorTree);
	}

}
