// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTurretsAI/MyBaseTurretsController.h"

void AMyBaseTurretsController::BeginPlay()
{
	Super::BeginPlay();

	if (ensureMsgf(BehaviorTree, TEXT("Behavior Tree is nullptr! Please assign BehaviorTree in your Turrets AI Controller!")))
	{
		RunBehaviorTree(BehaviorTree);
	}
	
}
