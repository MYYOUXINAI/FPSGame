// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MyPlayerCharacterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMyPlayerCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MYFPSGAME_API IMyPlayerCharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/* Set Focus Character Bright */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void PlayerFocusInterface(APawn* InstigatorPawn);

	/* Reset The Focus Character Bright */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void PlayerFocusInterfaceRelease(APawn* InstigatorPawn);
};
