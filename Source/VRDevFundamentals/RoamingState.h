// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "RoamingState.generated.h"

/**
 * 
 */

UCLASS()
class VRDEVFUNDAMENTALS_API URoamingState : public UBTDecorator
{
	GENERATED_BODY()

public:

	URoamingState();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
