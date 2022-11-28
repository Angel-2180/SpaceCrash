// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "ElectricalSocketComponent.generated.h"

/**
 *
 */
UCLASS()
class VRDEVFUNDAMENTALS_API UElectricalSocketComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

protected:

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	UElectricalSocketComponent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool Linked;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bPlayCableConnectedSound;

	//Overlap functions
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);
};
