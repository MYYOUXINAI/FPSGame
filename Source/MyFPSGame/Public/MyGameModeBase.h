// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MYFPSGAME_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "SpawnMinion")
		TSubclassOf<AActor>MinionClass;

	UPROPERTY(EditDefaultsOnly, Category = "SpawnMinion")
		float SpawnTimerInterval;

	UPROPERTY(EditDefaultsOnly, Category = "SpawnMinion")
		UCurveFloat* SpawnMinionCurve;

	FTimerHandle TimerHandle_SpawnMinion;

	UPROPERTY(EditDefaultsOnly,Category="SpawnMinion")
		FVector SpawnMinionLocatin;


	UPROPERTY(EditDefaultsOnly, Category = "GetMoneyToKiller")
		int32 MoneyPerKill;

	UFUNCTION()
		void SpawnMinionTimeElapsed();

	UFUNCTION()
		void RespawnPlayerElapsed(AController* Controller);

public:
	virtual void StartPlay() override;

	AMyGameModeBase();

	UFUNCTION(BlueprintCallable, Category = "ActorKilled")
		void OnActorKilled(AActor* VictimActor, AActor* Killer);
	
};
