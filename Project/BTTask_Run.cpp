// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Run.h"
#include "MyAIController.h"
#include "MyWalkingCharacter.h"

UBTTask_Run::UBTTask_Run()
{
	bNotifyTick = false;
}

EBTNodeResult::Type UBTTask_Run::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto MyCharacter = Cast<AMyWalkingCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (MyCharacter == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	MyCharacter->SetCharacterMaxSpeed(700.f);


	return Result;
}
