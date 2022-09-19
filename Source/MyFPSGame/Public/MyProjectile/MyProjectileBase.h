// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyProjectileBase.generated.h"

class USoundCue;
class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class MYFPSGAME_API AMyProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyProjectileBase();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Effects|Shake")
		TSubclassOf<UCameraShakeBase>ImpactShake;

	UPROPERTY(EditDefaultsOnly, Category = "Effects|Shake")
		float ImpactShakeInnerRadius;

	UPROPERTY(EditDefaultsOnly, Category = "Effects|Shake")
		float ImpactShakeOuterRadius;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		USoundCue* ImpactSound;

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


	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		float DamageValue;


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void ProjectileExplode();

	UFUNCTION()
	virtual void OnProjectileHit(UPrimitiveComponent* PrimitiveComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, FVector NormalImpluse, const FHitResult& HitResult);

	virtual void PostInitializeComponents() override;

public:	
	virtual void BeginPlay() override;
};
