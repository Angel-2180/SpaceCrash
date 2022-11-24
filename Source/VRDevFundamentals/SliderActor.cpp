// Fill out your copyright notice in the Description page of Project Settings.

#include "SliderActor.h"
#include "IndexCollision.h"
#include "Kismet/KismetMaterialLibrary.h"

#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>

// Sets default values
ASliderActor::ASliderActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = Mesh;

	Slider = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Slider"));
	Slider->SetupAttachment(Mesh);
	Slider->SetVectorParameterValueOnMaterials(TEXT("ActiveColor"), FVector(ActiveColor.R, ActiveColor.G, ActiveColor.B));
	Slider->SetVectorParameterValueOnMaterials(TEXT("InactiveColor"), FVector(InactiveColor.R, InactiveColor.G, InactiveColor.B));
	Slider->SetScalarParameterValueOnMaterials(TEXT("Progress"), Progress);
	Button = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button"));
	Button->SetupAttachment(Mesh);
	SetButtonPos();
	Mesh->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(OutsideColor.R, OutsideColor.G, OutsideColor.B));

	if (MaterialButtonType != nullptr)
	{
		UMaterialInstanceDynamic* DynamicMaterial = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, MaterialButtonType);
		Button->SetMaterial(0, DynamicMaterial);
		DynamicMaterial->SetTextureParameterValue(TEXT("Icon"), TextureButton);
		DynamicMaterial->SetVectorParameterValue(TEXT("Color"), FVector(ButtonColor.R, ButtonColor.G, ButtonColor.B));
	}
}

// Called when the game starts or when spawned
void ASliderActor::BeginPlay()
{
	Super::BeginPlay();
	UMaterialInstanceDynamic* DynamicMaterial = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, MaterialButtonType);
	Button->SetMaterial(0, DynamicMaterial);
	DynamicMaterial->SetTextureParameterValue(TEXT("Icon"), TextureButton);
	DynamicMaterial->SetVectorParameterValue(TEXT("Color"), FVector(ButtonColor.R, ButtonColor.G, ButtonColor.B));
}

// Called every frame
void ASliderActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Progress >= 0.98)
	{
		Progress = 1;
		SetButtonPos();
		bActivated = true;
	}
}

void ASliderActor::BeginOverLapping(AActor* OtherActor)
{
	AIndexCollision* TestCollider = Cast<AIndexCollision>(OtherActor);
	if (TestCollider && !bActivated)
	{
		Collider = TestCollider;
	}
}

void ASliderActor::EndOverLapping(AActor* OtherActor)
{
	if (Collider == OtherActor && !bActivated)
	{
		Collider = nullptr;
	}
}

void ASliderActor::Update()
{
	if (Collider != nullptr && !bActivated)
	{
		if (Collider->SphereCollider->IsActive())
		{
			FVector NewLocation = UKismetMathLibrary::InverseTransformLocation(Slider->GetComponentTransform(), Collider->GetRootComponent()->GetComponentLocation());
			UpdateFromLocation(NewLocation);
		}
	}
}

void ASliderActor::UpdateFromLocation(FVector Location)
{
	if (!bActivated)
	{
		Progress = FMath::Clamp<float>(Location.X / 75.0f + 0.5f, 0.0f, 1.0f);
		SetButtonPos();
	}
}

void ASliderActor::SetButtonPos()
{
	if (!bActivated)
	{
		Slider->SetScalarParameterValueOnMaterials(TEXT("Progress"), Progress * 0.8f + 0.1f);
		Button->SetRelativeLocation(FVector(FMath::Clamp((Progress - 0.5f) * 75.0f, -37.5f, 37.5f), 0.0f, 0.0f));
	}
}