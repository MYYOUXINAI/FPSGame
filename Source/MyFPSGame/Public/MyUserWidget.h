// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

class USizeBox;
/**
 * 
 */
UCLASS()
class MYFPSGAME_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "UI")
		AActor* AttachedActor;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "UI")
		FVector WorldOffset;

protected:
	UPROPERTY(meta = (BindWidget))
		USizeBox* ParentSizeBox;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
};
