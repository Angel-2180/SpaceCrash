// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VRDEVFUNDAMENTALS_API IMyInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void Interact(USceneComponent* ControllerUsed);
	virtual void Interact_Implementation(USceneComponent* ControllerUsed);
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void StopInteract();
	virtual void StopInteract_Implementation();
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
};
