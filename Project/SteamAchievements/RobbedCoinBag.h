// Copyright 2023. cubee021. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/MyCoinBag.h"
#include "RobbedCoinBag.generated.h"

/**
 * ĳ���Ϳ� interact �� ACH_PICKPOCKET ��ǥ �޼�
 */
UCLASS()
class PROJECT_API ARobbedCoinBag : public AMyCoinBag
{
	GENERATED_BODY()
	
protected:
	virtual void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& Sweepresult) override;
};
