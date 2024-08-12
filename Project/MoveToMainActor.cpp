// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveToMainActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMoveToMainActor::AMoveToMainActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMoveToMainActor::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{

			UGameplayStatics::OpenLevel(this, FName("MainMenu"));

		}), 7.f, false);
}


