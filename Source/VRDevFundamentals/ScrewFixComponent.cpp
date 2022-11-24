// Fill out your copyright notice in the Description page of Project Settings.

#include "ScrewFixComponent.h"

// Sets default values for this component's properties
UScrewFixComponent::UScrewFixComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	if (ScrewArray.Num() > 0)
		bFreeOfScrews = false;
}

// Called when the game starts
void UScrewFixComponent::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < ScrewArray.Num(); i++)
	{
		//if the screw is not null
		if (ScrewArray[i] != nullptr)
		{
			ScrewCount++;
			ScrewArray[i]->bisScrewed = true;
			ScrewArray[i]->OnScrewRelease.AddDynamic(this, &UScrewFixComponent::Release);
		}
	}
}

// Called every frame
void UScrewFixComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UScrewFixComponent::Release()
{
	ScrewCount--;
	if (ScrewCount <= 0)
	{
		bFreeOfScrews = true;
		if (OnAllScrewReleased.IsBound())
			OnAllScrewReleased.Broadcast();
	}
}