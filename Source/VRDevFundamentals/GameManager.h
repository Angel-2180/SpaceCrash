// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ElectricalBox.h"
#include "SImonPyramid.h"
#include "PasscodePuzzle.h"
#include "CableLinkPuzzle.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

UCLASS()
class VRDEVFUNDAMENTALS_API AGameManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGameManager();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		AElectricalBox* ElectricalBox;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		ASimonPyramid* SimonPyramid;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		APasscodePuzzle* PasscodePuzzle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		ACableLinkPuzzle* CableLinkPuzzle;
};
