// Fill out your copyright notice in the Description page of Project Settings.


#include "AlienController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AlienPatrolPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CentralCorridorEventTrigger.h"
#include "SideCorridorEventTrigger.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "SpaceCraftDoor.h"	
#include "Kismet/KismetMathLibrary.h"
#include "VRPawn.h"
#include "MotionControllerComponent.h"
#include "HandTriggers.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"

// Sets default values
AAlienController::AAlienController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
}

// Called when the game starts or when spawned
void AAlienController::BeginPlay()
{
	Super::BeginPlay();

	UBlackboardComponent* BlackBoardComponent = UAIBlueprintHelperLibrary::GetBlackboard(this);
	BlackBoardComponent->SetValueAsObject("CentralDoor", Cast<UObject>(CentralDoor));
	BlackBoardComponent->SetValueAsObject("RightDoor", Cast<UObject>(RightDoor));
	BlackBoardComponent->SetValueAsObject("LeftDoor", Cast<UObject>(LeftDoor));
	BlackBoardComponent->SetValueAsFloat("MinTimerBeforeRandomSound", MinTimerBeforeRandomSound);
	BlackBoardComponent->SetValueAsFloat("MaxTimerBeforeRandomSound", MaxTimerBeforeRandomSound);
	BlackBoardComponent->SetValueAsInt("RunSpeed", RunSpeed);
	BlackBoardComponent->SetValueAsInt("WalkSpeed", WalkSpeed);
	BlackBoardComponent->SetValueAsBool("AlienActivated", AlienActivated);
}

void AAlienController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	TArray<AActor*> ActorArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAlienPatrolPoint::StaticClass(), ActorArray);
	for (int i = 0; i < ActorArray.Num(); i++)
	{
		PatrolPointList.Add(Cast<AAlienPatrolPoint>(ActorArray[i]));
	}
}

// Called every frame
void AAlienController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAlienController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAlienController::UpdateAIWithSound(UBlackboardComponent* BlackBoardComponent)
{
	if (BlackBoardComponent->GetValueAsEnum("State") == 0 && AttackCooldownTimer > AttackCooldown)
	{
		BlackBoardComponent->SetValueAsEnum("State", 1);
		float CentralDist = this->GetDistanceTo(Cast<ACentralCorridorEventTrigger>(BlackBoardComponent->GetValueAsObject("CenteralCorridorEvent")));
		float LeftDist = this->GetDistanceTo(Cast<ASideCorridorEventTrigger>(BlackBoardComponent->GetValueAsObject("LeftSideCorridorEvent")));
		float RightDist = this->GetDistanceTo(Cast<ASideCorridorEventTrigger>(BlackBoardComponent->GetValueAsObject("RightSideCorridorEvent")));

		if (CentralDist < LeftDist && CentralDist < RightDist)
		{
			BlackBoardComponent->SetValueAsEnum("CorridorEventToGo", 0);
		}

		else if (LeftDist < CentralDist && LeftDist < RightDist)
		{
			BlackBoardComponent->SetValueAsEnum("CorridorEventToGo", 1);
		}

		else if (RightDist < CentralDist && RightDist < LeftDist)
		{
			BlackBoardComponent->SetValueAsEnum("CorridorEventToGo", 2);
		}
	}

	if (SurvivalMinigameActive)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, "HearedPlayer");
		BlackBoardComponent->SetValueAsBool("KillPlayer", true);
	}
}

void AAlienController::UpdatePlayerDetection(class UCameraComponent* PlayerCamera)
{
	if (SurvivalMinigameActive)
	{
		UBlackboardComponent* BBComp = UAIBlueprintHelperLibrary::GetBlackboard(this);
		AVRPawn* Player = Cast<AVRPawn>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		/*FVector FowardLookAt = UKismetMathLibrary::GetForwardVector(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Player->GetActorLocation()));
		FVector FowardPlayer = UKismetMathLibrary::GetForwardVector(PlayerCamera->GetComponentRotation());
		float DotProduct = UKismetMathLibrary::Dot_VectorVector(FowardLookAt, FowardPlayer) * -1.0f;
		if (DotProduct >= 0.99f)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, "PlayerLooking");
			BBComp->SetValueAsBool("KillPlayer", true);
		}*/

		if (Player->LightOn)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, "PlayerFlahlightOn");
			BBComp->SetValueAsBool("KillPlayer", true);
		}

		if (LeftHand)
		{
			FVector LeftHandLocation = LeftHand->GetComponentLocation();
			if (LeftHandLocation.X > LeftHandStartingLocation.X + HandDetectionLength || LeftHandLocation.X < LeftHandStartingLocation.X - HandDetectionLength)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, "PlayerMovedInXPos");
				BBComp->SetValueAsBool("KillPlayer", true);
				return;
			}

			if (LeftHandLocation.Y > LeftHandStartingLocation.Y + HandDetectionLength || LeftHandLocation.Y < LeftHandStartingLocation.Y - HandDetectionLength)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, "PlayerMovedInYPos");
				BBComp->SetValueAsBool("KillPlayer", true);
				return;
			}

			if (LeftHandLocation.Z > LeftHandStartingLocation.Z + HandDetectionLength || LeftHandLocation.Z < LeftHandStartingLocation.Z - HandDetectionLength)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, "PlayerMovedInZPos");
				BBComp->SetValueAsBool("KillPlayer", true);
				return;
			}
		}
	}
}

void AAlienController::EnterSurvivalMinigame()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, "EnteredSurvivalMinigame");
	SurvivalMinigameActive = true;
	AVRPawn* Player = Cast<AVRPawn>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	LeftHand = Player->LeftHandMotionController;
	LeftHandStartingLocation = LeftHand->GetComponentLocation();
	RightHand = Player->RightHandMotionController;
	RightHandStartingLocation = RightHand->GetComponentLocation();
}

void AAlienController::QuitSurvivalMinigame()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, "QuitSurvivalMinigame");
	SurvivalMinigameActive = false;
	if (LeftHand)
	{
		LeftHand = nullptr;
	}

	if (RightHand)
	{
		RightHand = nullptr;
	}
}

void AAlienController::KillPlayer()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, "PlayerKilled");
	UBlackboardComponent* BBComp = UAIBlueprintHelperLibrary::GetBlackboard(this);
	BBComp->SetValueAsEnum("State", 0);
	BBComp->SetValueAsFloat("AttackCooldown", 0);
	if (SurvivalMinigameActive)
	{
		QuitSurvivalMinigame();
	}

	UGameplayStatics::OpenLevel(GetWorld(), "ScreamerScene");
}