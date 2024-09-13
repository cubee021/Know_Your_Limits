// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckPoint.h"
#include "Save/MySaveGame.h"
#include "Character/MyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

// Sets default values
ACheckPoint::ACheckPoint()
{
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	SetRootComponent(Trigger);
}

void ACheckPoint::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ACheckPoint::OnCharacterOverlap);
}

void ACheckPoint::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweepresult)
{
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
	if (MyCharacter)
	{
		UMySaveGame* SaveGame = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
		if (SaveGame)
		{
			SaveGame->PlayerLastLocation = MyCharacter->GetActorLocation();
			SaveGame->PlayerLastRotation = MyCharacter->GetActorRotation();

			if (!UGameplayStatics::SaveGameToSlot(SaveGame, TEXT("SaveSlot1"), 0))
			{
				UE_LOG(LogTemp, Error, TEXT("Checkpoint Error : File Save falied"));
			}
		}
	}

}

