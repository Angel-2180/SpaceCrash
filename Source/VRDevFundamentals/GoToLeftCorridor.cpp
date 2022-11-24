// Fill out your copyright notice in the Description page of Project Settings.


#include "GoToLeftCorridor.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UGoToLeftCorridor::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsEnum("CorridorEventToGo") == 1)
	{
		return true;
	}
	return false;
}