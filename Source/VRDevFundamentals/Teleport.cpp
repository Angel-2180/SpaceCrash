// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleport.h"
#include "AlienController.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "AlienPatrolPoint.h"
#include "VRPawn.h"
#include "Components/AudioComponent.h"

EBTNodeResult::Type UTeleport::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBComp = OwnerComp.GetAIOwner()->GetBlackboardComponent();
	AAlienController* Alien = Cast<AAlienController>(BBComp->GetValueAsObject("SelfActor"));
	Alien->SetActorLocation(FVector(8716.858952, -17625.720229, 58.955473));
	Alien->SetActorRotation(FRotator(0, 256.914076, 0));
	return EBTNodeResult::Succeeded;
}