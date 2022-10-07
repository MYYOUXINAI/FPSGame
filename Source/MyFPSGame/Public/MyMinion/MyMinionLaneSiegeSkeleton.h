// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyMinionLaneSiegeSkeleton.generated.h"

class UMyUserWidget;
class UPawnSensingComponent;
class UMyActionComponent;
class UMyAttributeComponent;
class USpringArmComponent;
class UCameraComponent;


UCLASS()
class MYFPSGAME_API AMyMinionLaneSiegeSkeleton : public ACharacter
{
	GENERATED_BODY()

public:

	AMyMinionLaneSiegeSkeleton();


protected:
	//Component
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		UCameraComponent* CameraComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		UMyAttributeComponent* AttributeComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		UMyActionComponent* ActionComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Component")
		UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Blackboard")
		FName TargetActorName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HealthBarUI")
		UMyUserWidget* ActiveHealthBar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HealthBarUI")
		TSubclassOf<UUserWidget>HealthBarWidgetClass;

	//Function
	UFUNCTION()
		void MyOnPawnSeen(APawn* Pawn);

	UFUNCTION()
		AActor* GetTargetActor() const;

	UFUNCTION()
		void SetTargetActor(AActor* NewTargetActor) const;

	UFUNCTION()
		void OnHealthChanged(AActor* InstigatorActor, UMyAttributeComponent* OwningComp, float NewHealth, float Delta);

public:
	virtual void PostInitializeComponents() override;



};
