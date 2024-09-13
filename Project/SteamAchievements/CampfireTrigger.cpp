// Copyright 2023. cubee021. All rights reserved.


#include "CampfireTrigger.h"
#include "Character/MyCharacter.h"
#include "Game/ProjectGameModeBase.h"
#include "UI/GameOverUserWidget.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACampfireTrigger::ACampfireTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	SetRootComponent(Trigger);
}

// Called when the game starts or when spawned
void ACampfireTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACampfireTrigger::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ACampfireTrigger::OnCharacterOverlap);
}

void ACampfireTrigger::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweepresult)
{
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
	if (MyCharacter)
	{
		MyCharacter->CampfireAchievement();
		MyCharacter->GameOver();

	}

}


