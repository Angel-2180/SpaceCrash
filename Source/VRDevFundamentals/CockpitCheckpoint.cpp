// Fill out your copyright notice in the Description page of Project Settings.


#include "CockpitCheckpoint.h"

// Sets default values
ACockpitCheckpoint::ACockpitCheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACockpitCheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACockpitCheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

