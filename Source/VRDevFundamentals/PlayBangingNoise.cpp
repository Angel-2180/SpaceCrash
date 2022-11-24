// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayBangingNoise.h"
#include "AIController.h"
#include "AlienController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Components/AudioComponent.h"

EBTNodeResult::Type UPlayBangingNoise::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBComp = OwnerComp.GetAIOwner()->GetBlackboardComponent();
	AAlienController* Alien = Cast<AAlienController>(BBComp->GetValueAsObject("SelfActor"));
	Alien->AudioPlayerDoorBanging->SetSound(Alien->DoorBangingSounds[rand() % Alien->DoorBangingSounds.Num()]);
	Alien->AudioPlayerDoorBanging->Play();
	return EBTNodeResult::Succeeded;
}