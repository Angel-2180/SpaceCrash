// Fill out your copyright notice in the Description page of Project Settings.


#include "RoamingState.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"

URoamingState::URoamingState()
{
	bNotifyTick = true;
}

bool URoamingState::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsEnum("State") == 0)
	{
		return true;
	}
	return false;
}
