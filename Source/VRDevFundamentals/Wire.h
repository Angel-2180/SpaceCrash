// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Wire.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VRDEVFUNDAMENTALS_API UWire : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWire();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UStaticMeshComponent* WireRoot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UStaticMeshComponent* WireStart;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UStaticMeshComponent* WireSocket;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UCableComponent* Wire;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
