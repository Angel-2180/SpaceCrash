// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "ScrewFixComponent.h"
#include "ScrewedObject.generated.h"

/**
 *
 */
UCLASS()
class VRDEVFUNDAMENTALS_API AScrewedObject : public AStaticMeshActor, public IMyInterface
{
	GENERATED_BODY()

		AScrewedObject();

	UPROPERTY(EditAnywhere, Category = "ScrewedObject")
		UScrewFixComponent* ScrewFixComponent;

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
		void TurnOnPhysics();

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
		void Interact(USceneComponent* ControllerUsed);

	virtual void Interact_Implementation(USceneComponent* ControllerUsed) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
		void StopInteract();

	virtual void StopInteract_Implementation() override;
};
