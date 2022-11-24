// Fill out your copyright notice in the Description page of Project Settings.

#include "ElectricalCableGrabComponent.h"
#include "ScrewedObject.h"
#include "ScrewFixComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

UElectricalCableGrabComponent::UElectricalCableGrabComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UElectricalCableGrabComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsLinked)
	{
		if (UKismetMathLibrary::Vector_Distance(this->GetRelativeLocation(), PreviousParent->K2_GetComponentLocation()) >= 2.0f)
		{
			TimerOfTeleportation += DeltaTime;
			if (TimerOfTeleportation >= 5)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, PreviousParent->K2_GetComponentLocation().ToString());
				this->SetRelativeLocation(PreviousParent->K2_GetComponentLocation());
				this->SetRelativeRotation(FRotator(90, 0, 0));
				bIsLinked = true;
				TimerOfTeleportation = 0;
			}
		}
	}

	if (FixedComponent != nullptr && !bIsInteractable)
	{
		bIsInteractable = FixedComponent->bFreeOfScrews;
	}
}
void UElectricalCableGrabComponent::Interact_Implementation(USceneComponent* ControllerUsed)
{
	if (bIsInteractable)
	{
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
	}
}

void UElectricalCableGrabComponent::StopInteract_Implementation()
{
	if (bIsInteractable)
	{
		if (LastSocketTouched != nullptr && LastSocketTouched->GetMaterial(0) == this->GetMaterial(0))
		{
			SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
			DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

			LastSocketTouched->bPlayCableConnectedSound = true;
			AttachToComponent(Cast<USceneComponent>(LastSocketTouched), FAttachmentTransformRules::KeepWorldTransform);
			this->SetRelativeLocation(FVector(-5, 0, 0));
			this->SetRelativeRotation(FRotator(0, 0, 90));
			OnCableLinked.Broadcast();
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
}

void UElectricalCableGrabComponent::ChangeCableColor(UMaterial* Mat)
{
	this->SetMaterial(0, Mat);
}

void UElectricalCableGrabComponent::BeginPlay()
{
	Super::BeginPlay();

	AScrewedObject* Panel = Cast<AScrewedObject>(UGameplayStatics::GetActorOfClass(GetWorld(), AScrewedObject::StaticClass()));
	if (Panel != nullptr)
	{
		FixedComponent = Cast<UScrewFixComponent>(Panel->GetComponentByClass(UScrewFixComponent::StaticClass()));
	}
}