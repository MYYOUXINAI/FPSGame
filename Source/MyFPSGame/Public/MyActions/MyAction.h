// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/NoExportTypes.h"
#include "MyAction.generated.h"

class UMyActionComponent;

USTRUCT()
struct FActionRepData
{
	GENERATED_BODY()

public:

	UPROPERTY()
		bool bIsRunning;

	UPROPERTY()
		AActor* InstigatorActor;
};

/**
 * 
 */
UCLASS(Blueprintable)
class MYFPSGAME_API UMyAction : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(Replicated)
		UMyActionComponent* ActionComp;

	UFUNCTION(BlueprintCallable, Category = "Action")
		UMyActionComponent* GetOwningComponent()const;

	UPROPERTY(EditDefaultsOnly, Category = "Tags")
		FGameplayTagContainer GrantsTags;

	UPROPERTY(EditDefaultsOnly, Category = "Tags")
		FGameplayTagContainer BlockedTags;

	UPROPERTY(ReplicatedUsing = "OnRep_RepData")
		FActionRepData RepData;

	UPROPERTY(Replicated)
		float TimeStarted;

	UFUNCTION()
		void OnRep_RepData();

public:

	void Initialize(UMyActionComponent* NewActionComp);

	UPROPERTY(EditDefaultsOnly, Category = "Action")
		bool bAutoStart;

	UFUNCTION(BlueprintCallable, Category = "Action")
		bool IsRunning()const;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent, Category = "Action")
		bool CanStart(AActor* InstigatorActor);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent, Category = "Action")
		void StartAction(AActor* InstigatorActor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Action")
		void StopAction(AActor* InstigatorActor);

	UPROPERTY(EditDefaultsOnly, Category = "Action")
		FName ActionName;

	virtual UWorld* GetWorld() const override;


	virtual bool IsSupportedForNetworking() const override;
};
