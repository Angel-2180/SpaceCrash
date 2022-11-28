// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceCraftDoor.generated.h"

UCLASS()
class VRDEVFUNDAMENTALS_API ASpaceCraftDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpaceCraftDoor();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		USceneComponent* Root;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UStaticMeshComponent* DoorMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool IsOpen;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool PlayDoorOpeningSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool PlayDoorClosingSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FVector OpenedDistance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float TimeToOpenDoor;

	bool DoorFinishedMoving = true;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	FVector ClosedLocation;
	FRotator BaseRotation;
	float Timer = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void OpenDoor();

	void OpenDoorFinished();

	UFUNCTION(BlueprintCallable)
		void CloseDoor();
};
