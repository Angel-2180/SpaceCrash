// Fill out your copyright notice in the Description page of Project Settings.

#include "CableLinkPuzzle.h"
#include "WireActor.h"
#include "SpaceCrashGameInstance.h"
#include "WireSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/CompactBinary.h"

// Sets default values
ACableLinkPuzzle::ACableLinkPuzzle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Panel = CreateDefaultSubobject<USceneComponent>(TEXT("Panel"));
	RootComponent = Panel;
	LevelToLoad = "MainMenu";
}

// Called when the game starts or when spawned
void ACableLinkPuzzle::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = Cast<USpaceCrashGameInstance>(GetGameInstance());
	TArray<AActor*> ActorArray;
	GetAllChildActors(ActorArray);
	for (int i = 0; i < ActorArray.Num(); i++)
	{
		AWireActor* GrabbableActor = Cast<AWireActor>(ActorArray[i]);
		if (GrabbableActor != nullptr)
		{
			Wires.Add(GrabbableActor);
		}
	}
	bTaskCompleted = false;
	TotalValue = 0;
	TArray<UActorComponent*> WireSocketArray = GetComponentsByClass(UWireSocket::StaticClass());
	for (int i = 0; i < WireSocketArray.Num(); i++)
	{
		UWireSocket* WireSocketComponent = Cast<UWireSocket>(WireSocketArray[i]);
		if (WireSocketComponent != nullptr)
		{
			WireSockets.Add(WireSocketComponent);
		}
	}
}

// Called every frame
void ACableLinkPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GameInstance->bThirdPuzzleIsDone)
	{
		for (int i = 0; i < WireSockets.Num(); i++)
		{
			this->TotalValue += WireSockets[i]->TotalValueOnThisSocket;
			WireSockets[i]->TotalValueOnThisSocket = 0;
		}

		if (TotalValue == ValueToAchieve)
		{
			bTaskCompleted = true;
		}

		if (bTaskCompleted)
		{
			for (int i = 0; i < Wires.Num(); i++)
			{
				if (Wires[i] != nullptr)
					Wires[i]->bTaskCompleted = true;
			}
		}

		if (bTaskCompleted)
		{
			GameInstance->bEndGame = true;
			GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Cyan, TEXT("YOU WIN"));
			//quitGame
			if (LevelToLoad != "")
			{
				FLatentActionInfo LatentInfo;
				UGameplayStatics::LoadStreamLevel(this, LevelToLoad, true, true, LatentInfo);
			}
		}
	}
}