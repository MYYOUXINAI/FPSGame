// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyBaseMinionController.generated.h"

/**
 * 
 */
UCLASS()
class MYFPSGAME_API AMyBaseMinionController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly,Category="MinionAI")
		UBehaviorTree* BehaviorTree;

public:

	virtual void BeginPlay() override;
	
};
