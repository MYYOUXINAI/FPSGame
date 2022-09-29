// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"

int32 AMyPlayerState::GetMoney() const
{
	return this->Money;
}

void AMyPlayerState::AddMoney(int32 Delta)
{
	if(!ensure(Delta>=0))
	{
		return;
	}
	this->Money += Delta;
	OnMoneyChanged.Broadcast(this, this->Money, Delta);
}

bool AMyPlayerState::RemoveMoney(int32 Delta)
{
	if (!ensure(Delta >= 0))
	{
		return false;
	}

	if(Money<Delta)
	{
		return false;
	}

	this->Money -= Delta;
	OnMoneyChanged.Broadcast(this, this->Money, -Delta);

	return true;
}


//void AMyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//}