// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathTrigger.h"
#include "MyCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
ADeathTrigger::ADeathTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	SetRootComponent(Trigger);
}

void ADeathTrigger::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ADeathTrigger::OnCharacterOverlap);
}

// Called when the game starts or when spawned
void ADeathTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADeathTrigger::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweepresult)
{
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
	if (MyCharacter)
	{
		MyCharacter->GameOver();

	}
}



