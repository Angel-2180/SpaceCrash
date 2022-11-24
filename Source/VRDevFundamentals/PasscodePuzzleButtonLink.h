// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PasscodePuzzleButtonLink.generated.h"

UCLASS()
class VRDEVFUNDAMENTALS_API APasscodePuzzleButtonLink : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APasscodePuzzleButtonLink();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class USplineComponent* Spline;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class USplineMeshComponent* SplineMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
