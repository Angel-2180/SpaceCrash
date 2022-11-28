// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeAlienSpeed.h"
#include "AIController.h"
#include "AlienController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UChangeAlienSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BBComp = OwnerComp.GetAIOwner()->GetBlackboardComponent();
	AAlienController* Alien = Cast<AAlienController>(BBComp->GetValueAsObject("SelfActor"));
	Alien->GetCharacterMovement()->MaxWalkSpeed = BBComp->GetValueAsInt("WalkSpeed");
	return EBTNodeResult::Succeeded;
}