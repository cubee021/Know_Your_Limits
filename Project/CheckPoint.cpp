// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckPoint.h"
#include "MySaveGame.h"
#include "MyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

// Sets default values
ACheckPoint::ACheckPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	SetRootComponent(Trigger);
}

void ACheckPoint::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ACheckPoint::OnCharacterOverlap);
}

// Called when the game starts or when spawned
void ACheckPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

