// Fill out your copyright notice in the Description page of Project Settings.


#include "StartSurvivalMinigame.h"
#include "AlienController.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "AlienPatrolPoint.h"
#include "VRPawn.h"
#include "Components/AudioComponent.h"

EBTNodeResult::Type UStartSurvivalMinigame::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBComp = OwnerComp.GetAIOwner()->GetBlackboardComponent();
	AVRPawn* Player = Cast<AVRPawn>(BBComp->GetValueAsObject("Player"));
	Player->HeartBeatSound->Stop();
	AAlienController* Alien = Cast<AAlienController>(BBComp->GetValueAsObject("SelfActor"));
	Alien->KillPlayer();
	return EBTNodeResult::Succeeded;
}