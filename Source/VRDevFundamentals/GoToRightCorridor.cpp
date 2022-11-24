// Fill out your copyright notice in the Description page of Project Settings.


#include "GoToRightCorridor.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UGoToRightCorridor::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsEnum("CorridorEventToGo") == 2)
	{
		return true;
	}
	return false;
}