// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AlienAIController.generated.h"

/**
 * 
 */
UCLASS()
class VRDEVFUNDAMENTALS_API AAlienAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	AAlienAIController(FObjectInitializer const& object_initializer = FObjectInitializer::Get());

	void BeginPlay() override;

	void OnPossess(APawn* const pawn) override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* btree;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* behavior_treeComponent;

	class UBlackboardComponent* blackboard;
};
