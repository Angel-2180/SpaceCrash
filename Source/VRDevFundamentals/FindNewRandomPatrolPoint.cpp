// Fill out your copyright notice in the Description page of Project Settings.


#include "FindNewRandomPatrolPoint.h"
#include "AlienController.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "AlienPatrolPoint.h"

EBTNodeResult::Type UFindNewRandomPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBComp = OwnerComp.GetAIOwner()->GetBlackboardComponent();
	AAlienController* Alien = Cast<AAlienController>(BBComp->GetValueAsObject("SelfActor"));
	float RandNum = FMath::RandRange(0, Alien->PatrolPointList.Num() - 1);
	BBComp->SetValueAsVector("RandomPatrolPoint", Alien->PatrolPointList[RandNum]->GetActorLocation());
	return EBTNodeResult::Succeeded;
}