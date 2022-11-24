// Fill out your copyright notice in the Description page of Project Settings.


#include "RightDoorIsOpened.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SpaceCraftDoor.h"

bool URightDoorIsOpened::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (Cast<ASpaceCraftDoor>(OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsObject("RightDoor"))->IsOpen)
	{
		return true;
	}
	return false;
}