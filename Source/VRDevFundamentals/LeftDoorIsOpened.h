// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "LeftDoorIsOpened.generated.h"

/**
 * 
 */
UCLASS()
class VRDEVFUNDAMENTALS_API ULeftDoorIsOpened : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
