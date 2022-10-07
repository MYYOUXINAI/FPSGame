// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyTurretBase.generated.h"

class UMyActionComponent;
class UMyUserWidget;
class UPawnSensingComponent;
class UMyAttributeComponent;
class USpringArmComponent;
class UCameraComponent;
UCLASS()
class MYFPSGAME_API AMyTurretBase : public ACharacter
{
	GENERATED_BODY()

public:
	AMyTurretBase();


protected:
	//Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UMyAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UMyActionComponent* ActionComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Component")
		UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Blackboard")
		FName TargetActorName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HealthBarUI")
		UMyUserWidget* ActiveHealthBar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HealthBarUI")
		TSubclassOf<UUserWidget>HealthBarWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
		FVector LookAtLocation;

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

	UFUNCTION(BlueprintCallable, Category = "MyTurretsAnimation")
		FVector GetLookAtLocation()const;

	virtual void Tick(float DeltaSeconds) override;
};
