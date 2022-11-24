// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabbableActor.h"
#include "Components/SceneComponent.h"

// Sets default values
AGrabbableActor::AGrabbableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;
}

// Called when the game starts or when spawned
void AGrabbableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGrabbableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrabbableActor::Interact_Implementation(USceneComponent* ControllerUsed)
{
	BaseMesh->SetSimulatePhysics(false);
	BaseMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	BaseMesh->AttachToComponent(ControllerUsed, FAttachmentTransformRules::KeepWorldTransform);
}

void AGrabbableActor::StopInteract_Implementation()
{
	BaseMesh->SetSimulatePhysics(true);
	BaseMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	BaseMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
}