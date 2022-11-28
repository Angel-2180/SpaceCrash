// Fill out your copyright notice in the Description page of Project Settings.


#include "PasscodePuzzleButton.h"
#include "IndexCollision.h"
#include "PasscodePuzzleButtonLink.h"
#include "Components/SphereComponent.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"

// Sets default values for this component's properties
APasscodePuzzleButton::APasscodePuzzleButton()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = true;
}


// Called when the game starts
void APasscodePuzzleButton::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void APasscodePuzzleButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ...
}

void APasscodePuzzleButton::ButtonBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, APasscodePuzzleButtonLink* Link)
{
	AIndexCollision* Finger = Cast<AIndexCollision>(OtherActor);
	if (Finger != nullptr)
	{
		if (Finger->SphereCollider->IsActive())
		{
			OverlappedComp->SetMaterial(0, SelectedMat);
			if (Link != nullptr)
			{
				Link->Spline->SetLocationAtSplinePoint(1, OverlappedComp->GetComponentLocation(), ESplineCoordinateSpace::World);
				Link->SplineMesh->SetEndPosition(OverlappedComp->GetComponentLocation());
			}
		}
	}
}

APasscodePuzzleButtonLink* APasscodePuzzleButton::ButtonEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor)
{
	AIndexCollision* Finger = Cast<AIndexCollision>(OtherActor);
	if (Finger != nullptr)
	{
		if (Finger->SphereCollider->IsActive())
		{
			OverlappedComp->SetMaterial(0, NormalMat);
			APasscodePuzzleButtonLink* NewLink = GetWorld()->SpawnActor<APasscodePuzzleButtonLink>(LineBlueprint, OverlappedComp->GetComponentTransform());
			NewLink->Spline->SetLocationAtSplinePoint(0, OverlappedComp->GetComponentLocation(), ESplineCoordinateSpace::World);
			NewLink->Spline->SetLocationAtSplinePoint(1, Finger->GetActorLocation(), ESplineCoordinateSpace::World);
			FVector StartPos;
			FVector StartTan;
			FVector EndPos;
			FVector EndTan;
			NewLink->Spline->GetLocationAndTangentAtSplinePoint(0, StartPos, StartTan, ESplineCoordinateSpace::World);
			NewLink->Spline->GetLocationAndTangentAtSplinePoint(1, EndPos, EndTan, ESplineCoordinateSpace::World);
			NewLink->SplineMesh->SetStartAndEnd(StartPos, StartTan, EndPos, EndTan);
			return NewLink;
		}
	}
	return nullptr;
}

