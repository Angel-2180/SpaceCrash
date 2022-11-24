// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "MyInterface.h"
#include "GrabbableComponent.generated.h"

/**
 *
 */
UCLASS()
class VRDEVFUNDAMENTALS_API UGrabbableComponent : public UStaticMeshComponent, public IMyInterface
{
	GENERATED_BODY()

public:

	UGrabbableComponent();

	float Value;

	USceneComponent* PreviousParent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Interact")
		class UWireSocket* LastSocketTouched;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	float TimerOfTeleportation;

	bool IsLinked = true;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
		void Interact(USceneComponent* ControllerUsed);
	virtual void Interact_Implementation(USceneComponent* ControllerUsed) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
		void StopInteract();
	virtual void StopInteract_Implementation() override;
};
