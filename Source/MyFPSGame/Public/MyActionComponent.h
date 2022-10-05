// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "MyActionComponent.generated.h"


class UMyAction;
class UMyActionComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActionStateChanged, UMyActionComponent*, OwningComp, UMyAction*, Action);



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYFPSGAME_API UMyActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMyActionComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
		FGameplayTagContainer ActiveGameplayTags;

	UFUNCTION(BlueprintCallable, Category = "Actions")
		void AddAction(AActor* InstigatorActor, TSubclassOf<UMyAction> ActionClass);

	UFUNCTION(BlueprintCallable, Category = "Actions")
		void RemoveAction(UMyAction* ActionToRemove);

	UFUNCTION(BlueprintCallable, Category = "Actions")
		UMyAction* GetAction(TSubclassOf<UMyAction> ActionClass)const;

	UFUNCTION(BlueprintCallable, Category = "Actions")
		bool StartActionByName(AActor* InstigatorActor, FName ActionName);

	UFUNCTION(BlueprintCallable, Category = "Actions")
		bool StopActionByName(AActor* InstigatorActor, FName ActionName);

protected:
	UFUNCTION(Server, Reliable)
		void ServerStartAction(AActor* InstigatorActor, FName ActionName);

	UFUNCTION(Server, Reliable)
		void ServerStopAction(AActor* InstigatorActor, FName ActionName);

	UPROPERTY(EditAnywhere, Category = "Actions")
		TArray<TSubclassOf<UMyAction>> DefaultsActions;

	UPROPERTY(BlueprintReadOnly, Replicated)
		TArray<UMyAction*> Actions;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:

	UPROPERTY(BlueprintAssignable)
		FOnActionStateChanged OnActionStarted;

	UPROPERTY(BlueprintAssignable)
		FOnActionStateChanged OnActionStopped;

	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
