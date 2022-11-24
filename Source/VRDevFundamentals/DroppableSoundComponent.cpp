// Fill out your copyright notice in the Description page of Project Settings.


#include "DroppableSoundComponent.h"

// Sets default values for this component's properties
UDroppableSoundComponent::UDroppableSoundComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDroppableSoundComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDroppableSoundComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

USoundWave* UDroppableSoundComponent::SetRandomDropSound()
{
	return DropSoundList[rand() % DropSoundList.Num()];
}

