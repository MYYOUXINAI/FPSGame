// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAttackTraceAnimNotify.h"
#include "MyAttributeComponent.h"
#include "MyBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

UMyAttackTraceAnimNotify::UMyAttackTraceAnimNotify()
{
	DamageValue = -50;
	TraceRadius = 10.0f;
	EmitterScale = FVector(1.0, 1.0, 1.0);
}


void UMyAttackTraceAnimNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	Player = MeshComp->GetOwner();

	if (Player)
	{
		ActorsToIgnore.Add(Player);
	}
}

void UMyAttackTraceAnimNotify::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	if (Player)
	{
		for (int32 i = 0; i < SocketNames.Num() / 2; ++i)
		{
			UKismetSystemLibrary::SphereTraceMulti(MeshComp->GetWorld(), MeshComp->GetSocketLocation(SocketNames[2 * i]), MeshComp->GetSocketLocation(SocketNames[2 * i + 1]), TraceRadius, TraceType, false, ActorsToIgnore, EDrawDebugTrace::None, HitResults, true);
			for (int32 j = 0; j < HitResults.Num(); ++j)
			{
				AActor* HitActor = HitResults[j].GetActor();
				if (!HitActors.Contains(HitActor))
				{
					/* add attack emitter effect */
					{
						if(ensure(EmitterType))
						{
							UGameplayStatics::SpawnEmitterAtLocation(MeshComp->GetWorld(), EmitterType, HitResults[j].ImpactPoint, FRotator::ZeroRotator, EmitterScale, true);
						}
					}

					HitActors.Add(HitActor);
					UMyAttributeComponent* AttributeComponent = UMyAttributeComponent::GetAttributes(HitActor);
					if (AttributeComponent)
					{
						AttributeComponent->MyHitReact(HitResults[j].ImpactPoint);
						UMyBlueprintFunctionLibrary::ApplyDirectionalDamage(MeshComp->GetOwner(), HitActor, DamageValue, HitResults[j]);
					}
				}
			}
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
		ActorsToIgnore.Empty();
	}
}
