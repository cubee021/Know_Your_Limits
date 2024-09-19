// Copyright 2023. cubee021. All rights reserved.


#include "TitleScreenActor.h"
#include "PlayerController/MyPlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATitleScreenActor::ATitleScreenActor()
{
}

// Called when the game starts or when spawned
void ATitleScreenActor::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{

			UGameplayStatics::OpenLevel(this, FName("MainMenu"));

		}), 3.25f, false);
}

