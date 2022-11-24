// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

void AGM_LobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (GameState)
	{
		int32 NumberOfPlayer = GameState.Get()->PlayerArray.Num();

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Purple, FString::Printf(TEXT("Players in game: %d"), NumberOfPlayer));

			APlayerState* PlayerState = NewPlayer->GetPlayerState<APlayerState>();
			if (PlayerState)
			{
				FString PlayerName = PlayerState->GetPlayerName();
				GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Cyan, FString::Printf(TEXT("%s has joined the game!"), *PlayerName));
			}
		}
	}
}

void AGM_LobbyGameMode::Logout(AController* Exitting)
{
	Super::Logout(Exitting);
	APlayerState* PlayerState = Exitting->GetPlayerState<APlayerState>();
	if (PlayerState)
	{
		int32 NumberOfPlayer = GameState.Get()->PlayerArray.Num();
		GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Purple, FString::Printf(TEXT("Players in game: %d"), NumberOfPlayer - 1));

		FString PlayerName = PlayerState->GetPlayerName();
		GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Cyan, FString::Printf(TEXT("%s has exited the game!"), *PlayerName));
	}
}