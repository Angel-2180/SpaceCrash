// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ElectricalSocketComponent.h"
#include "ElectricalBox.generated.h"

//create delegate

UCLASS()
class VRDEVFUNDAMENTALS_API AElectricalBox : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AElectricalBox();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		USceneComponent* Panel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UStaticMeshComponent* PanelMesh;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		TArray<UElectricalSocketComponent*> WireSockets;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<UMaterial*> MatArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int NbrOfConnectedWires;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnComplete();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
