// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyInterface.h"
#include "ElectricalSocketComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ElectricalCableGrabComponent.generated.h"

//create delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCableLinked);
/**
 *
 */
UCLASS()
class VRDEVFUNDAMENTALS_API UElectricalCableGrabComponent : public UStaticMeshComponent, public IMyInterface
{
	GENERATED_BODY()

private:
	float TimerOfTeleportation;

	bool bIsLinked = true;

	bool bIsInteractable = false;

	class UScrewFixComponent* FixedComponent;

protected:

	virtual void BeginPlay() override;

public:

	UElectricalCableGrabComponent();

	USceneComponent* PreviousParent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UElectricalSocketComponent* LastSocketTouched;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
		void Interact(USceneComponent* ControllerUsed);
	virtual void Interact_Implementation(USceneComponent* ControllerUsed) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
		void StopInteract();
	virtual void StopInteract_Implementation() override;

	UFUNCTION()
		void ChangeCableColor(UMaterial* mat);

	FOnCableLinked OnCableLinked;
};
