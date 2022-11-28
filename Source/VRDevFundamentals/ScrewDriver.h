// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Screw.h"
#include "Engine/StaticMeshActor.h"
#include "MyInterface.h"
#include "Components/BoxComponent.h"
#include "ScrewDriver.generated.h"

/**
 *
 */
UCLASS()
class VRDEVFUNDAMENTALS_API AScrewDriver : public AStaticMeshActor, public IMyInterface
{
	GENERATED_BODY()

		AScrewDriver();

	UPROPERTY(EditAnywhere, Category = "ScrewDriver")
		UBoxComponent* BoxCollision;
private:
	float TimerOfTeleportation;

	FVector InitialPos;

	FRotator InitialRot;

	UPROPERTY(EditAnywhere, Category = "ScrewDriver")
		bool bIsInHand;

	UPROPERTY(EditAnywhere, Category = "ScrewDriver")
		bool bScrewFound;

	UPROPERTY(EditAnywhere, Category = "ScrewDriver")
		AScrew* ActiveScrew;

	UPROPERTY(EditAnywhere, Category = "ScrewDriver")
		float deltaRotation;

protected:
	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bActivated;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
		void Interact(USceneComponent* ControllerUsed);

	virtual void Interact_Implementation(USceneComponent* ControllerUsed) override;
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
		void StopInteract();

	virtual void StopInteract_Implementation() override;
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
