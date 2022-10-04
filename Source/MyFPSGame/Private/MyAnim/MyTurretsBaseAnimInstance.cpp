// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnim/MyTurretsBaseAnimInstance.h"
#include "AIController.h"
#include "MyTurrets/MyTurretBase.h"

void UMyTurretsBaseAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	RotateDelta = 2.0f;
}

void UMyTurretsBaseAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwningActor = Cast<AMyTurretBase>(GetOwningActor());
	ensure(OwningActor);
}

void UMyTurretsBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	float NewYaw = 0.0f;

	if (OwningActor)	NewYaw = OwningActor->GetYaw();

	NewYaw += 45;
	if(NewYaw>180)
	{
		NewYaw -= 360;
	}

	FocusToTargetActorSmooth(RotateDelta, NewYaw);

}

void UMyTurretsBaseAnimInstance::FocusToTargetActorSmooth(float Delta, float NewYaw)
{
	const int dis = fabs(NewYaw - Yaw);

	if(dis<=Delta)
	{
		Yaw = NewYaw;
		return;
	}

	const bool bFlag = dis > 180;
	if(bFlag)
	{
		if(NewYaw>Yaw)
		{
			Delta *= -1;
		}
		Yaw += Delta;
	}
	else
	{
		if(NewYaw<Yaw)
		{
			Delta *= -1;
		}
		Yaw += Delta;
	}

	if(Yaw>180)
	{
		Yaw -= 360;
	}
	if(Yaw<-180)
	{
		Yaw += 360;
	}
}
