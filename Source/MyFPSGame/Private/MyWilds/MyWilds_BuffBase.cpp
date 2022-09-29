// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWilds/MyWilds_BuffBase.h"

// Sets default values
AMyWilds_BuffBase::AMyWilds_BuffBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyWilds_BuffBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyWilds_BuffBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyWilds_BuffBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

