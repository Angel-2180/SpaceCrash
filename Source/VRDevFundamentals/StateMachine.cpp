// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine.h"
#include "AlienController.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "CentralCorridorEventTrigger.h"
#include "SideCorridorEventTrigger.h"
#include "Components/AudioComponent.h"

void UStateMachine::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* BBComp = OwnerComp.GetAIOwner()->GetBlackboardComponent();
	float RefreshedAttackCooldown = BBComp->GetValueAsFloat("AttackCooldown") + DeltaSeconds;
	BBComp->SetValueAsFloat("AttackCooldown", RefreshedAttackCooldown);
	float Timer = BBComp->GetValueAsFloat("TimerForRandomSound");
	AAlienController* Alien = Cast<AAlienController>(BBComp->GetValueAsObject("SelfActor"));

	if (BBComp->GetValueAsEnum("State") == 0)
	{
		Timer += DeltaSeconds;
		if (Timer >= BBComp->GetValueAsFloat("NewTimeForRandomSound"))
		{
			Alien->AudioPlayerRandomNoise->SetSound(Alien->RandomSounds[rand() % Alien->RandomSounds.Num()]);
			Alien->AudioPlayerRandomNoise->Play();
			BBComp->SetValueAsFloat("NewTimeForRandomSound", FMath::RandRange(BBComp->GetValueAsFloat("MinTimerBeforeRandomSound"), BBComp->GetValueAsFloat("MaxTimerBeforeRandomSound")));
			Timer = 0;
		}
	}

	BBComp->SetValueAsFloat("TimerForRandomSound", Timer);
	if (Alien)
	{
		Alien->AttackCooldownTimer = RefreshedAttackCooldown;
	}
}
