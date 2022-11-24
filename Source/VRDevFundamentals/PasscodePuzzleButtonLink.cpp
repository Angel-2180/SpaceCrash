// Fill out your copyright notice in the Description page of Project Settings.


#include "PasscodePuzzleButtonLink.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"

// Sets default values
APasscodePuzzleButtonLink::APasscodePuzzleButtonLink()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	RootComponent = Spline;
	SplineMesh = CreateDefaultSubobject<USplineMeshComponent>(TEXT("SplineMesh"));
	SplineMesh->SetupAttachment(Spline);
}

// Called when the game starts or when spawned
void APasscodePuzzleButtonLink::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APasscodePuzzleButtonLink::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

