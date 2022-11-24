// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "GoToRightCorridor.generated.h"

/**
 * 
 */
UCLASS()
class VRDEVFUNDAMENTALS_API UGoToRightCorridor : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
