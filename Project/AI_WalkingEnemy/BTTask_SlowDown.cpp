// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SlowDown.h"
#include "PlayerController/MyAIController.h"
#include "Character/MyWalkingCharacter.h"

UBTTask_SlowDown::UBTTask_SlowDown()
{
	bNotifyTick = false;
}

EBTNodeResult::Type UBTTask_SlowDown::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto MyCharacter = Cast<AMyWalkingCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (MyCharacter == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	MyCharacter->SetCharacterMaxSpeed(300.f);


	return Result;
}
