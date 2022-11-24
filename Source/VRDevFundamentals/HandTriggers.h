// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerSphere.h"
#include "HandTriggers.generated.h"

/**
 * 
 */
UCLASS()
class VRDEVFUNDAMENTALS_API AHandTriggers : public ATriggerSphere
{
	GENERATED_BODY()

public:

	AHandTriggers();

	UFUNCTION()
		void HandsOutBounds(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
