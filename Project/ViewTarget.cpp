// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewTarget.h"
#include "MyCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AViewTarget::AViewTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OVERLAPBOX"));
	OverlapBox->SetGenerateOverlapEvents(true);
	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &AViewTarget::OnOverlapBegin);
	//OverlapBox->OnComponentEndOverlap.AddDynamic(this, &AViewTarget::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AViewTarget::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
}

void AViewTarget::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
	if (MyCharacter)
	{
		if (CameraLocation)
		{
			PlayerController->SetViewTargetWithBlend(CameraLocation, BlendTime);
		}
	}

}


/*
void AViewTarget::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
	if (MyCharacter)
	{
		PlayerController->SetViewTargetWithBlend(PlayerController->GetPawn(), BlendTime);
	}

}
*/



