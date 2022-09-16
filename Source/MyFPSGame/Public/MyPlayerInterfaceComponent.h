// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyPlayerCharacter/MyPlayerCharacterInterface.h"
#include "MyPlayerInterfaceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYFPSGAME_API UMyPlayerInterfaceComponent : public UActorComponent,public IMyPlayerCharacterInterface
{
	GENERATED_BODY()

public:	
	UMyPlayerInterfaceComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly,Category="Trace")
		float TraceDistance;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
		float TraceRadius;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
		TEnumAsByte<ECollisionChannel>CollisionChannel;

	UPROPERTY(EditDefaultsOnly, Category = "Interface")
		FName FocusBrightName;

	UPROPERTY(EditDefaultsOnly, Category = "Interface")
		FColor BrightColor;

	UPROPERTY(EditDefaultsOnly, Category = "Interface")
		FName FocusBrightStrengthName;

	UPROPERTY(EditDefaultsOnly, Category = "Interface")
		float BrightStrength;

	UPROPERTY()
		AActor* FocusedActor;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable,Category="MyInterface")
	void FindBestInteractable();

	virtual void PlayerFocusInterface_Implementation(APawn* InstigatorPawn) override;

	virtual void PlayerFocusInterfaceRelease_Implementation(APawn* InstigatorPawn) override;
};
