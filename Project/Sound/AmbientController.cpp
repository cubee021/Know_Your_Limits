// Fill out your copyright notice in the Description page of Project Settings.


#include "AmbientController.h"
#include "Components/AudioComponent.h"

// Sets default values
AAmbientController::AAmbientController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AUDIO"));

	static ConstructorHelpers::FObjectFinder<USoundBase> SB(TEXT("SoundWave'/Game/Sounds/081_G__Lange_Blumenlied_ver_1.081_G__Lange_Blumenlied_ver_1'"));
	if (SB.Succeeded())
	{
		Ambient = SB.Object;
	}
}

// Called when the game starts or when spawned
void AAmbientController::BeginPlay()
{
	Super::BeginPlay();

	AudioComponent->SetSound(Ambient);
	AudioComponent->Play();
	
}

void AAmbientController::StopAmbient()
{
	AudioComponent->Stop();
}

bool AAmbientController::IsAmbientPlaying()
{
	return AudioComponent->IsPlaying() ? true : false;
}

