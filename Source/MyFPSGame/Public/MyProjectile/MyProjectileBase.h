// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyProjectileBase.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class MYFPSGAME_API AMyProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyProjectileBase();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		UParticleSystemComponent* EffectComp;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Effects")
		UParticleSystem* ImpactVFX;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Components")
		USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UProjectileMovementComponent* Movement;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UAudioComponent* AudioComp;


public:	

};
