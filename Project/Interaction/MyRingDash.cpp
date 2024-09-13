// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRingDash.h"
#include "Character/MyCharacter.h"
#include "Components/SplineComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AMyRingDash::AMyRingDash()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("SPLINE"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));

	RootComponent = Root;
	Spline->SetupAttachment(Root);
	Trigger->SetupAttachment(Spline);

	Trigger->SetCollisionProfileName(TEXT("MyCollectible")); 
	Trigger->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));

	Spline->Duration = TotalPathTime;
	Spline->bDrawDebug = true;

}

void AMyRingDash::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMyRingDash::OnCharacterOverlap);
}

// Called when the game starts or when spawned
void AMyRingDash::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyRingDash::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRingDash)
	{
		MoveAlongSpline(DeltaTime);
	}

}

void AMyRingDash::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweepresult)
{
	// 반응할 캐릭터 지정
	MyCharacter = Cast<AMyCharacter>(OtherActor);
	if (MyCharacter)
	{
		MyCharacter->OnFlyAlongSpline.AddLambda([this]()
			{
				if (!bRingDash && OnOverlap)
				{
					StartTime = GetWorld()->GetTimeSeconds();

					bRingDash = true;
				}
			});
		
	}
}

void AMyRingDash::NotifyActorBeginOverlap(AActor* OtherActor)
{
	AMyCharacter* Character = Cast<AMyCharacter>(OtherActor);
	if (Character)
	{
		OnOverlap = true;
	}
}

void AMyRingDash::NotifyActorEndOverlap(AActor* OtherActor)
{
	AMyCharacter* Character = Cast<AMyCharacter>(OtherActor);
	if (Character)
	{
		OnOverlap = false;
	}
}

void AMyRingDash::MoveAlongSpline(float DeltaTime)
{
	if (CurrentSplineTime < 1.0f)
	{
		CurrentSplineTime = (GetWorld()->GetTimeSeconds() - StartTime) / TotalPathTime;

		float Distance = Spline->GetSplineLength() * CurrentSplineTime;

		FVector Position = Spline->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
		
		MyCharacter->SetActorLocation(Position);
	}
	else
	{
		CurrentSplineTime = 0.f;
		StartTime = 0.f;
		bRingDash = false;
	}

}

