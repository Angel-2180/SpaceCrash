// Fill out your copyright notice in the Description page of Project Settings.


#include "CableLinkPuzzle.h"
#include "WireActor.h"
#include "WireSocket.h"

// Sets default values
ACableLinkPuzzle::ACableLinkPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Panel = CreateDefaultSubobject<USceneComponent>(TEXT("Panel"));
	RootComponent = Panel;
}

// Called when the game starts or when spawned
void ACableLinkPuzzle::BeginPlay()
{
	Super::BeginPlay();
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

	for (int i = 0; i < WireSockets.Num(); i++)
	{
		this->TotalValue += WireSockets[i]->TotalValueOnThisSocket;
		WireSockets[i]->TotalValueOnThisSocket = 0;
	}
}

