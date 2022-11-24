// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WireActor.generated.h"

UCLASS()
class VRDEVFUNDAMENTALS_API AWireActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWireActor();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UStaticMeshComponent* WireStart;

	class UGrabbableComponent* WireEnd;

	class UCableComponent* Wire;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Value;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void WireSocketBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void WireSocketEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
