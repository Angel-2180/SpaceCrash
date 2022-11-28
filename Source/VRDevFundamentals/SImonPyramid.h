// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyInterface.h"
#include "GameFramework/Actor.h"
#include "SImonPyramid.generated.h"

UCLASS()
class VRDEVFUNDAMENTALS_API ASimonPyramid : public AActor, public IMyInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASimonPyramid();
	// Create a root component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Simon Box")
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
		UMaterial* Pyramid_On_Material;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
		UMaterial* Pyramid_Off_Material;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* Face1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* Face2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* Face3;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		TArray<UStaticMeshComponent*> Faces;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int NbrOfActiveFaces;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bPuzzleStarted;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bPlayCompletedSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bPlayFailedSound;

	bool bPuzzleDone;

	float Timer;

	float SubTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlapFaceBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapBaseBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapBaseEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

	class USpaceCrashGameInstance* GameInstance;

private:

	class ASimonPyramidBase* PyramidBase;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
		void Interact(USceneComponent* ControllerUsed);
	virtual void Interact_Implementation(USceneComponent* ControllerUsed) override;
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
		void StopInteract();
	virtual void StopInteract_Implementation() override;
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
};
