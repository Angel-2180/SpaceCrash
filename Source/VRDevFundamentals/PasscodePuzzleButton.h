// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PasscodePuzzleButton.generated.h"


UCLASS()
class VRDEVFUNDAMENTALS_API APasscodePuzzleButton : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	APasscodePuzzleButton();

	UPROPERTY(BlueprintReadWrite)
	class USphereComponent* Button;

	UPROPERTY(BlueprintReadWrite)
		UMaterial* NormalMat;

	UPROPERTY(BlueprintReadWrite)
		UMaterial* SelectedMat;

	UPROPERTY(BlueprintReadWrite)
		TSubclassOf<class APasscodePuzzleButtonLink> LineBlueprint;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void ButtonBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, class APasscodePuzzleButtonLink* Link);

	UFUNCTION(BlueprintCallable)
	class APasscodePuzzleButtonLink* ButtonEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor);
};
