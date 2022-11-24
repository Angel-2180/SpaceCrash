// Fill out your copyright notice in the Description page of Project Settings.


#include "EngineSlider.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <Runtime/UMG/Public/Components/ProgressBar.h>

void UEngineSlider::SetEngineSlider(float NewLife)
{
	FLinearColor Red = FLinearColor::Red;
	FLinearColor Cyan = FLinearColor(0.0f, 1.0f, 1.0f);
	float Life = FMath::Clamp(NewLife, 0.0f, 100);
	EngineProgressBar->SetPercent(Life / 100);
	EngineProgressBar->SetFillColorAndOpacity(InterpolateColor(Red, Cyan, Life / 100));
}

FLinearColor UEngineSlider::InterpolateColor(FLinearColor color1, FLinearColor color2, float NewLife)
{
	float fraction = FMath::Clamp((NewLife - LowRatio) * (1 / (HighRatio - LowRatio)), 0, 1);
	FLinearColor LerpedColor;
	LerpedColor.R = (color2.R - color1.R) * fraction + color1.R;
	LerpedColor.G = (color2.G - color1.G) * fraction + color1.G;
	LerpedColor.B = (color2.B - color1.B) * fraction + color1.B;
	return LerpedColor;
}
