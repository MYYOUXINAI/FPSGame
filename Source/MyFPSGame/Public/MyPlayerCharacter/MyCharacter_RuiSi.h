// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter_RuiSi.generated.h"

class UMyActionComponent;
class UMyShootHelpLightComponent;
class UMyPlayerInterfaceComponent;
class USpringArmComponent;
class UCameraComponent;
class UMyAttributeComponent;


UCLASS()
class MYFPSGAME_API AMyCharacter_RuiSi : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCharacter_RuiSi();

protected:
	//component
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		UCameraComponent* CameraComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		UMyAttributeComponent* AttributeComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		UMyActionComponent* ActionComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		UMyPlayerInterfaceComponent* InterfaceComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		UMyShootHelpLightComponent* ShootHelpLightComp;

	//function
	UFUNCTION()
		void OnHealthChange(AActor* InstigatorActor, UMyAttributeComponent* OwningComp, float NewHealth, float Delta);

public:

	//Action & Axis
	void MoveForward(float Value);
	void MoveRight(float Value);
	void SprintStart();
	void SprintEnd();

	virtual void GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const override;

	void PrimaryAttack();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	virtual void PostInitializeComponents() override;

};
