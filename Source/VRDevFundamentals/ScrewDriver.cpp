// Fill out your copyright notice in the Description page of Project Settings.

#include "ScrewDriver.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

// Sets default values
AScrewDriver::AScrewDriver()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = this->GetStaticMeshComponent();
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCol"));
	BoxCollision->SetupAttachment(this->GetStaticMeshComponent());
}

void AScrewDriver::Interact_Implementation(USceneComponent* ControllerUsed)
{
	UE_LOG(LogTemp, Warning, TEXT("ScrewDriver: Interact"));
	TimerOfTeleportation = 0;
	bIsInHand = true;
	this->GetStaticMeshComponent()->SetSimulatePhysics(false);
	this->GetStaticMeshComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	this->GetStaticMeshComponent()->AttachToComponent(ControllerUsed, FAttachmentTransformRules::KeepWorldTransform);
	this->SetActorRelativeLocation(FVector(-8, 0, 0));
	this->SetActorRelativeRotation(FRotator(90, 0, 180));
}

void AScrewDriver::StopInteract_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("ScrewDriver: StopInteract"));

	bIsInHand = false;
	bScrewFound = false;
	ActiveScrew = nullptr;
	bActivated = false;
	this->GetStaticMeshComponent()->SetSimulatePhysics(true);
	this->GetStaticMeshComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	this->GetStaticMeshComponent()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
}

void AScrewDriver::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsInHand)
	{
		if (bScrewFound)
		{
			if (bActivated)
			{
				//play sound for screwdriver
				if (ActiveScrew->AddRotationValue(deltaRotation))
				{
					UE_LOG(LogTemp, Warning, TEXT("Screwdriver: Screw is now fully rotated"));

					bScrewFound = false;
					ActiveScrew = nullptr;
				}
			}
		}
	}
	else
	{
		if (UKismetMathLibrary::Vector_Distance(this->GetActorLocation(), UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->K2_GetActorLocation()) >= 100.0f)
		{
			TimerOfTeleportation += DeltaSeconds;
			if (TimerOfTeleportation >= 5)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Teleporting");
				this->SetActorLocation(InitialPos);
				this->SetActorRotation(InitialRot);
				TimerOfTeleportation = 0;
			}
		}
	}
}

void AScrewDriver::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AScrewDriver::OnBeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AScrewDriver::OnEndOverlap);

	InitialRot = this->GetActorRotation();
	InitialPos = this->GetActorLocation();
}

void AScrewDriver::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AScrew* ColScrew = Cast<AScrew>(OtherActor);

	if (ColScrew)
	{
		UE_LOG(LogTemp, Warning, TEXT("ScrewDriver: OnBeginOverlap"));

		bScrewFound = true;
		ActiveScrew = ColScrew;
		ActiveScrew->AddRotationValue(deltaRotation);
	}
}

void AScrewDriver::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AScrew* ColScrew = Cast<AScrew>(OtherActor);
	if (ColScrew)
	{
		UE_LOG(LogTemp, Warning, TEXT("ScrewDriver: OnEndOverlap"));
		bScrewFound = false;
		ActiveScrew = nullptr;
	}
}