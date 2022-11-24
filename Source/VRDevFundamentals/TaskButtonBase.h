// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TaskButtonBase.generated.h"

UCLASS()
class VRDEVFUNDAMENTALS_API ATaskButtonBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATaskButtonBase();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<class ATaskButton*> ButtonList;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bTaskCompleted;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bTaskActive;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bPlayActiveSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
