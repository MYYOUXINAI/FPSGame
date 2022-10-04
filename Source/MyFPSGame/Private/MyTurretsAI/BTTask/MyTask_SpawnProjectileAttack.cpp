// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTurretsAI/BTTask/MyTask_SpawnProjectileAttack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"



EBTNodeResult::Type UMyTask_SpawnProjectileAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIC = OwnerComp.GetAIOwner();
	if(ensure(AIC))
	{
		ACharacter* OwningCharacter = Cast<ACharacter>(AIC->GetPawn());
		if(ensure(OwningCharacter))
		{
			if(ensureMsgf(ProjectileClass,TEXT("Please assign the Projectile in spawn projectile attack AI task!!")))
			{
				FVector SocketLocation = OwningCharacter->GetMesh()->GetSocketLocation(SocketName);
				AActor* TargetActor = Cast<AActor>(AIC->GetBlackboardComponent()->GetValueAsObject(TargetActorKey.SelectedKeyName));

				if(ensure(TargetActor))
				{
					FVector TargetActorLocation = TargetActor->GetActorLocation();

					FRotator SpawnActorRotator = FRotationMatrix::MakeFromX(TargetActorLocation - SocketLocation).Rotator();

					FActorSpawnParameters SpawnParams;
					SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

					SpawnParams.Instigator = OwningCharacter;

					AActor* ProjectileActor = GetWorld()->SpawnActor<AActor>(ProjectileClass, SocketLocation, SpawnActorRotator, SpawnParams);

					if (ProjectileActor)
					{
						return EBTNodeResult::Succeeded;
					}
				}
			}
		}
	}

	return EBTNodeResult::Failed;
}
