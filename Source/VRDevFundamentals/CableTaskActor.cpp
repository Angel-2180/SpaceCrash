// Fill out your copyright notice in the Description page of Project Settings.

#include "CableTaskActor.h"
#include "CableTaskCollider.h"
#include "SpaceCrashGameInstance.h"
#include "CableTaskGrabbableComponent.h"

// Sets default values
ACableTaskActor::ACableTaskActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WireStart = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WireStart"));
	RootComponent = WireStart;
}

// Called when the game starts or when spawned
void ACableTaskActor::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = Cast<USpaceCrashGameInstance>(GetGameInstance());
	TArray<UActorComponent*> GrabbableComponentArray = GetComponentsByClass(UCableTaskGrabbableComponent::StaticClass());
	for (int i = 0; i < GrabbableComponentArray.Num(); i++)
	{
		UCableTaskGrabbableComponent* GrabbableComponent = Cast<UCableTaskGrabbableComponent>(GrabbableComponentArray[i]);
		if (GrabbableComponent != nullptr)
		{
			WireEnd = GrabbableComponent;
		}
	}

	WireEnd->PreviousParent = WireStart;

	WireEnd->OnComponentBeginOverlap.AddDynamic(this, &ACableTaskActor::WireSocketBeginOverlap);
	WireEnd->OnComponentEndOverlap.AddDynamic(this, &ACableTaskActor::WireSocketEndOverlap);
}

// Called every frame
void ACableTaskActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (WireEnd->bIsLinked && !bIsDone)
	{
		bIsDone = true;
		GameInstance->bThirdPuzzleIsDone = true;
		SetActorEnableCollision(false);
		SetActorTickEnabled(false);
	}
}

void ACableTaskActor::WireSocketBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACableTaskCollider* OverlappedCompCast = Cast<ACableTaskCollider>(OtherActor);
	if (OverlappedCompCast != nullptr)
	{
		WireEnd->LastSocketTouched = OverlappedCompCast;
	}
}

void ACableTaskActor::WireSocketEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACableTaskCollider* OverlappedCompCast = Cast<ACableTaskCollider>(OtherActor);
	if (OverlappedCompCast != nullptr)
	{
		WireEnd->LastSocketTouched = nullptr;;
	}
}