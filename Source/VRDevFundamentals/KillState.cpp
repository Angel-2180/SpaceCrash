// Fill out your copyright notice in the Description page of Project Settings.


#include "KillState.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UKillState::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsEnum("State") == 2)
	{
		return true;
	}
	return false;
}
