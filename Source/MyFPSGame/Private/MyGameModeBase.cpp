// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "EngineUtils.h"
#include "MyAttributeComponent.h"
#include "MyPlayerState.h"
#include "GameFramework/Character.h"
#include "MyPlayerCharacter/MyCharacter_RuiSi.h"


AMyGameModeBase::AMyGameModeBase()
{
	SpawnTimerInterval = 2.0f;
	MoneyPerKill = 20;

	PlayerStateClass = AMyPlayerState::StaticClass();

}

void AMyGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnMinion, this, &AMyGameModeBase::SpawnMinionTimeElapsed, SpawnTimerInterval, true);
}


void AMyGameModeBase::SpawnMinionTimeElapsed()
{
	if(ensure(MinionClass))
	{
		int32 NrOfAliveMinion = 0;
		for(TActorIterator<ACharacter> It(GetWorld());It;++It)
		{
			UMyAttributeComponent* AttributeComp = Cast<UMyAttributeComponent>(It->GetComponentByClass(UMyAttributeComponent::StaticClass()));
			if(AttributeComp&& AttributeComp->IsAlive())
			{
				++NrOfAliveMinion;
			}
		}

		float MaxMinionCnt = 5.0f;
		if(SpawnMinionCurve)
		{
			MaxMinionCnt = SpawnMinionCurve->GetFloatValue(GetWorld()->GetTimeSeconds());
		}

		if (NrOfAliveMinion > MaxMinionCnt)	return;

		GetWorld()->SpawnActor<AActor>(MinionClass, SpawnMinionLocatin, FRotator::ZeroRotator);
	}
}

void AMyGameModeBase::RespawnPlayerElapsed(AController* Controller)
{
	if(ensure(Controller))
	{
		Controller->UnPossess();

		RestartPlayer(Controller);
	}
}

void AMyGameModeBase::OnActorKilled(AActor* VictimActor, AActor* Killer)
{
	UE_LOG(LogTemp, Log, TEXT("OnActorKilled: Victim: %s ,Killer: %s"), *GetNameSafe(VictimActor), *GetNameSafe(Killer));

	AMyCharacter_RuiSi* Character_RuiSi = Cast<AMyCharacter_RuiSi>(VictimActor);

	/* the Victim Actor is Player Character */
	if(Character_RuiSi)
	{
		FTimerHandle TimerHandle_RespawnDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "RespawnPlayerElapsed", Character_RuiSi->GetController());

		float RespawnDelay = 2.0f;

		GetWorld()->GetTimerManager().SetTimer(TimerHandle_RespawnDelay, Delegate, RespawnDelay, false);
	}

	/* Add Money To Killer */
	APawn* KillerPawn = Cast<APawn>(Killer);
	if(KillerPawn && KillerPawn!=VictimActor)
	{
		AMyPlayerState* PS = KillerPawn->GetPlayerState<AMyPlayerState>();
		if(PS)
		{
			PS->AddMoney(MoneyPerKill);
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("AddMoney"), true);
		}
	}
}
