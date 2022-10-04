// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProjectile/MyTurretsProjectile.h"

#include "MyBlueprintFunctionLibrary.h"


AMyTurretsProjectile::AMyTurretsProjectile()
{
	this->DamageValue = -100;
}


void AMyTurretsProjectile::OnProjectileHit(UPrimitiveComponent* PrimitiveComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpluse, const FHitResult& HitResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		if (UMyBlueprintFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, DamageValue, HitResult))
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Has hit and Apply damage!"), true);
		}
		ProjectileExplode();
	}
}
