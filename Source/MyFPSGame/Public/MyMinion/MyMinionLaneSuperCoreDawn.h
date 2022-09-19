// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyMinionLaneSuperCoreDawn.generated.h"


class UMyAttributeComponent;
class USpringArmComponent;
class UCameraComponent;
UCLASS()
class MYFPSGAME_API AMyMinionLaneSuperCoreDawn : public ACharacter
{
	GENERATED_BODY()

public:
	AMyMinionLaneSuperCoreDawn();

protected:
	//component
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		UCameraComponent* CameraComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		UMyAttributeComponent* AttributeComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AttackAnim")
		UAnimMontage* MinionAttackMontage;


public:
	UFUNCTION(BlueprintCallable,Category="MinionAttack")
		void MinionAttack();


};
