// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyBaseWildsController.generated.h"

/**
 * 
 */
UCLASS()
class MYFPSGAME_API AMyBaseWildsController : public AAIController
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "WildsAI")
		UBehaviorTree* BehaviorTree;

public:
	virtual void BeginPlay() override;
	
};
