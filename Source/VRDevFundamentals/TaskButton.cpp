// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskButton.h"
#include "IndexCollision.h"

// Sets default values
ATaskButton::ATaskButton()
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
void ATaskButton::BeginPlay()
{
	Super::BeginPlay();
	
	ButtonMesh->OnComponentBeginOverlap.AddDynamic(this, &ATaskButton::ButtonBeginOverlap);
	ButtonMesh->OnComponentEndOverlap.AddDynamic(this, &ATaskButton::ButtonEndOverlap);
}

// Called every frame
void ATaskButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATaskButton::ButtonBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bDeactivateInteraction)
	{
		AIndexCollision* Finger = Cast<AIndexCollision>(OtherActor);
		if (Finger != nullptr)
		{
			Index = Finger;
			if (Index->SphereCollider->IsActive())
			{
				bActive = !bActive;
				if (bActive)
				{
					OverlappedComp->SetMaterial(1, SelectedMat);
					bPlayActiveSound = true;
				}
				else
				{
					OverlappedComp->SetMaterial(1, NormalMat);
					bPlayDeactiveSound = true;
				}
			}
		}
	}
}

void ATaskButton::ButtonEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	/*AIndexCollision* Finger = Cast<AIndexCollision>(OtherActor);
	if (Finger != nullptr)
	{
		if (Finger->SphereCollider->IsActive())
		{
			Index = nullptr;
			OverlappedComp->SetMaterial(0, NormalMat);
		}
	}*/
}