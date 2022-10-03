// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyBaseTurretsController.generated.h"

/**
 * 
 */
UCLASS()
class MYFPSGAME_API AMyBaseTurretsController : public AAIController
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "TurretsAI")
		UBehaviorTree* BehaviorTree;

public:
	virtual void BeginPlay() override;
	
};
