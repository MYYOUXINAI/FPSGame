// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProjectile/MyProjectileBase.h"

#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AMyProjectileBase::AMyProjectileBase()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	ImpactVFX = CreateDefaultSubobject<UParticleSystem>("ImpactVFX");
	ImpactVFX->bAutoDeactivate = true;

	AudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComp");
	AudioComp->SetupAttachment(SphereComp);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>("Movement");
	Movement->bRotationFollowsVelocity = true;
	Movement->bInitialVelocityInLocalSpace = true;
	Movement->ProjectileGravityScale = 0.f;
	Movement->InitialSpeed = 8000.f;

}


