// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalActor.h"
#include "MyCharacter.h"
#include "AmbientController.h"
#include "GoalScoreUserWidget.h"
#include "Components/BoxComponent.h"
#include "ProjectGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

// Sets default values
AGoalActor::AGoalActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));

	Trigger->SetCollisionProfileName(TEXT("MyCollectible"));
	Trigger->SetBoxExtent(FVector(300.0f, 300.0f, 100.0f));

	SetRootComponent(Trigger);

	static ConstructorHelpers::FObjectFinder<USoundBase> SB(TEXT("SoundWave'/Game/Sounds/outro1.outro1'"));
	if (SB.Succeeded())
	{
		OutroSound = SB.Object;
	}

}

void AGoalActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AGoalActor::OnCharacterOverlap);
}

// Called when the game starts or when spawned
void AGoalActor::BeginPlay()
{
	Super::BeginPlay();

	//CurrentMap = GetWorld()->GetName();
}

// Called every frame
void AGoalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsOverlapped)
	{
		if (MyHUD)
		{
			// 마이너스 값 되지 않게 0 리턴 만들것

			const FString Total = FString::Printf(TEXT("Total                                    %d%d%d%d%d"),
				Mili, Thou, Hund, Ten, One);
			MyHUD->txt_Total->SetText(FText::FromString(Total));

			if (Timer > 230)
			{
				if (Mili >= 9 || Thou >= 9 || Hund >= 9 || Ten >= 9 || One >= 9)
				{
					Mili = 0, Thou = 0, Hund = 0, Ten = 0, One = 0;
				}
				else
				{
					Mili++, Thou++, Hund++, Ten++, One++;
				}
			}
			else if (Timer > 190)
			{
				One = GetTotalScore() % 10;

				if (Mili >= 9 || Thou >= 9 || Hund >= 9 || Ten >= 9)
				{
					Mili = 0, Thou = 0, Hund = 0, Ten = 0;
				}
				else
				{
					Mili++, Thou++, Hund++, Ten++;
				}
			}
			else if (Timer > 150)
			{
				Ten = (GetTotalScore() % 100 - One) / 10;

				if (Mili >= 9 || Thou >= 9 || Hund >= 9)
				{
					Mili = 0, Thou = 0, Hund = 0;
				}
				else
				{
					Mili++, Thou++, Hund++;
				}
			}
			else if (Timer > 110)
			{
				Hund = (GetTotalScore() % 1000 - Ten*10) / 100;

				if (Mili >= 9 || Thou >= 9)
				{
					Mili = 0, Thou = 0;
				}
				else
				{
					Mili++, Thou++;
				}
			}
			else if (Timer > 70)
			{
				Thou = (GetTotalScore() % 10000 - Hund*100) / 1000;

				if (Mili >= 9)
				{
					Mili = 0;
				}
				else
				{
					Mili++;
				}
			}
			else if (Timer > 30)
			{
				Mili = GetTotalScore() / 10000;
			}
			Timer -= DeltaTime;

		}
		
	}
	

}

void AGoalActor::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweepresult)
{
	TArray<AActor*> FoundAmbientControllers;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAmbientController::StaticClass(), FoundAmbientControllers);
	for (auto AmbientController : FoundAmbientControllers)
	{
		AAmbientController* Ambient = Cast<AAmbientController>(AmbientController);
		if (Ambient)
		{
			if (Ambient->IsAmbientPlaying())
			{
				Ambient->StopAmbient();
			}
		}
	}

	MyCharacter = Cast<AMyCharacter>(OtherActor);
	if (MyCharacter)
	{
		AProjectGameModeBase* GameMode = Cast<AProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GameMode)
		{
			MyHUD = Cast<UGoalScoreUserWidget>(GameMode->CurrentWidget3);
			if (MyHUD)
			{
				const FString TimeScore = FString::Printf(TEXT("Time Score                                   %05d"), 
					GetTimeScore());
				MyHUD->txt_TimeScore->SetText(FText::FromString(TimeScore));
				
				const FString EnemyScore = FString::Printf(TEXT("Enemy Score                                   %05d"), 
					GetEnemyScore());
				MyHUD->txt_EnemyScore->SetText(FText::FromString(EnemyScore));

				const FString RingScore = FString::Printf(TEXT("  Max Speed                                    %05d"), 
					GetRingScore());
				MyHUD->txt_RingScore->SetText(FText::FromString(RingScore));
				
				IsOverlapped = true;

				MyHUD->SetVisibility(ESlateVisibility::Visible);
			}
		}
		
		UGameplayStatics::PlaySoundAtLocation(this, OutroSound, GetActorLocation());

		MyCharacter->Destroy();
	}
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			if (GetWorld()->GetName() == FString("Map_NorthenIsle_01"))
			{
				UGameplayStatics::OpenLevel(this, FName("Map_NorthenIsle_2"));
			}
			else if(GetWorld()->GetName() == FString("Map_NorthenIsle_2"))
			{
				UGameplayStatics::OpenLevel(this, FName("EndingScreen"));
			}

		}), 13.f, false);
}

int32 AGoalActor::GetTimeScore()
{
	int32 CalculateTimeScore = 99999 - MyCharacter->Minutes * 8000 - MyCharacter->Seconds * 10;
	if (CalculateTimeScore < 0)
	{
		return 0;
	}

	return CalculateTimeScore;
	
}

int32 AGoalActor::GetEnemyScore()
{
	return MyCharacter->GetDestroyedEnemyCount() * 1000;
}

int32 AGoalActor::GetRingScore()
{
	return MyCharacter->GetMaxSpeed();
}

int32 AGoalActor::GetTotalScore()
{
	return GetTimeScore() + GetEnemyScore() + GetRingScore();
}

