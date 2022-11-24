// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayCentralDoorFootStep.h"
#include "AIController.h"
#include "AlienController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Components/AudioComponent.h"

EBTNodeResult::Type UPlayCentralDoorFootStep::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBComp = OwnerComp.GetAIOwner()->GetBlackboardComponent();
	AAlienController* Alien = Cast<AAlienController>(BBComp->GetValueAsObject("SelfActor"));
	if (!Alien->AudioPlayerFeet->IsPlaying())
	{
		Alien->AudioPlayerFeet->SetSound(Alien->CentralDoorsFeetSounds[rand() % Alien->CentralDoorsFeetSounds.Num()]);
		Alien->AudioPlayerFeet->Play();
		Alien->AudioPlayerBreath->Play();
	}
	return EBTNodeResult::Succeeded;
}