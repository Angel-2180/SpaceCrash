// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TaskButton.generated.h"

UCLASS()
class VRDEVFUNDAMENTALS_API ATaskButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATaskButton();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		USceneComponent* Root;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UStaticMeshComponent* BaseButtonMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UStaticMeshComponent* ButtonMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UMaterial* NormalMat;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UMaterial* SelectedMat;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bActive;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bDeactivateInteraction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bPlayActiveSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bPlayDeactiveSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	class AIndexCollision* Index;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void ButtonBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void ButtonEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
