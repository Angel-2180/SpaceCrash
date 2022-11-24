// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EngineSlider.generated.h"

/**
 * 
 */
UCLASS()
class VRDEVFUNDAMENTALS_API UEngineSlider : public UUserWidget
{
	GENERATED_BODY()

public:

		UPROPERTY(meta = (BindWidget))
		class UProgressBar* EngineProgressBar;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
			float LowRatio;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
			float HighRatio;

		UFUNCTION(BlueprintCallable)
		void SetEngineSlider(float NewLife);
		FLinearColor InterpolateColor(FLinearColor color1, FLinearColor color2, float NewLife);
};
