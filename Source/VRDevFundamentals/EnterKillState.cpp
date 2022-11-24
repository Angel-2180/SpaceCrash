// Fill out your copyright notice in the Description page of Project Settings.


#include "EnterKillState.h"
#include "AlienController.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "AlienPatrolPoint.h"

EBTNodeResult::Type UEnterKillState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBComp = OwnerComp.GetAIOwner()->GetBlackboardComponent();
	BBComp->SetValueAsEnum("State", 2);
	return EBTNodeResult::Succeeded;
}