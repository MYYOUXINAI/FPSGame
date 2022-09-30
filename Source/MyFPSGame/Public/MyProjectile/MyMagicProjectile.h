// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProjectile/MyProjectileBase.h"
#include "MyMagicProjectile.generated.h"

/**
 * 
 */
UCLASS()
class MYFPSGAME_API AMyMagicProjectile : public AMyProjectileBase
{
	GENERATED_BODY()

protected:
	virtual void OnProjectileHit(UPrimitiveComponent* PrimitiveComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpluse, const FHitResult& HitResult) override;

public:
	AMyMagicProjectile();
};
