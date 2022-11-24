// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorButton.generated.h"

UCLASS()
class VRDEVFUNDAMENTALS_API ADoorButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorButton();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		USceneComponent* Root;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UStaticMeshComponent* BaseButtonMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UStaticMeshComponent* ButtonMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class ASpaceCraftDoor* DoorControlled;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class ADoorEngine* DoorEngine;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UMaterial* NormalMat;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UMaterial* SelectedMat;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	class AIndexCollision* Index;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void ButtonBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void ButtonEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
