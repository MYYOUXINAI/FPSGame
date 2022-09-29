// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProjectile/MyProjectileBase.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"


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

	ImpactShakeInnerRadius = 0.0f;
	ImpactShakeOuterRadius = 900.0f;

	ImpactSound = CreateDefaultSubobject<USoundCue>("ImpactSound");

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>("Movement");
	Movement->bRotationFollowsVelocity = true;
	Movement->bInitialVelocityInLocalSpace = true;
	Movement->ProjectileGravityScale = 0.f;
	Movement->InitialSpeed = 8000.f;


	DamageValue = -20.f;
}

void AMyProjectileBase::ProjectileExplode_Implementation()
{
	if(!IsPendingKill())
	{
		if (ensure(ImpactVFX))
			UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, this->GetActorLocation(), this->GetActorRotation());
		if (ensure(ImpactSound))
			UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, this->GetActorLocation());
		if (ensure(ImpactShake))
			UGameplayStatics::PlayWorldCameraShake(this, ImpactShake, this->GetActorLocation(), ImpactShakeInnerRadius, ImpactShakeOuterRadius);
		Destroy();
	}

	////GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("test hit times!"), true);
}


void AMyProjectileBase::OnProjectileHit(UPrimitiveComponent* PrimitiveComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpluse, const FHitResult& HitResult)
{
	if(OtherActor!=GetInstigator())	ProjectileExplode();
}

void AMyProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	this->SphereComp->OnComponentHit.AddDynamic(this, &AMyProjectileBase::OnProjectileHit);
}

void AMyProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(10.0);


}


