// Fill out your copyright notice in the Description page of Project Settings.


#include "IndexCollision.h"

// Sets default values
AIndexCollision::AIndexCollision()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AIndexCollision::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIndexCollision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIndexCollision::SetVariables(UStaticMeshComponent* MeshVar, USphereComponent* SphereColliderVar)
{
	Mesh = MeshVar;
	SphereCollider = SphereColliderVar;
}

void AIndexCollision::SetColliderState(bool IsActive)
{
	if (IsActive)
	{
		if (Mesh != nullptr)
			Mesh->SetVisibility(false);

		if (SphereCollider != nullptr)
			SphereCollider->Activate();
	}
	else
	{
		if (Mesh != nullptr)
			Mesh->SetVisibility(true);

		if (SphereCollider != nullptr)
		SphereCollider->Deactivate();
	}
}

