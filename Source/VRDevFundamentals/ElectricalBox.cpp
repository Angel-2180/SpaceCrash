// Fill out your copyright notice in the Description page of Project Settings.

#include "ElectricalBox.h"
#include "Lever.h"

#include "ColoredWire.h"

// Sets default values
AElectricalBox::AElectricalBox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Panel = CreateDefaultSubobject<USceneComponent>(TEXT("Panel"));
	RootComponent = Panel;
	PanelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PanelMesh"));
	PanelMesh->SetupAttachment(Panel);
}

// Called when the game starts or when spawned
void AElectricalBox::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = Cast<USpaceCrashGameInstance>(GetGameInstance());

	TArray<UActorComponent*> WireSocketArray = GetComponentsByClass(UElectricalSocketComponent::StaticClass());
	for (int i = 0; i < WireSocketArray.Num(); i++)
	{
		UElectricalSocketComponent* Socket = Cast<UElectricalSocketComponent>(WireSocketArray[i]);
		if (Socket)
		{
			Socket->SetMaterial(0, MatArray[i]);

			WireSockets.Add(Socket);
		}
	}
}

// Called every frame
void AElectricalBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (WireSockets[0]->Linked && WireSockets[1]->Linked && WireSockets[2]->Linked && WireSockets[3]->Linked && Lever->bLeverDown && GameInstance->bFirstPuzzleIsDone)
	{*/
	if (GameInstance)
	{
		if (GameInstance->bFirstPuzzleIsDone)
		{
			if (WireSockets[1]->Linked)
			{
				if (WireSockets[2]->Linked)
				{
					if (WireSockets[3]->Linked)
					{
						if (Lever->bLeverDown)
						{
							GameInstance->bSecondPuzzleIsDone = true;
						}
					}
				}
			}
		}
	}
}