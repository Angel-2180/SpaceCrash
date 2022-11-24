// Fill out your copyright notice in the Description page of Project Settings.

#include "VRPawn.h"
#include "MyInterface.h"

#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AVRPawn::AVRPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AVRPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AVRPawn::LeftHandPressedGrab(USceneComponent* LeftHandMesh)
{
	FVector WorldPosition = LeftHandMesh->GetComponentLocation();
	FVector Foward = LeftHandMesh->GetComponentLocation() + LeftHandMesh->GetUpVector() * 4;
	TArray<FHitResult> HitResult;
	if (UKismetSystemLibrary::BoxTraceMulti(this, WorldPosition, Foward, FVector(3, 3, 3), FRotator(0, 0, 0), ETraceTypeQuery::TraceTypeQuery1, false, TArray<AActor*>(), EDrawDebugTrace::ForDuration, HitResult, true))
	{
		for (int i = 0; i < HitResult.Num(); i++)
		{
			if (UKismetSystemLibrary::IsValid(HitResult[i].GetActor()))
			{
				if (HitResult[i].GetActor()->GetClass()->ImplementsInterface(UMyInterface::StaticClass()))
				{
					IMyInterface::Execute_Interact(HitResult[i].GetActor(), LeftHandMesh);

					LeftHandHeldActor = HitResult[i].GetActor();
					return;
				}

				if (HitResult[i].GetComponent()->GetClass()->ImplementsInterface(UMyInterface::StaticClass()))
				{
					IMyInterface::Execute_Interact(HitResult[i].GetComponent(), LeftHandMesh);

					LeftHandHeldComponent = HitResult[i].GetComponent();
					return;
				}
			}
		}
	}
}

void AVRPawn::RightHandPressedGrab(USceneComponent* RightHandMesh)
{
	FVector WorldPosition = RightHandMesh->GetComponentLocation();
	FVector Foward = RightHandMesh->GetComponentLocation() + RightHandMesh->GetUpVector() * 4;
	TArray<FHitResult> HitResult;
	if (UKismetSystemLibrary::BoxTraceMulti(this, WorldPosition, Foward, FVector(3, 3, 3), FRotator(0, 0, 0), ETraceTypeQuery::TraceTypeQuery1, false, TArray<AActor*>(), EDrawDebugTrace::ForDuration, HitResult, true))
	{
		for (int i = 0; i < HitResult.Num(); i++)
		{
			if (UKismetSystemLibrary::IsValid(HitResult[i].GetActor()))
			{
				if (HitResult[i].GetActor()->GetClass()->ImplementsInterface(UMyInterface::StaticClass()))
				{
					IMyInterface::Execute_Interact(HitResult[i].GetActor(), RightHandMesh);

					RightHandHeldActor = HitResult[i].GetActor();
					return;
				}

				if (HitResult[i].GetComponent()->GetClass()->ImplementsInterface(UMyInterface::StaticClass()))
				{
					IMyInterface::Execute_Interact(HitResult[i].GetComponent(), RightHandMesh);

					RightHandHeldComponent = HitResult[i].GetComponent();
					return;
				}
			}
		}
	}
}

void AVRPawn::LeftHandReleaseGrab(USceneComponent* LeftHandMesh)
{
	if (LeftHandHeldActor != nullptr || LeftHandHeldComponent != nullptr)
	{
		if (LeftHandHeldActor == RightHandHeldActor && LeftHandHeldActor != nullptr)
		{
			LeftHandHeldActor = nullptr;
		}
		else if (LeftHandHeldComponent == RightHandHeldComponent && LeftHandHeldComponent != nullptr)
		{
			LeftHandHeldComponent = nullptr;
		}
		else
		{
			/*if (LeftHandHeldActor->GetClass()->ImplementsInterface(UMyInterface::StaticClass()))
			{
				if(LeftClass == "Actor")
					IMyInterface::Execute_StopInteract(LeftHandHeldActor);
				else
					IMyInterface::Execute_StopInteract(LeftHandHeldActor);

				LeftHandHeldActor = nullptr;
				return;
			}*/

			if (LeftHandHeldActor != nullptr)
			{
				IMyInterface::Execute_StopInteract(LeftHandHeldActor);
				LeftHandHeldActor = nullptr;
				return;
			}
			else if (LeftHandHeldComponent != nullptr)
			{
				IMyInterface::Execute_StopInteract(LeftHandHeldComponent);
				LeftHandHeldComponent = nullptr;
				return;
			}
		}
	}
}

void AVRPawn::RightHandReleaseGrab(USceneComponent* RightHandMesh)
{
	if (RightHandHeldActor != nullptr || RightHandHeldComponent != nullptr)
	{
		if (LeftHandHeldActor == RightHandHeldActor && RightHandHeldActor != nullptr)
		{
			RightHandHeldActor = nullptr;
		}
		else if (LeftHandHeldComponent == RightHandHeldComponent && RightHandHeldComponent != nullptr)
		{
			RightHandHeldActor = nullptr;
		}
		else
		{
			/*if (RightHandHeldActor->GetClass()->ImplementsInterface(UMyInterface::StaticClass()))
			{
				if (RightClass == "Actor")
					IMyInterface::Execute_StopInteract(RightHandHeldActor->GetAttachmentRootActor());
				else
					IMyInterface::Execute_StopInteract(RightHandHeldActor);

				RightHandHeldActor = nullptr;
				return;
			}*/

			if (RightHandHeldActor != nullptr)
			{
				IMyInterface::Execute_StopInteract(RightHandHeldActor);
				RightHandHeldActor = nullptr;
				return;
			}
			else if (RightHandHeldComponent != nullptr)
			{
				IMyInterface::Execute_StopInteract(RightHandHeldComponent);
				RightHandHeldComponent = nullptr;
				return;
			}
		}
	}
}

void AVRPawn::UpdateUI(bool InUI, FVector HitLocationOnUI, UStaticMeshComponent* InteractionHitSphere, USplineMeshComponent* SplineMesh, USplineComponent* Spline)
{
	if (!InUI)
	{
		InteractionHitSphere->SetHiddenInGame(true);
		SplineMesh->SetHiddenInGame(true);
	}
	else
	{
		InteractionHitSphere->SetHiddenInGame(false);
		InteractionHitSphere->SetWorldLocation(HitLocationOnUI);
		SplineMesh->SetHiddenInGame(false);
		Spline->SetLocationAtSplinePoint(1, HitLocationOnUI, ESplineCoordinateSpace::World);
		FVector StartPos;
		FVector StartTan;
		FVector EndPos;
		FVector EndTan;
		Spline->GetLocationAndTangentAtSplinePoint(0, StartPos, StartTan, ESplineCoordinateSpace::Local);
		Spline->GetLocationAndTangentAtSplinePoint(1, EndPos, EndTan, ESplineCoordinateSpace::Local);
		SplineMesh->SetStartAndEnd(StartPos, StartTan, EndPos, EndTan);
	}
}

void AVRPawn::SetupHandPointers(UMotionControllerComponent* LeftHandComp, UMotionControllerComponent* RightHandComp)
{
	LeftHandMotionController = LeftHandComp;
	RightHandMotionController = RightHandComp;
}