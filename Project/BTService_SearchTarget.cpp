// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SearchTarget.h"
#include "MyAIController.h"
#include "MyCharacter.h"
#include "MyWalkingCharacter.h"
#include "BehaviorTree/Blackboardcomponent.h"
#include "DrawDebugHelpers.h"
UBTService_SearchTarget::UBTService_SearchTarget()
{
	NodeName = TEXT("SearchTarget");
	Interval = 1.0f;
}

void UBTService_SearchTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (CurrentPawn == nullptr)
	{
		return;
	}

	AMyWalkingCharacter* WalkingCharacter = Cast<AMyWalkingCharacter>(CurrentPawn);
	if (WalkingCharacter)
	{
		if (WalkingCharacter->isDestroyed == true)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName(TEXT("IsDestroyed")), true);
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName(TEXT("IsDestroyed")), false);
		}
		
	}

	UWorld* World = CurrentPawn->GetWorld();
	FVector Center = CurrentPawn->GetActorLocation();
	float SearchRadius = 1500.f;

	if (World == nullptr)
	{
		return;
	}

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams QueryParams(NAME_None, false, CurrentPawn);

	bool bResult = World->OverlapMultiByChannel(OverlapResults, Center, FQuat::Identity, ECollisionChannel::ECC_EngineTraceChannel4,
												FCollisionShape::MakeSphere(SearchRadius), QueryParams);

	if (bResult)
	{
		for (auto& OverlapResult : OverlapResults)
		{
			if (AMyCharacter* MyCharacter = Cast<AMyCharacter>(OverlapResult.GetActor()))
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), MyCharacter);
			
				//DrawDebugSphere(World, Center, SearchRadius, 16, FColor::Green, false, 0.2f);

				return;
			}
			else
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), nullptr);
				//임시방편.. 콜리전에 캐릭터 말고 다른게 물리고 있음
			}
		}
	}

}

