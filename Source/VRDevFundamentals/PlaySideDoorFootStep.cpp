// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaySideDoorFootStep.h"
#include "AIController.h"
#include "AlienController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Components/AudioComponent.h"

EBTNodeResult::Type UPlaySideDoorFootStep::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBComp = OwnerComp.GetAIOwner()->GetBlackboardComponent();
	AAlienController* Alien = Cast<AAlienController>(BBComp->GetValueAsObject("SelfActor"));
	if (!Alien->AudioPlayerFeet->IsPlaying())
	{
		Alien->AudioPlayerFeet->SetSound(Alien->SideDoorsFeetSounds[rand() % Alien->SideDoorsFeetSounds.Num()]);
		Alien->AudioPlayerFeet->Play();
		Alien->AudioPlayerBreath->Play();
	}
	return EBTNodeResult::Succeeded;
}