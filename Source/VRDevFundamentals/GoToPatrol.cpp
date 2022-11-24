// Fill out your copyright notice in the Description page of Project Settings.


#include "GoToPatrol.h"
#include "AlienController.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "AlienPatrolPoint.h"
#include "VRPawn.h"
#include "Components/AudioComponent.h"

EBTNodeResult::Type UGoToPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBComp = OwnerComp.GetAIOwner()->GetBlackboardComponent();
	BBComp->SetValueAsEnum("State", 0);
	BBComp->SetValueAsFloat("AttackCooldown", 0);
	AAlienController* Alien = Cast<AAlienController>(BBComp->GetValueAsObject("SelfActor"));
	if (Alien->SurvivalMinigameActive)
	{
		Alien->QuitSurvivalMinigame();
	}
	AVRPawn* Player = Cast<AVRPawn>(BBComp->GetValueAsObject("Player"));
	Player->HeartBeatSound->Stop();
	return EBTNodeResult::Succeeded;
}