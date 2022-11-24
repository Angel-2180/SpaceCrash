// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PasscodePuzzle.generated.h"

UCLASS()
class VRDEVFUNDAMENTALS_API APasscodePuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APasscodePuzzle();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init")
	int32 NbOfButton = 9;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init")
	int32 NbOfButtonNeededForCombination = 4;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Init")
	TArray<class UPasscodePuzzleButtonComponent*> ButtonList;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* Panel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UBoxComponent* Collider;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterial* NormalMat;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterial* SelectedMat;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class APasscodePuzzleButtonLink> LineBlueprint;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool PlayCompletedSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool PlayFailedSound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool PlayButtonSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	class AIndexCollision* Index;

	class APasscodePuzzleButtonLink* Line;

	UPrimitiveComponent* LastHitComponent;

	UPrimitiveComponent* CurrentHitComponent;

	TArray<APasscodePuzzleButtonLink*> Links;

	TArray<UPasscodePuzzleButtonComponent*> ButtonCombination;

	TArray<UPasscodePuzzleButtonComponent*> ButtonPressed;

	UPasscodePuzzleButtonComponent* GenerateRandomNumber(UPasscodePuzzleButtonComponent* PreviousButton);

	void GenerateAdjacentButton();

	float Timer = 0;

	float Subtimer = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void ButtonBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void ButtonEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void InPanel(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OutsidePanel(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
