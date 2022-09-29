// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

class AMyPlayerState;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnMoneyChanged, AMyPlayerState*, PlayerState, int32, NewMoney, int32, Delta);


/**
 * 
 */
UCLASS()
class MYFPSGAME_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Money")
		int32 Money;


public:

	UPROPERTY(BlueprintAssignable)
		FOnMoneyChanged OnMoneyChanged;

	UFUNCTION(BlueprintCallable, Category = "Money")
		int32 GetMoney()const;

	UFUNCTION(BlueprintCallable, Category = "Money")
		void AddMoney(int32 Delta);

	UFUNCTION(BlueprintCallable, Category = "Money")
		bool RemoveMoney(int32 Delta);

};
