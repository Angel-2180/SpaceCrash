// Fill out your copyright notice in the Description page of Project Settings.


#include "CuriousState.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UCuriousState::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsEnum("State") == 1)
	{
		return true;
	}
	return false;
}