// Fill out your copyright notice in the Description page of Project Settings.


#include "AlienAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CentralCorridorEventTrigger.h"
#include "SideCorridorEventTrigger.h"
#include "AlienController.h"
#include "AlienPatrolPoint.h"
#include "Kismet/GameplayStatics.h"
#include "CockpitCheckpoint.h"
#include "VRPawn.h"

AAlienAIController::AAlienAIController(FObjectInitializer const& object_initializer)
{
	behavior_treeComponent = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	blackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
}

void AAlienAIController::BeginPlay()
{
	Super::BeginPlay();
	blackboard->SetValueAsObject("SelfActor", this->GetPawn());

	TArray<AActor*> ActorArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACentralCorridorEventTrigger::StaticClass(), ActorArray);
	blackboard->SetValueAsObject("CenteralCorridorEvent", ActorArray[0]);

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASideCorridorEventTrigger::StaticClass(), ActorArray);
	if (ActorArray[0]->GetActorLocation().Y < ActorArray[1]->GetActorLocation().Y)
	{
		blackboard->SetValueAsObject("LeftSideCorridorEvent", ActorArray[0]);
		blackboard->SetValueAsObject("RightSideCorridorEvent", ActorArray[1]);
	}
	else
	{
		blackboard->SetValueAsObject("LeftSideCorridorEvent", ActorArray[1]);
		blackboard->SetValueAsObject("RightSideCorridorEvent", ActorArray[0]);
	}

	blackboard->SetValueAsFloat("TimerForRandomSound", 0);
	blackboard->SetValueAsFloat("NewTimeForRandomSound", FMath::RandRange(blackboard->GetValueAsFloat("MinTimerBeforeRandomSound"), blackboard->GetValueAsFloat("MaxTimerBeforeRandomSound")));

	blackboard->SetValueAsFloat("AttackCooldown", 100);

	blackboard->SetValueAsBool("KillPlayer", false);

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACockpitCheckpoint::StaticClass(), ActorArray);
	blackboard->SetValueAsObject("Cockpit", ActorArray[0]);

	blackboard->SetValueAsObject("Player", Cast<AVRPawn>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)));

	AAlienController* Alien = Cast<AAlienController>(this->GetPawn());
	float RandNum = FMath::RandRange(0, Alien->PatrolPointList.Num() - 1);
	blackboard->SetValueAsVector("RandomPatrolPoint", Alien->PatrolPointList[RandNum]->GetActorLocation());

	RunBehaviorTree(btree);
	behavior_treeComponent->StartTree(*btree);
}

void AAlienAIController::OnPossess(APawn* const pawn)
{
	Super::OnPossess(pawn);
	if (blackboard)
	{
		blackboard->InitializeBlackboard(*btree->BlackboardAsset);
	}
}
