// Fill out your copyright notice in the Description page of Project Settings.

#include "GrabbableComponent.h"
#include "WireSocket.h"

UGrabbableComponent::UGrabbableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UGrabbableComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UGrabbableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsLinked)
	{
		if (FVector::Dist(this->GetRelativeLocation(), PreviousParent->GetComponentLocation()) >= 2.0f)
		{
			TimerOfTeleportation += DeltaTime;
			if (TimerOfTeleportation > 5)
			{
				this->SetRelativeLocation(PreviousParent->GetComponentLocation());
				this->SetRelativeRotation(FRotator(0, 0, 0));
				IsLinked = true;
				TimerOfTeleportation = 0;
			}
		}
	}
}

void UGrabbableComponent::Interact_Implementation(USceneComponent* ControllerUsed)
{
	IsLinked = true;
	if (LastSocketTouched != nullptr)
	{
		if (PreviousParent != nullptr)
		{
			LastSocketTouched->TotalValueOnThisSocket = -this->Value * LastSocketTouched->Value;
			LastSocketTouched = nullptr;
		}
	}
	SetSimulatePhysics(false);
	SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	AttachToComponent(ControllerUsed, FAttachmentTransformRules::KeepWorldTransform);
}

void UGrabbableComponent::StopInteract_Implementation()
{
	if (LastSocketTouched != nullptr)
	{
		LastSocketTouched->IsParticleActive = true;
		SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
		DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);		

		LastSocketTouched->TotalValueOnThisSocket = this->Value * LastSocketTouched->Value;
		LastSocketTouched->PlayCableConnectedSound = true;

		AttachToComponent(Cast<USceneComponent>(LastSocketTouched), FAttachmentTransformRules::KeepWorldTransform);
		this->SetRelativeLocation(FVector(0, 0, 0));
		this->SetRelativeRotation(FRotator(0, 0, 0));
	}

	else
	{
		IsLinked = false;
		SetSimulatePhysics(true);
		SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
		DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

		if (PreviousParent != nullptr)
		{
			AttachToComponent(PreviousParent, FAttachmentTransformRules::KeepWorldTransform);
			//this->SetRelativeLocation(PreviousParent->GetComponentLocation());
			//this->SetRelativeRotation(FRotator(90, 0, 0));
		}
	}
}