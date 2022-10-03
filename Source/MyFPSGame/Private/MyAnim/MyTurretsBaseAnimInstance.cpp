// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnim/MyTurretsBaseAnimInstance.h"
#include "AIController.h"
#include "MyTurrets/MyTurretBase.h"

void UMyTurretsBaseAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

}

void UMyTurretsBaseAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwningActor = Cast<AMyTurretBase>(GetOwningActor());
	ensure(OwningActor);

	if(false)
	{
		OpenPanel = true;
		Aiming = true;
		OpenShield = true;
		isFiring = true;
		TurretDamage = 1.0f;
	}
}

void UMyTurretsBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OwningActor)	Yaw = OwningActor->GetYaw();

	Yaw += 45;
	if(Yaw>180)
	{
		Yaw -= 360;
	}

}
