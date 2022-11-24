// Fill out your copyright notice in the Description page of Project Settings.

#include "ColoredWire.h"

// Sets default values
AColoredWire::AColoredWire()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WireStart = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WireStart"));
	RootComponent = WireStart;
}

// Called when the game starts or when spawned
void AColoredWire::BeginPlay()
{
	Super::BeginPlay();

	TArray<UActorComponent*> CableArray = GetComponentsByClass(UCableComponent::StaticClass());
	for (int32 i = 0; i < CableArray.Num(); i++)
	{
		UCableComponent* TestWireCast = Cast<UCableComponent>(CableArray[i]);
		if (TestWireCast != nullptr)
			Wire = TestWireCast;
	}

	TArray<UActorComponent*> GrabbableComponentArray = GetComponentsByClass(UElectricalCableGrabComponent::StaticClass());

	for (int i = 0; i < GrabbableComponentArray.Num(); i++)
	{
		UElectricalCableGrabComponent* GrabbableComponent = Cast<UElectricalCableGrabComponent>(GrabbableComponentArray[i]);
		if (GrabbableComponent != nullptr)
		{
			WireEnd = GrabbableComponent;
		}
		GrabbableComponent->OnCableLinked.AddDynamic(this, &AColoredWire::OnConnection);
	}
	WireEnd->PreviousParent = WireStart;
	WireEnd->OnComponentBeginOverlap.AddDynamic(this, &AColoredWire::WireSocketBeginOverlap);
	WireEnd->OnComponentEndOverlap.AddDynamic(this, &AColoredWire::WireSocketEndOverlap);
}

// Called every frame
void AColoredWire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AColoredWire::WireSocketBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UElectricalSocketComponent* OverlappedCompCast = Cast<UElectricalSocketComponent>(OtherComp);
	GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Blue, TEXT("BeginOverlapOfCable"));
	if (OverlappedCompCast != nullptr)
	{
		WireEnd->LastSocketTouched = OverlappedCompCast;
	}
}

void AColoredWire::WireSocketEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UElectricalSocketComponent* OverlappedCompCast = Cast<UElectricalSocketComponent>(OtherComp);
	if (OverlappedCompCast != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Blue, TEXT("LastSocket Null"));
		WireEnd->LastSocketTouched = nullptr;
	}
}

void AColoredWire::OnConnection()
{
	NbrOfWiresConnected;
	NbrOfWiresConnected++;
	if (NbrOfWiresConnected == 4)
	{
		OnCompleteEvent.Broadcast();
	}
}