// Fill out your copyright notice in the Description page of Project Settings.


#include "WireActor.h"
#include "CableComponent.h"
#include "GrabbableComponent.h"
#include "WireSocket.h"

// Sets default values
AWireActor::AWireActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WireStart = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WireStart"));
	RootComponent = WireStart;
}

// Called when the game starts or when spawned
void AWireActor::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<UActorComponent*> GrabbableComponentArray = GetComponentsByClass(UGrabbableComponent::StaticClass());
	for (int i = 0; i < GrabbableComponentArray.Num(); i++)
	{
		UGrabbableComponent* GrabbableComponent = Cast<UGrabbableComponent>(GrabbableComponentArray[i]);
		if (GrabbableComponent != nullptr)
		{
			WireEnd = GrabbableComponent;
			WireEnd->Value = this->Value;
		}
	}

	WireEnd->PreviousParent = WireStart;

	TArray<UActorComponent*> CableArray = GetComponentsByClass(UCableComponent::StaticClass());
	for (int32 i = 0; i < CableArray.Num(); i++)
	{
		UCableComponent* TestWireCast = Cast<UCableComponent>(CableArray[i]);
		if (TestWireCast != nullptr)
			Wire = TestWireCast;
	}

	WireEnd->OnComponentBeginOverlap.AddDynamic(this, &AWireActor::WireSocketBeginOverlap);
	WireEnd->OnComponentEndOverlap.AddDynamic(this, &AWireActor::WireSocketEndOverlap);
}

// Called every frame
void AWireActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTaskCompleted)
	{
		WireEnd->bTaskCompleted = true;
	}
}

void AWireActor::WireSocketBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UWireSocket* OverlappedCompCast = Cast<UWireSocket>(OtherComp);
	if (OverlappedCompCast != nullptr)
	{
		if(OtherComp->GetAttachChildren().Num() == 0)
			WireEnd->LastSocketTouched = OverlappedCompCast;
	}
}

void AWireActor::WireSocketEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UWireSocket* OverlappedCompCast = Cast<UWireSocket>(OtherComp);
	if (OverlappedCompCast != nullptr)
	{
		WireEnd->LastSocketTouched = nullptr;;
	}
}

