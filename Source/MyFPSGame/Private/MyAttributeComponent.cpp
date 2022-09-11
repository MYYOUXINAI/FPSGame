// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAttributeComponent.h"

// Sets default values for this component's properties
UMyAttributeComponent::UMyAttributeComponent()
{
	SprintDeltaSpeed = 600.f;


}

UMyAttributeComponent* UMyAttributeComponent::GetAttributes(AActor* InstigatorActor)
{
	if(ensure(InstigatorActor))
	{
		UMyAttributeComponent* AttributeComp = Cast<UMyAttributeComponent>(InstigatorActor->GetComponentByClass(UMyAttributeComponent::StaticClass()));
		if(ensure(AttributeComp))
		{
			return AttributeComp;
		}
	}
	return nullptr;
}


