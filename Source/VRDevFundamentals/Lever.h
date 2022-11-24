// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h
#include "SpaceCrashGameInstance.h"
#include "Lever.generated.h"

UCLASS()
class VRDEVFUNDAMENTALS_API ALever : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALever();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bLeverDown = false;

	UFUNCTION(BlueprintCallable)
		void UpdateLeverRotation(USceneComponent* Lever, class USphereComponent* OutterSphere, class USphereComponent* InnerSphere, class ULeverGrabbable* LeverGrabbable);

	UFUNCTION(BlueprintCallable)
		bool IsLeverActivated(USceneComponent* Lever);

	float Timer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpaceCrashGameInstance* GameInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bPuzzleStarted;
};
