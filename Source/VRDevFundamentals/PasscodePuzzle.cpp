// Fill out your copyright notice in the Description page of Project Settings.


#include "PasscodePuzzle.h"
#include "PasscodePuzzleButtonComponent.h"
#include "Components/BoxComponent.h"
#include "PasscodePuzzleButtonLink.h"
#include "IndexCollision.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"

// Sets default values
APasscodePuzzle::APasscodePuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Panel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Panel"));
	RootComponent = Panel;
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(Panel);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &APasscodePuzzle::InPanel);
	Collider->OnComponentEndOverlap.AddDynamic(this, &APasscodePuzzle::OutsidePanel);
	ButtonList.Reserve(NbOfButton);
	for (int32 i = 0; i < NbOfButton; i++)
	{
		FString num = FString::FromInt(i);
		UPasscodePuzzleButtonComponent* NewButton = CreateDefaultSubobject<UPasscodePuzzleButtonComponent>(FName("Button" + num));
		NewButton->SetupAttachment(Panel);
		ButtonList.Add(NewButton);
	}

	GenerateAdjacentButton();
}

// Called when the game starts or when spawned
void APasscodePuzzle::BeginPlay()
{
	Super::BeginPlay();
	
	//TArray<UActorComponent*> myarray = GetComponentsByClass(UPasscodePuzzleButtonComponent::StaticClass());
	for (int32 i = 0; i < ButtonList.Num(); i++)
	{
		//UPasscodePuzzleButtonComponent* button = Cast<UPasscodePuzzleButtonComponent>(myarray[i]);
		ButtonList[i]->OnComponentBeginOverlap.AddDynamic(this, &APasscodePuzzle::ButtonBeginOverlap);
		ButtonList[i]->OnComponentEndOverlap.AddDynamic(this, &APasscodePuzzle::ButtonEndOverlap);
	}

	UPasscodePuzzleButtonComponent* PreviousButton = ButtonList[5];
	for (int32 j = 0; j < NbOfButtonNeededForCombination; j++)
	{
		UPasscodePuzzleButtonComponent* NextButton = GenerateRandomNumber(PreviousButton);
		PreviousButton = NextButton;
		ButtonCombination.Add(NextButton);
	}
}

// Called every frame
void APasscodePuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Line != nullptr && Index != nullptr)
	{
		if (Index->SphereCollider->IsActive())
		{
			Line->Spline->SetLocationAtSplinePoint(1, Index->GetActorLocation(), ESplineCoordinateSpace::World);
			Line->SplineMesh->SetEndPosition(Index->GetActorLocation());
		}
		else
		{
			for (int i = 0; i < ButtonList.Num(); i++)
			{
				ButtonList[i]->SetMaterial(0, NormalMat);
			}
			for (int i = 0; i < Links.Num(); i++)
			{
				Links[i]->Destroy();
			}
			Links.Empty();
			ButtonPressed.Empty();
			LastHitComponent = nullptr;
			CurrentHitComponent = nullptr;
			Line = nullptr;
		}
	}

	if (ButtonPressed.IsEmpty())
	{
		Timer += DeltaTime;
		if (Timer >= 10.0f)
		{
			Subtimer += DeltaTime;
			if (Subtimer >= 0.0f && Subtimer <= 1.0f)
			{
				ButtonCombination[0]->SetMaterial(0, SelectedMat);
			}

			else if (Subtimer >= 1.0f && Subtimer <= 2.0f)
			{
				ButtonCombination[0]->SetMaterial(0, NormalMat);
				ButtonCombination[1]->SetMaterial(0, SelectedMat);
			}

			else if (Subtimer >= 2.0f && Subtimer <= 3.0f)
			{
				ButtonCombination[1]->SetMaterial(0, NormalMat);
				ButtonCombination[2]->SetMaterial(0, SelectedMat);
			}

			else if (Subtimer >= 3.0f && Subtimer <= 4.0f)
			{
				ButtonCombination[2]->SetMaterial(0, NormalMat);
				ButtonCombination[3]->SetMaterial(0, SelectedMat);				
			}

			else if (Subtimer >= 4.0f && Subtimer <= 5.0f)
			{
				ButtonCombination[3]->SetMaterial(0, NormalMat);
				Timer = 0;
				Subtimer = 0;
			}
		}
	}

	else if (ButtonPressed.Num() == NbOfButtonNeededForCombination)
	{
		for (int i = 0; i < ButtonPressed.Num(); i++)
		{
			if (ButtonCombination[i] != ButtonPressed[i])
			{
				ButtonPressed.Empty();
				for (int j = 0; j < Links.Num(); j++)
				{
					Links[j]->Destroy();
				}
				Links.Empty();
				CurrentHitComponent->SetMaterial(0, NormalMat);
				CurrentHitComponent = nullptr;
				Line = nullptr;
				PlayFailedSound = true;
				return;
			}
		}	

		for (int i = 0; i < ButtonList.Num(); i++)
		{
			ButtonList[i]->SetMaterial(0, SelectedMat);
		}
		SetActorEnableCollision(false);
		SetActorTickEnabled(false);
		PlayCompletedSound = true;
	}

	else
	{
		Timer = 0;
		Subtimer = 0;
	}
}

void APasscodePuzzle::ButtonBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AIndexCollision* Finger = Cast<AIndexCollision>(OtherActor);
	if (Index != nullptr && Finger != nullptr)
	{
		if (Index->SphereCollider->IsActive() && LastHitComponent != OverlappedComp)
		{
			CurrentHitComponent = OverlappedComp;
			for (int i = 0; i < ButtonList.Num(); i++)
			{
				ButtonList[i]->SetMaterial(0, NormalMat);
			}
			OverlappedComp->SetMaterial(0, SelectedMat);
			PlayButtonSound = true;
			if (Line != nullptr)
			{
				Line->Spline->SetLocationAtSplinePoint(1, OverlappedComp->GetComponentLocation(), ESplineCoordinateSpace::World);
				Line->SplineMesh->SetEndPosition(OverlappedComp->GetComponentLocation());
				Line = nullptr;				
			}
			if (ButtonPressed.Num() != 0)
			{
				if (ButtonPressed[ButtonPressed.Num() - 1] != Cast<UPasscodePuzzleButtonComponent>(OverlappedComp))
					ButtonPressed.Add(Cast<UPasscodePuzzleButtonComponent>(OverlappedComp));
			}
			else
			{
				ButtonPressed.Add(Cast<UPasscodePuzzleButtonComponent>(OverlappedComp));
			}
		}
	}
}

void APasscodePuzzle::ButtonEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AIndexCollision* Finger = Cast<AIndexCollision>(OtherActor);
	if (Index != nullptr && Finger != nullptr)
	{
		if (Index->SphereCollider->IsActive() && LastHitComponent != OverlappedComp)
		{
			LastHitComponent = OverlappedComp;
			OverlappedComp->SetMaterial(0, NormalMat);
			APasscodePuzzleButtonLink* NewLink = GetWorld()->SpawnActor<APasscodePuzzleButtonLink>(LineBlueprint, OverlappedComp->GetComponentTransform());
			Line = NewLink;
			Line->Spline->SetLocationAtSplinePoint(0, OverlappedComp->GetComponentLocation(), ESplineCoordinateSpace::World);
			Line->Spline->SetLocationAtSplinePoint(1, Index->GetActorLocation(), ESplineCoordinateSpace::World);
			FVector StartPos;
			FVector StartTan;
			FVector EndPos;
			FVector EndTan;
			Line->Spline->GetLocationAndTangentAtSplinePoint(0, StartPos, StartTan, ESplineCoordinateSpace::World);
			Line->Spline->GetLocationAndTangentAtSplinePoint(1, EndPos, EndTan, ESplineCoordinateSpace::World);
			Line->SplineMesh->SetStartAndEnd(StartPos, StartTan, EndPos, EndTan);
			Links.Add(Line);
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, TEXT("AddLine"));
		} 
	}
}

void APasscodePuzzle::InPanel(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AIndexCollision* Finger = Cast<AIndexCollision>(OtherActor);
	if (Finger != nullptr)
	{
		Index = Finger;
	}
}

void APasscodePuzzle::OutsidePanel(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AIndexCollision* Finger = Cast<AIndexCollision>(OtherActor);
	if (Finger != nullptr)
	{
		Index = nullptr;
		for (int i = 0; i < Links.Num(); i++)
		{
			Links[i]->Destroy();
		}
		Links.Empty();
		ButtonPressed.Empty();
		PlayFailedSound = true;
		LastHitComponent = nullptr;
		CurrentHitComponent = nullptr;
		Line = nullptr;
	}
}

UPasscodePuzzleButtonComponent* APasscodePuzzle::GenerateRandomNumber(UPasscodePuzzleButtonComponent* PreviousButton)
{
	int RandomNum = rand() % PreviousButton->AdjacentButtons.Num();
	return PreviousButton->AdjacentButtons[RandomNum];
}

void APasscodePuzzle::GenerateAdjacentButton()
{
	for (int32 i = 0; i < ButtonList.Num(); i++)
	{
		if (i == 0)
		{
			ButtonList[i]->AdjacentButtons.Add(ButtonList[1]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[3]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[4]);
		}

		if (i == 1)
		{
			ButtonList[i]->AdjacentButtons.Add(ButtonList[0]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[2]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[3]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[4]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[5]);
		}

		if (i == 2)
		{
			ButtonList[i]->AdjacentButtons.Add(ButtonList[1]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[4]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[5]);
		}

		if (i == 3)
		{
			ButtonList[i]->AdjacentButtons.Add(ButtonList[0]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[1]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[4]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[6]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[7]);
		}

		if (i == 4)
		{
			ButtonList[i]->AdjacentButtons.Add(ButtonList[0]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[1]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[2]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[3]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[5]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[6]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[7]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[8]);
		}

		if(i == 5)
		{
			ButtonList[i]->AdjacentButtons.Add(ButtonList[1]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[2]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[4]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[7]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[8]);
		}

		if (i == 6)
		{
			ButtonList[i]->AdjacentButtons.Add(ButtonList[3]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[4]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[7]);
		}

		if (i == 7)
		{
			ButtonList[i]->AdjacentButtons.Add(ButtonList[3]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[4]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[5]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[6]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[8]);
		}

		if (i == 8)
		{
			ButtonList[i]->AdjacentButtons.Add(ButtonList[4]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[5]);
			ButtonList[i]->AdjacentButtons.Add(ButtonList[7]);
		}
	}
}
