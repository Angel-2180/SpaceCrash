// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyInterface.h"
#include "GrabbableActor.generated.h"

UCLASS()
class VRDEVFUNDAMENTALS_API AGrabbableActor : public AActor, public IMyInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrabbableActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interact")
	class UStaticMeshComponent* BaseMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	AActor* PreviousParent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void Interact(USceneComponent* ControllerUsed);
	virtual void Interact_Implementation(USceneComponent* ControllerUsed) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void StopInteract();
	virtual void StopInteract_Implementation() override;
};
