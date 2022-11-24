// Fill out your copyright notice in the Description page of Project Settings.


#include "LeftDoorIsOpened.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SpaceCraftDoor.h"

bool ULeftDoorIsOpened::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (Cast<ASpaceCraftDoor>(OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsObject("LeftDoor"))->IsOpen)
	{
		return true;
	}
	return false;
}