// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathTrigger.h"
#include "Character/MyCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
ADeathTrigger::ADeathTrigger()
{
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	SetRootComponent(Trigger);
}

void ADeathTrigger::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ADeathTrigger::OnCharacterOverlap);
}

void ADeathTrigger::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweepresult)
{
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
	if (MyCharacter)
	{
		MyCharacter->GameOver();
	}
}



