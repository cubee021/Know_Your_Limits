// Copyright 2023. cubee021. All rights reserved.


#include "SteamAchievements/RobbedCoinBag.h"
#include "Character/MyCharacter.h"

void ARobbedCoinBag::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweepresult)
{
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
	if (MyCharacter)
	{
		if (!IsOverlappedAlready)
		{
			PlayRingSound();

			int32 RandomCount = FMath::RandRange(0, 20);

			for (int32 i = 0; i < RandomCount; i++)
			{
				if (MyCharacter->GetMaxSpeed() == 3000.f)
				{
					break;
				}

				MyCharacter->IncreaseMaxSpeed();
			}

			IsOverlappedAlready = true;

			MyCharacter->PickpocketAchievement();
		}
	}
}
