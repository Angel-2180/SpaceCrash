// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorEngine.h"
#include "SpaceCraftDoor.h"

// Sets default values
ADoorEngine::ADoorEngine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoorEngine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoorEngine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LeftDoor)
	{
		if (!LeftDoor->IsOpen)
		{
			TotalEnergyRemaining -= EnergyCostToKeepDoorClosedPerSecond * DeltaTime;
		}
	}

	if (RightDoor)
	{
		if (!RightDoor->IsOpen)
		{
			TotalEnergyRemaining -= EnergyCostToKeepDoorClosedPerSecond * DeltaTime;
		}
	}

	if (CentralDoor)
	{
		if (!CentralDoor->IsOpen)
		{
			TotalEnergyRemaining -= EnergyCostToKeepDoorClosedPerSecond * DeltaTime;
		}
	}

	if (LeftDoor->IsOpen && RightDoor->IsOpen && CentralDoor->IsOpen && !EngineShutdown)
	{
		TotalEnergyRemaining += EnergyRecoveryPerSecond * DeltaTime;
	}

	if (TotalEnergyRemaining < 0)
	{
		if (!EngineShutdown)
			PlayEngineShutDownSound = true;

		EngineShutdown = true;

		if (!LeftDoor->IsOpen)
			LeftDoor->OpenDoor();

		if (!RightDoor->IsOpen)
			RightDoor->OpenDoor();

		if (!CentralDoor->IsOpen)
			CentralDoor->OpenDoor();
	}

	if (EngineShutdown)
	{
		TimerBeforeEngineBackOnline += DeltaTime;
		if (TimerBeforeEngineBackOnline >= TimeBeforeEngineBackOnlineInSec)
		{
			PlayEngineBackUpSound = true;
			TotalEnergyRemaining = 100;
			TimerBeforeEngineBackOnline = 0;
			EngineShutdown = false;
		}
	}
}

