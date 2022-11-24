// Fill out your copyright notice in the Description page of Project Settings.


#include "HandTriggers.h"
#include "Kismet/GameplayStatics.h"
#include "AlienController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/ShapeComponent.h"
#include "VRPawn.h"

AHandTriggers::AHandTriggers()
{
	GetCollisionComponent()->OnComponentEndOverlap.AddDynamic(this, &AHandTriggers::HandsOutBounds);
}

void AHandTriggers::HandsOutBounds(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AVRPawn* CastTest;
	AActor* ParentActor = OtherActor->GetParentActor();
	if(ParentActor != nullptr)
		CastTest = Cast<AVRPawn>(ParentActor);
	else
		CastTest = Cast<AVRPawn>(OtherActor);

	if (CastTest != nullptr)
	{
		AAlienController* Alien = Cast<AAlienController>(UGameplayStatics::GetActorOfClass(GetWorld(), AAlienController::StaticClass()));
		UBlackboardComponent* BBComp = UAIBlueprintHelperLibrary::GetBlackboard(Alien);
		BBComp->SetValueAsBool("KillPlayer", true);
	}
}
