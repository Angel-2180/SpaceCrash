// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PlayCentralDoorFootStep.generated.h"

/**
 * 
 */
UCLASS()
class VRDEVFUNDAMENTALS_API UPlayCentralDoorFootStep : public UBTTaskNode
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
