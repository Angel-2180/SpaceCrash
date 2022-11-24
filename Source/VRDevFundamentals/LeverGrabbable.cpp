// Fill out your copyright notice in the Description page of Project Settings.


#include "LeverGrabbable.h"

ULeverGrabbable::ULeverGrabbable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void ULeverGrabbable::BeginPlay()
{
	Super::BeginPlay();
}

void ULeverGrabbable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void ULeverGrabbable::Interact_Implementation(USceneComponent* ControllerUsed)
{
	SetSimulatePhysics(false);
	SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	AttachToComponent(ControllerUsed, FAttachmentTransformRules::KeepWorldTransform);
}

void ULeverGrabbable::StopInteract_Implementation()
{
	SetSimulatePhysics(false);
	SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

	if (PreviousParent != nullptr)
	{
		AttachToComponent(PreviousParent, FAttachmentTransformRules::KeepWorldTransform);
		this->SetRelativeLocation(FVector(0, 0, 0));
		this->SetRelativeRotation(FRotator(0, 0, 0));
	}
}

void ULeverGrabbable::DropLever()
{
	SetSimulatePhysics(false);
	SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

	if (PreviousParent != nullptr)
	{
		AttachToComponent(PreviousParent, FAttachmentTransformRules::KeepWorldTransform);
		this->SetRelativeLocation(FVector(0, 0, 0));
		this->SetRelativeRotation(FRotator(0, 0, 0));
	}
}
