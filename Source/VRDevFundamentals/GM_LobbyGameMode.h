// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM_LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class VRDEVFUNDAMENTALS_API AGM_LobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void Logout(AController* Exitting) override;
};
