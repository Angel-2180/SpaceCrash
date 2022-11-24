// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayDetectionNoise.h"
#include "AIController.h"
#include "AlienController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Components/AudioComponent.h"

EBTNodeResult::Type UPlayDetectionNoise::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBComp = OwnerComp.GetAIOwner()->GetBlackboardComponent();
	AAlienController* Alien = Cast<AAlienController>(BBComp->GetValueAsObject("SelfActor"));
	Alien->AudioPlayerDetection->SetSound(Alien->DetectionSounds[rand() % Alien->DetectionSounds.Num()]);
	Alien->AudioPlayerDetection->Play();
	return EBTNodeResult::Succeeded;
}