// Fill out your copyright notice in the Description page of Project Settings.

#include "SimonPyramidBase.h"

#include "CableTaskGrabbableComponent.h"
#include "SimonPyramid.h"

// Sets default values
ASimonPyramidBase::ASimonPyramidBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BasePyramidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BasePyramidMesh"));
	RootComponent = BasePyramidMesh;
}

// Called when the game starts or when spawned
void ASimonPyramidBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASimonPyramidBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}