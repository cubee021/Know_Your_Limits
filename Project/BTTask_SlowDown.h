// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SlowDown.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UBTTask_SlowDown : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_SlowDown();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	
};
