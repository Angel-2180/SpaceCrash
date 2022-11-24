// Fill out your copyright notice in the Description page of Project Settings.


#include "GoToCentralCorridor.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UGoToCentralCorridor::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsEnum("CorridorEventToGo") == 0)
	{
		return true;
	}
	return false;
}