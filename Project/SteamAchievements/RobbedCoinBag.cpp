// Copyright 2023. cubee021. All rights reserved.


#include "RobbedCoinBag.h"
#include "Character/MyCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ARobbedCoinBag::ARobbedCoinBag()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CoinBag = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RING"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("StaticMesh'/Game/Graphics/Prototype_Project/Meshes/Icons/SM_CoinBag_01_1.SM_CoinBag_01_1'"));
	if (SM.Succeeded())
	{
		CoinBag->SetStaticMesh(SM.Object);
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> SB(TEXT("SoundWave'/Game/Sounds/coin_c_02-102844.coin_c_02-102844'"));
	if (SB.Succeeded())
	{
		RingSound = SB.Object;
	}

	SetRootComponent(CoinBag);
	Trigger->SetupAttachment(CoinBag);

	Trigger->SetBoxExtent(FVector(30.0f, 30.0f, 30.0f));
	Trigger->SetRelativeLocation(FVector(0.f, 0.f, 40.f));
}

// Called when the game starts or when spawned
void ARobbedCoinBag::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARobbedCoinBag::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ARobbedCoinBag::OnCharacterOverlap);
}

// Called every frame
void ARobbedCoinBag::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARobbedCoinBag::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweepresult)
{
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
	if (MyCharacter)
	{
		if (!IsOverlappedAlready)
		{
			UGameplayStatics::PlaySoundAtLocation(this, RingSound, GetActorLocation());

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

			MyCharacter->PickpocketAchievement();

		}

	}
}


