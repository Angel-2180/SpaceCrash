// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyInterface.h"
#include "Components/ArrowComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Screw.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FScrewRelease);

/**
 *
 */
UCLASS()
class VRDEVFUNDAMENTALS_API AScrew : public AStaticMeshActor, public IMyInterface
{
	//declare delegate
	GENERATED_BODY()

		AScrew();

	UPROPERTY(EditAnywhere, Category = "Screw")
		float CurrentScrewDist;

	FVector InitialPos;

protected:

	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable, Category = "Screw")
		bool AddRotationValue(float DeltaRotation);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Screw")
		bool bisScrewed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Screw")
		float MaximumScrewDist = 4.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Screw")
		float ThreadPitch = 7.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Screw;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
		void Interact(USceneComponent* ControllerUsed);
	virtual void Interact_Implementation(USceneComponent* ControllerUsed) override;
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
		void StopInteract();
	virtual void StopInteract_Implementation() override;
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

	//event release Screw
	UPROPERTY(BlueprintAssignable, Category = "Screw")
		FScrewRelease OnScrewRelease;
};
