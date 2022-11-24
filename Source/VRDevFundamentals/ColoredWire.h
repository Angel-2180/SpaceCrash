// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CableComponent.h"
#include "ElectricalCableGrabComponent.h"
#include "GameFramework/Actor.h"
#include "ColoredWire.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnComplete);

UCLASS()
class VRDEVFUNDAMENTALS_API AColoredWire : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AColoredWire();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int Color;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		UStaticMeshComponent* WireStart;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		UCableComponent* Wire;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		UElectricalCableGrabComponent* WireEnd;

	int NbrOfWiresConnected;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnConnection();

	UFUNCTION()
		void WireSocketBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void WireSocketEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	FOnComplete OnCompleteEvent;
};
