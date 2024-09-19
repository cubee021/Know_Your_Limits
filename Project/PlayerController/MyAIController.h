// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AMyAIController : public AAIController
{
	GENERATED_BODY()
	

public:
	AMyAIController();


public:
	// AI Section
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

protected:
	UPROPERTY()
		class UBehaviorTree* BehaviorTree;

	UPROPERTY()
		class UBlackboardData* BlackboardData;
};
