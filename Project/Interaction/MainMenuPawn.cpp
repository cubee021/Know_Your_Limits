// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuPawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMainMenuPawn::AMainMenuPawn()
{
 	
}

// Called when the game starts or when spawned
void AMainMenuPawn::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
}



