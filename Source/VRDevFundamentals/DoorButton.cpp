// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorButton.h"
#include "SpaceCraftDoor.h"
#include "IndexCollision.h"
#include "DoorEngine.h"

// Sets default values
ADoorButton::ADoorButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	BaseButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseButtonMesh"));
	BaseButtonMesh->SetupAttachment(Root);

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
	ButtonMesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ADoorButton::BeginPlay()
{
	Super::BeginPlay();

	ButtonMesh->OnComponentBeginOverlap.AddDynamic(this, &ADoorButton::ButtonBeginOverlap);
	ButtonMesh->OnComponentEndOverlap.AddDynamic(this, &ADoorButton::ButtonEndOverlap);
}

// Called every frame
void ADoorButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Index != nullptr)
	{
		if (!Index->SphereCollider->IsActive())
		{
			Index = nullptr;
			ButtonMesh->SetMaterial(0, NormalMat);
		}
	}

}

void ADoorButton::ButtonBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (DoorControlled->DoorFinishedMoving)
	{
		AIndexCollision* Finger = Cast<AIndexCollision>(OtherActor);
		if (Finger != nullptr)
		{
			Index = Finger;
			if (Index->SphereCollider->IsActive())
			{
				OverlappedComp->SetMaterial(0, SelectedMat);
				if (DoorControlled->IsOpen)
				{
					if (DoorEngine->TotalEnergyRemaining > DoorEngine->EnergyCostToCloseDoor)
					{
						DoorControlled->CloseDoor();
						DoorEngine->TotalEnergyRemaining -= DoorEngine->EnergyCostToCloseDoor;
					}
				}
				else
					DoorControlled->OpenDoor();
			}
		}
	}
}

void ADoorButton::ButtonEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AIndexCollision* Finger = Cast<AIndexCollision>(OtherActor);
	if (Finger != nullptr)
	{
		if (Finger->SphereCollider->IsActive())
		{
			Index = nullptr;
			OverlappedComp->SetMaterial(0, NormalMat);
		}
	}
}