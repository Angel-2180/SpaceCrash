// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "IndexCollision.generated.h"

UCLASS()
class VRDEVFUNDAMENTALS_API AIndexCollision : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIndexCollision();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UStaticMeshComponent* Mesh;
	USphereComponent* SphereCollider;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetVariables(UStaticMeshComponent* MeshVar, USphereComponent* SphereColliderVar);

	UFUNCTION(BlueprintCallable)
	void SetColliderState(bool IsActive);
};
