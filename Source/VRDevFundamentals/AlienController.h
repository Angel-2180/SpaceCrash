// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AlienController.generated.h"

UCLASS()
class VRDEVFUNDAMENTALS_API AAlienController : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAlienController();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UAIPerceptionComponent* AIPerception;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class ASpaceCraftDoor* CentralDoor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class ASpaceCraftDoor* LeftDoor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class ASpaceCraftDoor* RightDoor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float AttackCooldown;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<USoundWave*> DetectionSounds;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<USoundWave*>DoorBangingSounds;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<USoundWave*> RandomSounds;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<USoundWave*> SideDoorsFeetSounds;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<USoundWave*> CentralDoorsFeetSounds;

	UPROPERTY(BlueprintReadWrite)
		UAudioComponent* AudioPlayerDetection;

	UPROPERTY(BlueprintReadWrite)
		UAudioComponent* AudioPlayerDoorBanging;

	UPROPERTY(BlueprintReadWrite)
		UAudioComponent* AudioPlayerRandomNoise;

	UPROPERTY(BlueprintReadWrite)
		UAudioComponent* AudioPlayerFeet;

	UPROPERTY(BlueprintReadWrite)
		UAudioComponent* AudioPlayerBreath;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float HandDetectionLength;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float MinTimerBeforeRandomSound;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float MaxTimerBeforeRandomSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int RunSpeed = 400;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int WalkSpeed = 135;

	float AttackCooldownTimer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool AlienActivated = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool SurvivalMinigameActive = false;

	TArray<class AAlienPatrolPoint*> PatrolPointList;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

private:

	class UMotionControllerComponent* LeftHand;
	class UMotionControllerComponent* RightHand;
	FVector LeftHandStartingLocation;
	FVector RightHandStartingLocation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void UpdateAIWithSound(class UBlackboardComponent* BlackBoardComponent);

	UFUNCTION(BlueprintCallable)
		void UpdatePlayerDetection(class UCameraComponent* PlayerCamera);

	UFUNCTION(BlueprintCallable)
	void EnterSurvivalMinigame();

	UFUNCTION(BlueprintCallable)
	void QuitSurvivalMinigame();

	void KillPlayer();
};
