// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Materials/MaterialInterface.h"
#include "SliderActor.generated.h"

UCLASS()
class VRDEVFUNDAMENTALS_API ASliderActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASliderActor();

	UStaticMeshComponent* Mesh;

	UStaticMeshComponent* Slider;

	UStaticMeshComponent* Button;

	UPROPERTY(BlueprintReadWrite)
		float Progress = 0;

	UPROPERTY(BlueprintReadWrite)
		bool bActivated = false;

	UPROPERTY(EditAnywhere, Category = "Color")
		FLinearColor ActiveColor {
		0.0f, 0.9f, 1.0f, 0.0f
	};

	UPROPERTY(EditAnywhere, Category = "Color")
		FLinearColor InactiveColor {
		0.4f, 0.4f, 0.4f, 0.0f
	};

	UPROPERTY(EditAnywhere, Category = "Color")
		FLinearColor ButtonColor {
		0.75f, 0.9f, 1.0f, 1.0f
	};

	UPROPERTY(EditAnywhere, Category = "Color")
		FLinearColor OutsideColor {
		0.0f, 0.9f, 1.0f, 0.0f
	};

	UPROPERTY(EditAnywhere, Category = "TextureAndMaterials")
		UMaterialInterface* MaterialButtonType;

	UPROPERTY(EditAnywhere, Category = "TextureAndMaterials")
		UTexture* TextureButton;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void BeginOverLapping(AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
		void EndOverLapping(AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
		void Update();

private:

	UStaticMeshComponent* SliderComp;
	UStaticMeshComponent* ButtonComp;
	class AIndexCollision* Collider;

	void UpdateFromLocation(FVector Location);

	void SetButtonPos();
};
