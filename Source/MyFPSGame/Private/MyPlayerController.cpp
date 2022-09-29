// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

void AMyPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	OnPawnChanged.Broadcast(InPawn);
}

void AMyPlayerController::BeginPlayingState()
{
	Super::BeginPlayingState();

	OnPlayerStateReceived.Broadcast(PlayerState);
}
