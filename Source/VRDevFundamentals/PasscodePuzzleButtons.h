// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PasscodePuzzleButtons.generated.h"

UCLASS()
class VRDEVFUNDAMENTALS_API APasscodePuzzleButtons : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APasscodePuzzleButtons();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UMaterial* NormalMat;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UMaterial* SelectedMat;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<class APasscodePuzzleButtonLink> LineBlueprint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void ButtonBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, class APasscodePuzzleButtonLink* Link);

	UFUNCTION(BlueprintCallable)
		class APasscodePuzzleButtonLink* ButtonEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor);
};
