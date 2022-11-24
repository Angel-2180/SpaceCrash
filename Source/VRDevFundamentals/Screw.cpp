// Fill out your copyright notice in the Description page of Project Settings.

#include "Screw.h"

// Sets default values
AScrew::AScrew()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = this->GetStaticMeshComponent();
	bisScrewed = false;
}

bool AScrew::AddRotationValue(float DeltaRotation)
{
	UE_LOG(LogTemp, Warning, TEXT("Screw: AddRotationValue"));
	FRotator DeltaRotationAmount = FRotator(0.0f, DeltaRotation, 0.0f);
	//AddActorLocalRotation(DeltaRotationAmount);
	Screw->AddLocalRotation(DeltaRotationAmount);
	FVector deltaPos = FVector(Screw->GetRelativeLocation().X, Screw->GetRelativeLocation().Y, Screw->GetRelativeLocation().Z + (DeltaRotation * (ThreadPitch / 360.0f)));
	//AddActorWorldOffset(deltaPos);
	Screw->SetRelativeLocation(deltaPos);
	CurrentScrewDist += (DeltaRotation * (ThreadPitch / 360.0f));
	if (Screw->GetRelativeLocation().Z >= InitialPos.Z + MaximumScrewDist)
	{
		bisScrewed = false;
		//call event for release object
		if (OnScrewRelease.IsBound())
			OnScrewRelease.Broadcast();
		Screw->SetSimulatePhysics(true);
		return true;
	}
	return false;
}

void AScrew::BeginPlay()
{
	Super::BeginPlay();

	CurrentScrewDist = 0.0f;

	InitialPos = Screw->GetRelativeLocation();

	if (bisScrewed)
	{
		this->GetStaticMeshComponent()->SetSimulatePhysics(false);
	}
	else
	{
		this->GetStaticMeshComponent()->SetSimulatePhysics(true);
	}
}

void AScrew::Interact_Implementation(USceneComponent* ControllerUsed)
{
	//if the screw is not screwed
	if (bisScrewed == false)
	{
		this->GetStaticMeshComponent()->SetSimulatePhysics(false);
		this->GetStaticMeshComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

		this->GetStaticMeshComponent()->AttachToComponent(ControllerUsed, FAttachmentTransformRules::KeepWorldTransform);
	}
}

void AScrew::StopInteract_Implementation()
{
	if (bisScrewed == false)
	{
		this->GetStaticMeshComponent()->SetSimulatePhysics(true);
		this->GetStaticMeshComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
		this->GetStaticMeshComponent()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}
}