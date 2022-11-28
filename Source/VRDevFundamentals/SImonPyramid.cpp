// Fill out your copyright notice in the Description page of Project Settings.

#include "SimonPyramid.h"
#include "IndexCollision.h"
#include "SimonPyramidBase.h"
#include "SpaceCrashGameInstance.h"
#include "Kismet/KismetArrayLibrary.h"

// Fill out your copyright notice in the Description page of Project Settings.

// Sets default values
ASimonPyramid::ASimonPyramid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("GROOT"));
	RootComponent = Root;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GrabbableMesh"));
	BaseMesh->SetupAttachment(Root);

	Face1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Face 1"));
	Face1->SetupAttachment(BaseMesh);

	Face2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Face 2"));
	Face2->SetupAttachment(BaseMesh);

	Face3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Face 3"));
	Face3->SetupAttachment(BaseMesh);

	Faces.Add(Face1);
	Faces.Add(Face2);
	Faces.Add(Face3);

	NbrOfActiveFaces = 0;
	bPlayCompletedSound = false;
}

// Called when the game starts or when spawned
void ASimonPyramid::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = Cast<USpaceCrashGameInstance>(GetGameInstance());
	BaseMesh->OnComponentBeginOverlap.AddDynamic(this, &ASimonPyramid::OnOverlapBaseBegin);
	BaseMesh->OnComponentEndOverlap.AddDynamic(this, &ASimonPyramid::OnOverlapBaseEnd);

	Face1->OnComponentBeginOverlap.AddDynamic(this, &ASimonPyramid::OnOverlapFaceBegin);

	Face1->SetMaterial(0, Pyramid_Off_Material);

	Face2->OnComponentBeginOverlap.AddDynamic(this, &ASimonPyramid::OnOverlapFaceBegin);

	Face2->SetMaterial(0, Pyramid_Off_Material);

	Face3->OnComponentBeginOverlap.AddDynamic(this, &ASimonPyramid::OnOverlapFaceBegin);

	Face3->SetMaterial(0, Pyramid_Off_Material);

	const int32 NumShuffles = Faces.Num() - 1;
	for (int32 i = 0; i < NumShuffles; ++i)
	{
		int32 SwapIdx = FMath::RandRange(i, NumShuffles);
		Faces.Swap(i, SwapIdx);
	}
}

void ASimonPyramid::OnOverlapFaceBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AIndexCollision* finger = Cast<AIndexCollision>(OtherActor);
	UStaticMeshComponent* face = Cast<UStaticMeshComponent>(OverlappedComp);
	if (finger != nullptr && face != nullptr)
	{
		if (OtherActor && (OtherActor != this) && OtherComp)
		{
			if (finger->SphereCollider->IsActive())
			{
				if (NbrOfActiveFaces == Faces.Num())
				{
					//call end of puzzle event
					bPlayCompletedSound = true;
					bPuzzleDone = true;
					bPuzzleStarted = false;
					SetActorTickEnabled(false);
				}
				else
				{
					if (face == Faces[NbrOfActiveFaces])
					{
						OverlappedComp->SetMaterial(0, Pyramid_On_Material);
						NbrOfActiveFaces++;
					}
					bPlayFailedSound = true;
				}
			}
		}
	}
}

void ASimonPyramid::OnOverlapBaseBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASimonPyramidBase* PyramidBaseCast = Cast<ASimonPyramidBase>(OtherActor);
	if (PyramidBaseCast != nullptr)
	{
		PyramidBase = PyramidBaseCast;
	}
}

void ASimonPyramid::OnOverlapBaseEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ASimonPyramidBase* PyramidBaseCast = Cast<ASimonPyramidBase>(OtherActor);
	if (PyramidBaseCast == nullptr)
	{
		PyramidBase = nullptr;;
	}
}

// Called every frame
void ASimonPyramid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bPuzzleStarted)
	{
		Timer += DeltaTime;
		if (Timer > 10.0f)
		{
			SubTimer += DeltaTime;
			if (SubTimer >= 0.0f && SubTimer <= 1.0f)
			{
				Faces[0]->SetMaterial(0, Pyramid_On_Material);
			}
			else if (SubTimer > 1.0f && SubTimer <= 2.0f)
			{
				Faces[0]->SetMaterial(0, Pyramid_Off_Material);
				Faces[1]->SetMaterial(0, Pyramid_On_Material);
			}
			else if (SubTimer > 2.0f && SubTimer <= 3.0f)
			{
				Faces[1]->SetMaterial(0, Pyramid_Off_Material);
				Faces[2]->SetMaterial(0, Pyramid_On_Material);
			}
			else if (SubTimer > 3.0f && SubTimer <= 4.0f)
			{
				Faces[2]->SetMaterial(0, Pyramid_Off_Material);
			}
		}
	}
}
void ASimonPyramid::Interact_Implementation(USceneComponent* ControllerUsed)
{
	if (GameInstance->bSecondPuzzleIsDone)
	{
		bPuzzleStarted = true;
		BaseMesh->SetSimulatePhysics(false);
		BaseMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		BaseMesh->AttachToComponent(ControllerUsed, FAttachmentTransformRules::KeepWorldTransform);
	}
}

void ASimonPyramid::StopInteract_Implementation()
{
	if (PyramidBase != nullptr)
	{
		BaseMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
		BaseMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		BaseMesh->AttachToComponent(PyramidBase->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
		BaseMesh->SetRelativeLocation(FVector(0, 0, 0));
		BaseMesh->SetRelativeRotation(FRotator(0, 0, 0));
		if (bPuzzleDone && GameInstance->bSecondPuzzleIsDone)
		{
			GameInstance->bThirdPuzzleIsDone = true;
			SetActorEnableCollision(false);
		}
	}
	else
	{
		BaseMesh->SetSimulatePhysics(true);
		BaseMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
		BaseMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}
}