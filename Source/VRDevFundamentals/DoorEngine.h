// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorEngine.generated.h"

UCLASS()
class VRDEVFUNDAMENTALS_API ADoorEngine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorEngine();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class ASpaceCraftDoor* LeftDoor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class ASpaceCraftDoor* RightDoor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class ASpaceCraftDoor* CentralDoor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float EnergyCostToCloseDoor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float EnergyCostToKeepDoorClosedPerSecond;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float EnergyRecoveryPerSecond;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float TimeBeforeEngineBackOnlineInSec;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float TotalEnergyRemaining = 100;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool PlayEngineShutDownSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool PlayEngineBackUpSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	bool EngineShutdown = false;

	float TimerBeforeEngineBackOnline = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
