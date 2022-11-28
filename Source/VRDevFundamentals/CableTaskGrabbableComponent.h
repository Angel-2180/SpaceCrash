// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyInterface.h"
#include "Components/StaticMeshComponent.h"
#include "CableTaskGrabbableComponent.generated.h"

/**
 *
 */
UCLASS()
class VRDEVFUNDAMENTALS_API UCableTaskGrabbableComponent : public UStaticMeshComponent, public IMyInterface
{
	GENERATED_BODY()

private:
	float TimerOfTeleportation;

	FVector InitialPos;

	FRotator InitialRot;

protected:

	virtual void BeginPlay() override;

public:
	bool bIsInteractable = false;

	bool bIsLinked = true;

	UCableTaskGrabbableComponent();

	USceneComponent* PreviousParent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class ACableTaskCollider* LastSocketTouched;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bPlayCableConnectedSound;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
		void Interact(USceneComponent* ControllerUsed);
	virtual void Interact_Implementation(USceneComponent* ControllerUsed) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
		void StopInteract();
	virtual void StopInteract_Implementation() override;
};
