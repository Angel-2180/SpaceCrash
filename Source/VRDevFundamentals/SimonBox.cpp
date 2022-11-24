// Fill out your copyright notice in the Description page of Project Settings.

#include "SimonBox.h"

// Sets default values
ASimonBox::ASimonBox()
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

	Face4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Face 4"));
	Face4->SetupAttachment(BaseMesh);

	Face5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Face 5"));
	Face5->SetupAttachment(BaseMesh);

	Face6 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Face 6"));
	Face6->SetupAttachment(BaseMesh);

	Faces.Add(Face1);
	Faces.Add(Face2);
	Faces.Add(Face3);
	Faces.Add(Face4);
	Faces.Add(Face5);
	Faces.Add(Face6);

	NbrOfActiveFaces = 0;
}

// Called when the game starts or when spawned
void ASimonBox::BeginPlay()
{
	Super::BeginPlay();

	Face1->OnComponentBeginOverlap.AddDynamic(this, &ASimonBox::OnOverlapBegin);

	Face1->SetMaterial(0, Box_Off_Material);

	Face2->OnComponentBeginOverlap.AddDynamic(this, &ASimonBox::OnOverlapBegin);

	Face2->SetMaterial(0, Box_Off_Material);

	Face3->OnComponentBeginOverlap.AddDynamic(this, &ASimonBox::OnOverlapBegin);

	Face3->SetMaterial(0, Box_Off_Material);

	Face4->OnComponentBeginOverlap.AddDynamic(this, &ASimonBox::OnOverlapBegin);

	Face4->SetMaterial(0, Box_Off_Material);

	Face5->OnComponentBeginOverlap.AddDynamic(this, &ASimonBox::OnOverlapBegin);

	Face5->SetMaterial(0, Box_Off_Material);

	Face6->OnComponentBeginOverlap.AddDynamic(this, &ASimonBox::OnOverlapBegin);

	Face6->SetMaterial(0, Box_Off_Material);

	if (Faces.Num() > 0)
	{
		int32 LastIndex = Faces.Num() - 1;
		for (int32 i = 0; i <= LastIndex; ++i)
		{
			int32 Index = FMath::RandRange(i, LastIndex);
			if (i != Index)
			{
				Faces.Swap(i, Index);
			}
		}
	}
}

void ASimonBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AIndexCollision* finger = Cast<AIndexCollision>(OtherActor);
	UStaticMeshComponent* face = Cast<UStaticMeshComponent>(OverlappedComp);
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (finger->SphereCollider->IsActive())
		{
			if (NbrOfActiveFaces == Faces.Num())
			{
				//call end of puzzle event
				
				bPuzzleStarted = false;
			}
			else
			{
				if (face == Faces[NbrOfActiveFaces])
				{
					OverlappedComp->SetMaterial(0, Box_On_Material);
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Faecs: %i"), Faces.Num()));
					NbrOfActiveFaces++;
				}
			}
		}
	}
}

// Called every frame
void ASimonBox::Tick(float DeltaTime)
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
				Faces[0]->SetMaterial(0, Box_On_Material);
			}
			else if (SubTimer > 1.0f && SubTimer <= 2.0f)
			{
				Faces[0]->SetMaterial(0, Box_Off_Material);
				Faces[1]->SetMaterial(0, Box_On_Material);
			}
			else if (SubTimer > 2.0f && SubTimer <= 3.0f)
			{
				Faces[1]->SetMaterial(0, Box_Off_Material);
				Faces[2]->SetMaterial(0, Box_On_Material);
			}
			else if (SubTimer > 3.0f && SubTimer <= 4.0f)
			{
				Faces[2]->SetMaterial(0, Box_Off_Material);
				Faces[3]->SetMaterial(0, Box_On_Material);
			}
			else if (SubTimer > 4.0f && SubTimer <= 5.0f)
			{
				Faces[3]->SetMaterial(0, Box_Off_Material);
				Faces[4]->SetMaterial(0, Box_On_Material);
			}
			else if (SubTimer > 5.0f && SubTimer <= 6.0f)
			{
				Faces[4]->SetMaterial(0, Box_Off_Material);
				Faces[5]->SetMaterial(0, Box_On_Material);
			}
			else if (SubTimer > 6.0f && SubTimer <= 7.0f)
			{
				Faces[5]->SetMaterial(0, Box_Off_Material);
			}
		}
	}
}
void ASimonBox::Interact_Implementation(USceneComponent* ControllerUsed)
{
	bPuzzleStarted = true;
	BaseMesh->SetSimulatePhysics(false);
	BaseMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	BaseMesh->AttachToComponent(ControllerUsed, FAttachmentTransformRules::KeepWorldTransform);
}

void ASimonBox::StopInteract_Implementation()
{
	BaseMesh->SetSimulatePhysics(true);
	BaseMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	BaseMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
}