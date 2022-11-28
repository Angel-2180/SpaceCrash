// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportLeft.h"
#include "AlienController.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "AlienPatrolPoint.h"
#include "VRPawn.h"
#include "Components/AudioComponent.h"

EBTNodeResult::Type UTeleportLeft::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBComp = OwnerComp.GetAIOwner()->GetBlackboardComponent();
	AAlienController* Alien = Cast<AAlienController>(BBComp->GetValueAsObject("SelfActor"));
	Alien->SetActorLocation(FVector(8732.252641, -18056.407494, 58.955473));
	Alien->SetActorRotation(FRotator(0, -257.481388, 0));
	return EBTNodeResult::Succeeded;
}