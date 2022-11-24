// Fill out your copyright notice in the Description page of Project Settings.

#include "ScrewedObject.h"

// Sets default values

AScrewedObject::AScrewedObject()
{
	RootComponent = this->GetStaticMeshComponent();
	ScrewFixComponent = CreateDefaultSubobject<UScrewFixComponent>(TEXT("ScrewFixComponent"));
}

void AScrewedObject::BeginPlay()
{
	Super::BeginPlay();
	if (this->GetStaticMeshComponent())
	{
		this->GetStaticMeshComponent()->SetSimulatePhysics(false);
	}
	if (ScrewFixComponent->OnAllScrewReleased.IsBound())
		ScrewFixComponent->OnAllScrewReleased.AddDynamic(this, &AScrewedObject::TurnOnPhysics);
}

void AScrewedObject::Interact_Implementation(USceneComponent* ControllerUsed)
{
	//if the object is not free of screws
	if (ScrewFixComponent->bFreeOfScrews)
	{
		//if the object is not screwed

		this->GetStaticMeshComponent()->SetSimulatePhysics(false);
		this->GetStaticMeshComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

		this->GetStaticMeshComponent()->AttachToComponent(ControllerUsed, FAttachmentTransformRules::KeepWorldTransform);
	}
}

void AScrewedObject::StopInteract_Implementation()
{
	if (ScrewFixComponent->bFreeOfScrews)
	{
		this->GetStaticMeshComponent()->SetSimulatePhysics(true);
		this->GetStaticMeshComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
		this->GetStaticMeshComponent()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}
}

void AScrewedObject::TurnOnPhysics()
{
	this->GetStaticMeshComponent()->SetSimulatePhysics(true);
}