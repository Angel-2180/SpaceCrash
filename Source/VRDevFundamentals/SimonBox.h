#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "MyInterface.h"
#include "IndexCollision.h"
#include "SimonBox.generated.h"

UCLASS()
class VRDEVFUNDAMENTALS_API ASimonBox : public AActor, public IMyInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASimonBox();

	// Create a root component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Simon Box")
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
		UMaterial* Box_On_Material;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
		UMaterial* Box_Off_Material;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* Face1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* Face2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* Face3;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* Face4;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* Face5;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* Face6;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
		TArray<UStaticMeshComponent*> Faces;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int NbrOfActiveFaces;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bPuzzleStarted;

	float Timer;

	float SubTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
		void Interact(USceneComponent* ControllerUsed);
	virtual void Interact_Implementation(USceneComponent* ControllerUsed) override;
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
		void StopInteract();
	virtual void StopInteract_Implementation() override;
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
};
