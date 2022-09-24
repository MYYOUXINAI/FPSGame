// Fill out your copyright notice in the Description page of Project Settings.


#include "MyShootHelpLightComponent.h"

#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MyPlayerCharacter/MyCharacter_RuiSi.h"


class AMyCharacter_RuiSi;

UMyShootHelpLightComponent::UMyShootHelpLightComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	TraceLength = 1000.f;
	Radius = 5.0f;
	bHasFindLocation = false;

	EyeLocationName = "Eyes_Position";
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
	/*if(ensure(InstigatorActor))
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
	return FVector::ZeroVector;*/


	if (ensure(InstigatorActor))
	{
		FVector EyeLocation;
		FRotator EyeRotator;

		AMyCharacter_RuiSi* OwnerCharacter = Cast<AMyCharacter_RuiSi>(InstigatorActor);
		if(!ensure(OwnerCharacter))	return FVector::ZeroVector;

		OwnerCharacter->GetActorEyesViewPoint(EyeLocation, EyeRotator);

		const FVector StartLocation = OwnerCharacter->GetMesh()->GetSocketLocation(EyeLocationName) + OwnerCharacter->
		                                                                                              GetActorRotation().Vector() * 20;

		const FVector EndLocation = EyeLocation + (EyeRotator.Vector() * TraceLength);

		FCollisionShape CollisionShape;
		CollisionShape.SetSphere(Radius);

		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);


		FHitResult Hit;

		const bool bHasHit = GetWorld()->SweepSingleByObjectType(Hit, StartLocation, EndLocation, FQuat::Identity, ObjectQueryParams, CollisionShape);
		
		if (bHasHit)
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

