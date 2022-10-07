// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"

#include "AIController.h"
#include "MyAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


bool UMyBlueprintFunctionLibrary::ApplyDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount)
{
	UMyAttributeComponent* AttributeComp = UMyAttributeComponent::GetAttributes(TargetActor);
	if(AttributeComp)
	{
		return AttributeComp->ApplyHealthChange(DamageCauser, DamageAmount);
	}
	return false;
}

bool UMyBlueprintFunctionLibrary::ApplyDirectionalDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount,
	const FHitResult& HitResult)
{
	if(ApplyDamage(DamageCauser,TargetActor,DamageAmount))
	{
		UPrimitiveComponent* HitComp = HitResult.GetComponent();
		if(ensure(HitComp) && HitComp->IsSimulatingPhysics())
		{
			FVector Direction = HitResult.TraceEnd - HitResult.TraceStart;
			Direction.Normalize();

			HitComp->AddImpulseAtLocation(Direction * 30000.f, HitResult.ImpactPoint, HitResult.BoneName);
			return true;
		}
		return true;
	}

	return false;
}

bool UMyBlueprintFunctionLibrary::TurretGunFocusToTargetActor(APawn* OwnerPawn,
	FName TargetActorName, FVector& LookAtLocation)
{
	if(ensure(OwnerPawn))
	{
		AAIController* AIC = Cast<AAIController>(OwnerPawn->GetController());
		if(ensure(AIC))
		{
			AActor* TargetActor = Cast<AActor>(AIC->GetBlackboardComponent()->GetValueAsObject(TargetActorName));
			if(TargetActor)
			{
				LookAtLocation = TargetActor->GetActorLocation() - OwnerPawn->GetActorLocation();
				return true;
			}
		}
	}
	return false;
}

