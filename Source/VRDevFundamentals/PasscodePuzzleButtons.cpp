// Fill out your copyright notice in the Description page of Project Settings.


#include "PasscodePuzzleButtons.h"
#include "IndexCollision.h"
#include "PasscodePuzzleButtonLink.h"
#include "Components/SphereComponent.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"

// Sets default values
APasscodePuzzleButtons::APasscodePuzzleButtons()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetWorldScale3D(FVector(0.05f, 0.15f, 0.15f));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void APasscodePuzzleButtons::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APasscodePuzzleButtons::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APasscodePuzzleButtons::ButtonBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, APasscodePuzzleButtonLink* Link)
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

APasscodePuzzleButtonLink* APasscodePuzzleButtons::ButtonEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor)
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