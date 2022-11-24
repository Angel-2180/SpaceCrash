// Fill out your copyright notice in the Description page of Project Settings.


#include "Wire.h"
#include "CableComponent.h"

// Sets default values for this component's properties
UWire::UWire()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	WireRoot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WireRoot"));
	WireStart = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WireStart"));
	WireStart->SetupAttachment(WireRoot);
	WireSocket = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WireEnd"));
	WireSocket->SetupAttachment(WireRoot);
	Wire = CreateDefaultSubobject<UCableComponent>(TEXT("WireCable"));
	Wire->SetupAttachment(WireRoot);
}


// Called when the game starts
void UWire::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWire::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

