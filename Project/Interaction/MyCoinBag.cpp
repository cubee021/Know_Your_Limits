// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCoinBag.h"
#include "Character/MyCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"


// Sets default values
AMyCoinBag::AMyCoinBag()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RING"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("StaticMesh'/Game/Graphics/Prototype_Project/Meshes/Icons/SM_CoinBag_01_1.SM_CoinBag_01_1'"));
	if (SM.Succeeded())
	{
		Mesh->SetStaticMesh(SM.Object);
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> SB(TEXT("SoundWave'/Game/Sounds/coin_c_02-102844.coin_c_02-102844'"));
	if (SB.Succeeded())
	{
		RingSound = SB.Object;
	}

	SetRootComponent(Mesh);
	Trigger->SetupAttachment(Mesh);

	Trigger->SetBoxExtent(FVector(30.0f, 30.0f, 30.0f));
	Trigger->SetRelativeLocation(FVector(0.f, 0.f, 40.f));

}

void AMyCoinBag::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMyCoinBag::OnCharacterOverlap);
}

void AMyCoinBag::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweepresult)
{
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
	if (MyCharacter)
	{
		if (!IsOverlappedAlready)
		{
			PlayRingSound();
	
			int32 RandomCount = FMath::RandRange(0, 20);

			for (int32 i = 0; i < RandomCount; i++)
			{
				if (MyCharacter->GetMaxSpeed() == 3000.f)
				{
					break;
				}

				MyCharacter->IncreaseMaxSpeed();
			}

			IsOverlappedAlready = true;

		}

	}

}

void AMyCoinBag::PlayRingSound()
{
	UGameplayStatics::PlaySoundAtLocation(this, RingSound, GetActorLocation());
}

