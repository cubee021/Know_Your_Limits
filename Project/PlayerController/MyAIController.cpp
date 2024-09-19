// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackBoardComponent.h"

AMyAIController::AMyAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("BehaviorTree'/Game/AI/BT_MyCharacter.BT_MyCharacter'"));
	if (BT.Succeeded())
	{
		BehaviorTree = BT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BB(TEXT("BlackboardData'/Game/AI/BB_MyCharacter.BB_MyCharacter'"));
	if (BB.Succeeded())
	{
		BlackboardData = BB.Object;
	}
}

void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BlackboardData, Blackboard))
	{
		if (RunBehaviorTree(BehaviorTree))
		{
			// UE_LOG(LogTemp, Warning, TEXT("Blackboard and BehaviorTree possess success!"));
		}
	}
}

void AMyAIController::OnUnPossess()
{
	Super::OnUnPossess();

}

