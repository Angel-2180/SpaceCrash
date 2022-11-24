// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "StateMachine.generated.h"

/**
 * 
 */
UCLASS()
class VRDEVFUNDAMENTALS_API UStateMachine : public UBTService
{
	GENERATED_BODY()
	
public:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
};
