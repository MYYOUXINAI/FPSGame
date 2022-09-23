// Fill out your copyright notice in the Description page of Project Settings.


#include "MyShootHelpLightComponent.h"
#include "Kismet/KismetSystemLibrary.h"


UMyShootHelpLightComponent::UMyShootHelpLightComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	TraceLength = 1000.f;
	Radius = 5.0f;
	bHasFindLocation = false;
}


void UMyShootHelpLightComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


void UMyShootHelpLightComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

FVector UMyShootHelpLightComponent::GetTraceTargetLocation(AActor* InstigatorActor)
{
	if(ensure(InstigatorActor))
	{
		FVector EyeLocation;
		FRotator EyeRotator;

		InstigatorActor->GetActorEyesViewPoint(EyeLocation, EyeRotator);

		const FVector EndLocation = EyeLocation + (EyeRotator.Vector() * TraceLength);

		FCollisionShape CollisionShape;
		CollisionShape.SetSphere(Radius);

		FHitResult Hit;

		const bool bHasHit= UKismetSystemLibrary::LineTraceSingle(InstigatorActor->GetWorld(), EyeLocation, EndLocation, TraceType, false, IgnoreActors, EDrawDebugTrace::None, Hit, true);
		if(bHasHit)
		{
			bHasFindLocation = true;
			TargetLocation = Hit.ImpactPoint;
		}
		else
		{
			bHasFindLocation = true;
			TargetLocation = EndLocation;
		}

		return TargetLocation;
	}

	bHasFindLocation = false;
	return FVector::ZeroVector;
}

