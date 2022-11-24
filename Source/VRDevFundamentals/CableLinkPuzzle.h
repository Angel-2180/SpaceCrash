// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CableLinkPuzzle.generated.h"

UCLASS()
class VRDEVFUNDAMENTALS_API ACableLinkPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACableLinkPuzzle();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		USceneComponent* Panel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<class AWireActor*> Wires;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<class UWireSocket*> WireSockets;

	float TotalValue;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
