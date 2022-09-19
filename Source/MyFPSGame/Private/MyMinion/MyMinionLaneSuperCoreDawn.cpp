// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMinion/MyMinionLaneSuperCoreDawn.h"

#include "MyAttributeComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


AMyMinionLaneSuperCoreDawn::AMyMinionLaneSuperCoreDawn()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	AttributeComp = CreateDefaultSubobject<UMyAttributeComponent>("AttributeComp");

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void AMyMinionLaneSuperCoreDawn::MinionAttack()
{
	if(ensure(MinionAttackMontage))
	{
		PlayAnimMontage(MinionAttackMontage);
	}
}
