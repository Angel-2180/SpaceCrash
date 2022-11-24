// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SplineMeshComponent.h"
#include "Components/SplineComponent.h"
#include "MotionControllerComponent.h"
#include "VRPawn.generated.h"

UCLASS()
class VRDEVFUNDAMENTALS_API AVRPawn : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVRPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	int HandGrabLength;

	UPROPERTY(BlueprintReadWrite)
		bool LightOn;

	UPROPERTY(BlueprintReadWrite)
		UMotionControllerComponent* LeftHandMotionController;

	UPROPERTY(BlueprintReadWrite)
		UMotionControllerComponent* RightHandMotionController;

	UPROPERTY(BlueprintReadWrite)
	AActor* LeftHandHeldActor;
	USceneComponent* LeftHandHeldComponent;

	UPROPERTY(BlueprintReadWrite)
	AActor* RightHandHeldActor;

	UPROPERTY(BlueprintReadWrite)
	USceneComponent* RightHandHeldComponent;

	UPROPERTY(BlueprintReadWrite)
	UAudioComponent* HeartBeatSound;

	UFUNCTION(BlueprintCallable)
	void LeftHandPressedGrab(USceneComponent* LeftHandMesh);

	UFUNCTION(BlueprintCallable)
	void RightHandPressedGrab(USceneComponent* RightHandMesh);

	UFUNCTION(BlueprintCallable)
	void LeftHandReleaseGrab(USceneComponent* LeftHandMesh);

	UFUNCTION(BlueprintCallable)
	void RightHandReleaseGrab(USceneComponent* RightHandMesh);

	UFUNCTION(BlueprintCallable)
	void UpdateUI(bool InUI, FVector HitLocationOnUI, UStaticMeshComponent* InteractionHitSphere, USplineMeshComponent* SplineMesh, USplineComponent* Spline);

	UFUNCTION(BlueprintCallable)
	void SetupHandPointers(UMotionControllerComponent* LeftHandComp, UMotionControllerComponent* RightHandComp);
};
