// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProjectile/MyMagicProjectile.h"

#include "MyBlueprintFunctionLibrary.h"
#include "Components/SphereComponent.h"

//void AMyMagicProjectile::OnMagicProjectileHit(UPrimitiveComponent* PrimitiveComponent, AActor* OtherActor,
//	UPrimitiveComponent* OtherComp, FVector NormalImpluse, const FHitResult& HitResult)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("!"), true);
//	if (OtherActor && OtherActor != GetInstigator())
//	{
//		if (UMyBlueprintFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, DamageValue, HitResult))
//		{
//			//ProjectileExplode();
//		}
//	}
//
//}
//
//void AMyMagicProjectile::PostInitializeComponents()
//{
//	Super::PostInitializeComponents();
//
//	this->SphereComp->OnComponentHit.AddDynamic(this, &AMyMagicProjectile::OnMagicProjectileHit);
//}


void AMyMagicProjectile::OnProjectileHit(UPrimitiveComponent* PrimitiveComponent, AActor* OtherActor,
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

AMyMagicProjectile::AMyMagicProjectile()
{
	this->DamageValue = -50;
}
