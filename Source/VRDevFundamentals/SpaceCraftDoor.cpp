// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceCraftDoor.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ASpaceCraftDoor::ASpaceCraftDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ASpaceCraftDoor::BeginPlay()
{
	Super::BeginPlay();
	ClosedLocation = DoorMesh->GetRelativeLocation();
	BaseRotation = DoorMesh->GetRelativeRotation();
	OpenDoor();
}

// Called every frame
void ASpaceCraftDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpaceCraftDoor::OpenDoor()
{
	IsOpen = true;
	//if (DoorFinishedMoving)
	//{
		//DoorFinishedMoving = false;
	PlayDoorOpeningSound = true;
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = FName("OpenDoorFinished");
	LatentInfo.Linkage = 0;
	LatentInfo.UUID = 0;
	UKismetSystemLibrary::MoveComponentTo(DoorMesh, ClosedLocation + OpenedDistance, BaseRotation, true, true, TimeToOpenDoor, false, EMoveComponentAction::Move, LatentInfo);
	//}
	/*else
	{
		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this;
		LatentInfo.ExecutionFunction = FName("OpenDoorFinished");
		LatentInfo.Linkage = 0;
		LatentInfo.UUID = 0;
		UKismetSystemLibrary::MoveComponentTo(DoorMesh, ClosedLocation, BaseRotation, true, true, TimeToOpenDoor, false, EMoveComponentAction::Return, LatentInfo);
	}*/
}

void ASpaceCraftDoor::OpenDoorFinished()
{
	DoorFinishedMoving = true;
}

void ASpaceCraftDoor::CloseDoor()
{
	IsOpen = false;
	//if (DoorFinishedMoving)
	//{
		//DoorFinishedMoving = false;
	PlayDoorClosingSound = true;
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = FName("OpenDoorFinished");
	LatentInfo.Linkage = 0;
	LatentInfo.UUID = 0;
	UKismetSystemLibrary::MoveComponentTo(DoorMesh, ClosedLocation, BaseRotation, true, true, TimeToOpenDoor, false, EMoveComponentAction::Move, LatentInfo);
	//}
	/*else
	{
		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this;
		LatentInfo.ExecutionFunction = FName("OpenDoorFinished");
		LatentInfo.Linkage = 0;
		LatentInfo.UUID = 0;
		UKismetSystemLibrary::MoveComponentTo(DoorMesh, ClosedLocation + OpenedDistance, BaseRotation, true, true, TimeToOpenDoor, false, EMoveComponentAction::Return, LatentInfo);
	}*/
}
