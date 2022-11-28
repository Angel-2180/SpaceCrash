// Fill out your copyright notice in the Description page of Project Settings.

#include "CableTaskGrabbableComponent.h"
#include "CableTaskCollider.h"
#include "SpaceCrashGameInstance.h"
#include "Kismet/KismetMathLibrary.h"

UCableTaskGrabbableComponent::UCableTaskGrabbableComponent()
{
}

void UCableTaskGrabbableComponent::BeginPlay()
{
	InitialPos = GetComponentLocation();
	InitialRot = GetComponentRotation();
	bIsInteractable = false;
}

void UCableTaskGrabbableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (!bIsLinked)
	{
		if (UKismetMathLibrary::Vector_Distance(this->GetRelativeLocation(), PreviousParent->K2_GetComponentLocation()) >= 2.0f)
		{
			TimerOfTeleportation += DeltaTime;
			if (TimerOfTeleportation >= 5)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, PreviousParent->K2_GetComponentLocation().ToString());
				this->SetRelativeRotation(InitialRot);
				this->SetRelativeLocation(InitialPos);
				bIsLinked = true;
				TimerOfTeleportation = 0;
			}
		}
	}
}

void UCableTaskGrabbableComponent::Interact_Implementation(USceneComponent* ControllerUsed)
{
	GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Emerald, TEXT("Overlap"));
	if (bIsInteractable == false)
	{
		GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Emerald, TEXT("Interact"));
		bIsLinked = true;
		if (LastSocketTouched != nullptr)
		{
			if (PreviousParent != nullptr)
			{
				LastSocketTouched = nullptr;
			}
		}
		SetSimulatePhysics(false);
		SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		AttachToComponent(ControllerUsed, FAttachmentTransformRules::KeepWorldTransform);
		SetRelativeLocation(FVector(0, -1, 1));
		SetRelativeRotation(FRotator(0, 0, -90));
	}
}

void UCableTaskGrabbableComponent::StopInteract_Implementation()
{
	if (LastSocketTouched != nullptr)
	{
		SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
		DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

		bPlayCableConnectedSound = true;
		AttachToComponent(Cast<USceneComponent>(LastSocketTouched->GetRootComponent()), FAttachmentTransformRules::KeepWorldTransform);
		this->SetRelativeLocation(FVector(0, 0, 30));
		this->SetRelativeRotation(FRotator(-90, 0, 0));
		bIsInteractable = true;
	}
	else
	{
		bIsLinked = false;
		SetSimulatePhysics(true);
		SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
		DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		if (PreviousParent != nullptr)
		{
			AttachToComponent(PreviousParent, FAttachmentTransformRules::KeepWorldTransform);
		}
	}
}