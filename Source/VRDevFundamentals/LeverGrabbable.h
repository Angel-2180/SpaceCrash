// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "MyInterface.h"
#include "LeverGrabbable.generated.h"

/**
 * 
 */
UCLASS()
class VRDEVFUNDAMENTALS_API ULeverGrabbable : public UStaticMeshComponent, public IMyInterface
{
	GENERATED_BODY()
	
public:

	ULeverGrabbable();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Interact")
		USceneComponent* PreviousParent;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
		void Interact(USceneComponent* ControllerUsed);
	virtual void Interact_Implementation(USceneComponent* ControllerUsed) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
		void StopInteract();
	virtual void StopInteract_Implementation() override;

	UFUNCTION(BlueprintCallable)
		void DropLever();
};
