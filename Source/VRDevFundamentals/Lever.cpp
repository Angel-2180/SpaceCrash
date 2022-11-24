// Fill out your copyright notice in the Description page of Project Settings.

#include "Lever.h"
#include "Components/SphereComponent.h"
#include "LeverGrabbable.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ALever::ALever()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALever::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = Cast<USpaceCrashGameInstance>(GetGameInstance());
}

// Called every frame
void ALever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GameInstance->bFirstPuzzleIsDone && !GameInstance->bSecondPuzzleIsDone)
	{
		Timer += DeltaTime;
		if (Timer >= 3)
		{
			if (bPuzzleStarted)
			{
				this->SetActorEnableCollision(true);
			}
		}
	}
}

void ALever::UpdateLeverRotation(USceneComponent* Lever, class USphereComponent* OutterSphere, class USphereComponent* InnerSphere, ULeverGrabbable* LeverGrabbable)
{
	if (!bLeverDown)
	{
		FVector LeverGrabbableLocation = LeverGrabbable->GetComponentLocation();
		FVector OutterSphereLocation = OutterSphere->GetComponentLocation();
		FVector InnerSphereLocation = InnerSphere->GetComponentLocation();
		FVector LeverLocation = Lever->GetComponentLocation();
		FRotator LeverRotation = Lever->GetComponentRotation();
		FRotator NewLookAtRotation = UKismetMathLibrary::FindLookAtRotation(LeverLocation, LeverGrabbableLocation);
		float NewYRotation = UKismetMathLibrary::FClamp(NewLookAtRotation.Pitch, -60, 60);
		FRotator NewRotation = FRotator(NewYRotation, LeverRotation.Yaw, LeverRotation.Roll);
		Lever->SetWorldRotation(NewRotation);

		if (UKismetMathLibrary::Vector_Distance(LeverGrabbableLocation, OutterSphereLocation) >= OutterSphere->GetScaledSphereRadius())
		{
			LeverGrabbable->DropLever();
		}

		if (UKismetMathLibrary::Vector_Distance(LeverGrabbableLocation, InnerSphereLocation) <= InnerSphere->GetScaledSphereRadius())
		{
			LeverGrabbable->DropLever();
		}
	}
}

bool ALever::IsLeverActivated(USceneComponent* Lever)
{
	FRotator LeverRotation = Lever->GetComponentRotation();
	if (LeverRotation.Pitch <= -55 && GameInstance->bFirstPuzzleIsDone)
	{
		FRotator NewRotation = FRotator(-60, LeverRotation.Yaw, LeverRotation.Roll);
		Lever->SetWorldRotation(NewRotation);
		bLeverDown = true;
		GameInstance->bSecondPuzzleIsDone = true;
		this->SetActorTickEnabled(false);
		this->SetActorEnableCollision(false);
		return true;
	}
	return false;
}