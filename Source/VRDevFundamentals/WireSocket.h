// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "WireSocket.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VRDEVFUNDAMENTALS_API UWireSocket : public UStaticMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWireSocket();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Particle")
	bool IsParticleActive;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool PlayCableConnectedSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Value;

	float TotalValueOnThisSocket;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void WireSocketBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void WireSocketEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
