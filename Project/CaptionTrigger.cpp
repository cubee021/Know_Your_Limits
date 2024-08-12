// Fill out your copyright notice in the Description page of Project Settings.


#include "CaptionTrigger.h"
#include "MyCharacter.h"
#include "CaptionWidget.h"
#include "ProjectGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Components/TextBlock.h"

// Sets default values
ACaptionTrigger::ACaptionTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	SetRootComponent(Trigger);

	static ConstructorHelpers::FObjectFinder<USoundBase> SB(TEXT("SoundWave'/Game/Sounds/collectcoin-6075.collectcoin-6075'"));
	if (SB.Succeeded())
	{
		CaptionSound = SB.Object;
	}

	WriteCaptionHere = "";
}

void ACaptionTrigger::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ACaptionTrigger::OnCharacterOverlap);
}

// Called when the game starts or when spawned
void ACaptionTrigger::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		MyHUD = Cast<UCaptionWidget>(GameMode->CurrentWidget4);
		if (MyHUD)
		{

		}
	}

}

void ACaptionTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (StartTimer)
	{
		if (Timer > 0)
		{
			Timer -= DeltaTime;
		}
		else
		{
			Timer = 230;
			StartTimer = false;
			IsShowedOnce = true;

			MyHUD->SetVisibility(ESlateVisibility::Collapsed);
		}

	}
}

void ACaptionTrigger::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweepresult)
{
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
	if (MyCharacter && !IsShowedOnce)
	{
		if (CaptionSoundOn)
		{
			if (!IsSoundPlayedOnce)
			{
				UGameplayStatics::PlaySoundAtLocation(this, CaptionSound, GetActorLocation());
				IsSoundPlayedOnce = true;
			}
			
		}

		MyHUD->SetVisibility(ESlateVisibility::Visible);

		const FString CaptionHere = FString::Printf(TEXT("%s"), *FString(WriteCaptionHere));
		MyHUD->Caption->SetText(FText::FromString(CaptionHere));

		StartTimer = true;

	}
}

