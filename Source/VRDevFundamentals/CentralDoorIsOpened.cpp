// Fill out your copyright notice in the Description page of Project Settings.


#include "CentralDoorIsOpened.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SpaceCraftDoor.h"

bool UCentralDoorIsOpened::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (Cast<ASpaceCraftDoor>(OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsObject("CentralDoor"))->IsOpen)
	{
		return true;
	}
	return false;
}