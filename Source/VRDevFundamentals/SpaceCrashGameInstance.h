// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SpaceCrashGameInstance.generated.h"

/**
 *
 */
UCLASS()
class VRDEVFUNDAMENTALS_API USpaceCrashGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool bFirstPuzzleIsDone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool bSecondPuzzleIsDone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool bThirdPuzzleIsDone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
		bool bFourthPuzzleIsDone;
};
