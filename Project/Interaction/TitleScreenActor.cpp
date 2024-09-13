// Copyright 2023. cubee021. All rights reserved.


#include "TitleScreenActor.h"
#include "PlayerController/MyPlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATitleScreenActor::ATitleScreenActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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

