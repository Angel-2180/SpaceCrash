// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskButtonBase.h"
#include "TaskButton.h"

// Sets default values
ATaskButtonBase::ATaskButtonBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATaskButtonBase::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> ButtonArray;
	GetAllChildActors(ButtonArray);
	for (int i = 0; i < ButtonArray.Num(); i++)
	{
		ATaskButton* NewButton = Cast<ATaskButton>(ButtonArray[i]);
		if (NewButton != nullptr)
		{
			ButtonList.Add(NewButton);
		}
	}
}

// Called every frame
void ATaskButtonBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ButtonList[0]->bActive && ButtonList[1]->bActive && ButtonList[2]->bActive)
	{
		bTaskCompleted = true;
	}

	if (bTaskCompleted && bTaskActive)
	{
		for (int i = 0; i < ButtonList.Num(); i++)
		{
			ButtonList[i]->bDeactivateInteraction = true;
		}
		bPlayActiveSound = true;
	}
}

