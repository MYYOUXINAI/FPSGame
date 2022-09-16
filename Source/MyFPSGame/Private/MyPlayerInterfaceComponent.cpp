// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerInterfaceComponent.h"

#include "DrawDebugHelpers.h"
#include "MyPlayerCharacter/MyCharacter_RuiSi.h"
#include "MyPlayerCharacter/MyPlayerCharacterInterface.h"


UMyPlayerInterfaceComponent::UMyPlayerInterfaceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	PrimaryComponentTick.TickGroup = TG_PostUpdateWork;

	TraceDistance = 1000.0f;
	TraceRadius = 30.0f;
	CollisionChannel = ECC_Pawn;

	FocusBrightName = "FocusBrightColor";
	BrightColor = FColor(0.737, 0.76, 0.02);

	FocusBrightStrengthName = "BrightStrength";
	BrightStrength = 0.5f;

	FocusedActor = nullptr;
}



void UMyPlayerInterfaceComponent::BeginPlay()
{
	Super::BeginPlay();


}


// Called every frame
void UMyPlayerInterfaceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	this->FindBestInteractable();
}

void UMyPlayerInterfaceComponent::FindBestInteractable()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(CollisionChannel);

	AActor* MyOwner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotator;

	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotator);

	//EyeRotator = MyOwner->GetInstigatorController()->GetControlRotation();

	FVector EndLocation = EyeLocation + (EyeRotator.Vector() * TraceDistance);

	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(TraceRadius);

	TArray<FHitResult>Hits;

	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, EndLocation, FQuat::Identity, ObjectQueryParams, CollisionShape);

	FColor LineColor = bBlockingHit ? FColor::Red : FColor::Green;

	AActor* OldTargetActor = FocusedActor;
	FocusedActor = nullptr;

	for (FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor && HitActor != MyOwner)
		{
			if (HitActor->Implements<UMyPlayerCharacterInterface>())
			{
				//DrawDebugSphere(GetWorld(), Hit.ImpactPoint, TraceRadius, 32, LineColor, false, 0.0f);
				FocusedActor = HitActor;
				break;
			}
		}
	}

	if (FocusedActor != OldTargetActor)
	{
		if(FocusedActor!=nullptr)
		{
			AMyCharacter_RuiSi* TargetCharacter = Cast<AMyCharacter_RuiSi>(FocusedActor);
			if (ensure(TargetCharacter))
			{
				UMyPlayerInterfaceComponent* InterfaceComponent = Cast<UMyPlayerInterfaceComponent>(TargetCharacter->GetComponentByClass(UMyPlayerInterfaceComponent::StaticClass()));
				if (ensure(InterfaceComponent))
				{
					APawn* MyPawn = Cast<APawn>(GetOwner());
					if (MyPawn)
					{
						IMyPlayerCharacterInterface::Execute_PlayerFocusInterface(InterfaceComponent, MyPawn);
					}
				}
			}
		}

		if(OldTargetActor!=nullptr)
		{
			AMyCharacter_RuiSi* TargetCharacter = Cast<AMyCharacter_RuiSi>(OldTargetActor);
			if (ensure(OldTargetActor))
			{
				UMyPlayerInterfaceComponent* InterfaceComponent = Cast<UMyPlayerInterfaceComponent>(OldTargetActor->GetComponentByClass(UMyPlayerInterfaceComponent::StaticClass()));
				if (ensure(InterfaceComponent))
				{
					APawn* MyPawn = Cast<APawn>(GetOwner());
					if (MyPawn)
					{
						IMyPlayerCharacterInterface::Execute_PlayerFocusInterfaceRelease(InterfaceComponent, MyPawn);
					}
				}
			}
		}
	}

}

void UMyPlayerInterfaceComponent::PlayerFocusInterface_Implementation(APawn* InstigatorPawn)
{
	IMyPlayerCharacterInterface::PlayerFocusInterface_Implementation(InstigatorPawn);
	
	const AMyCharacter_RuiSi* MyCharacter = Cast<AMyCharacter_RuiSi>(GetOwner());
	if(ensure(MyCharacter))
	{
		USkeletalMeshComponent* MyMesh = MyCharacter->GetMesh();
		if(ensure(MyMesh))
		{
			/* set color */
			MyMesh->SetVectorParameterValueOnMaterials(FocusBrightName, FVector(BrightColor.R / 255.f, BrightColor.G / 255.f, BrightColor.B / 255.f));

			/* set light strength */
			MyMesh->SetScalarParameterValueOnMaterials(FocusBrightStrengthName, BrightStrength);
		}
	}
}

void UMyPlayerInterfaceComponent::PlayerFocusInterfaceRelease_Implementation(APawn* InstigatorPawn)
{
	IMyPlayerCharacterInterface::PlayerFocusInterfaceRelease_Implementation(InstigatorPawn);

	const AMyCharacter_RuiSi* MyCharacter = Cast<AMyCharacter_RuiSi>(GetOwner());
	if (ensure(MyCharacter))
	{
		USkeletalMeshComponent* MyMesh = MyCharacter->GetMesh();
		if (ensure(MyMesh))
		{
			/* Reset Color */
			MyMesh->SetVectorParameterValueOnMaterials(FocusBrightName, FVector(0,0,0));

			/* Reset Light Strength */
			MyMesh->SetScalarParameterValueOnMaterials(FocusBrightStrengthName, 1.0f);
		}
	}
}



