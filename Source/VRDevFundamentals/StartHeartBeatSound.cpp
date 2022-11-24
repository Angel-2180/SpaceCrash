// Fill out your copyright notice in the Description page of Project Settings.


#include "StartHeartBeatSound.h"
#include "AIController.h"
#include "AlienController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "VRPawn.h"
#include "Components/AudioComponent.h"

EBTNodeResult::Type UStartHeartBeatSound::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBComp = OwnerComp.GetAIOwner()->GetBlackboardComponent();
	AVRPawn* Player = Cast<AVRPawn>(BBComp->GetValueAsObject("Player"));
	Player->HeartBeatSound->Play();
	return EBTNodeResult::Succeeded;
}