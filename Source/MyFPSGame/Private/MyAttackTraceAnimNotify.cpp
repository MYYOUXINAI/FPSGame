// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAttackTraceAnimNotify.h"
#include "MyAttributeComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UMyAttackTraceAnimNotify::UMyAttackTraceAnimNotify()
{
	DamageValue = -50;
}


void UMyAttackTraceAnimNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                           float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	Player = MeshComp->GetOwner();
	
	if (Player)
	{
		for (const FName SocketName : SocketNames)
		{
			LastLocations.Add(MeshComp->GetSocketLocation(SocketName));
		}
		ActorsToIgnore.Add(Player);
	}
}

void UMyAttackTraceAnimNotify::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	if (Player)
	{
		
		for (int32 i = 0; i < LastLocations.Num(); ++i)
		{
			UKismetSystemLibrary::BoxTraceMulti(MeshComp->GetWorld(), LastLocations[i], MeshComp->GetSocketLocation(SocketNames[i]), FVector(5, 40, 20), MeshComp->GetSocketRotation(SocketNames[i]), TraceType, false, ActorsToIgnore, EDrawDebugTrace::ForOneFrame, HitResults, true);
			for(int32 j=0;j<HitResults.Num();++j)
			{
				AActor* HitActor = HitResults[j].GetActor();
				if(!HitActors.Contains(HitActor))
				{
					HitActors.Add(HitActor);
					UMyAttributeComponent* AttributeComponent = UMyAttributeComponent::GetAttributes(HitActor);
					if(AttributeComponent)
					{
						AttributeComponent->ApplyHealthChange(MeshComp->GetOwner(), DamageValue);
					}
				}
			}
			LastLocations[i] = MeshComp->GetSocketLocation(SocketNames[i]);
		}
	}
}

void UMyAttackTraceAnimNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	/* clear data */
	if (Player)
	{
		HitResults.Empty();
		HitActors.Empty();
		LastLocations.Empty();
		ActorsToIgnore.Empty();
	}
}
