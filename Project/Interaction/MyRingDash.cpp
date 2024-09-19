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

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("SPLINE"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));

	RootComponent = SceneComponent;
	Spline->SetupAttachment(SceneComponent);
	Trigger->SetupAttachment(Spline);

	Trigger->SetCollisionProfileName(TEXT("MyCollectible")); 
	Trigger->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));

	Spline->Duration = 3.f;
	Spline->bDrawDebug = true;
}

void AMyRingDash::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMyRingDash::OnCharacterOverlap);
}

// Called every frame
void AMyRingDash::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsKeyPressed)
	{
		MoveAlongSpline(DeltaTime);
	}
}

void AMyRingDash::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweepresult)
{
	// MyCharacter가 Trigger 안에서 키 누르면 MoveAlongSpline 시작
	MyCharacter = Cast<AMyCharacter>(OtherActor);
	if (MyCharacter)
	{
		MyCharacter->OnFlyAlongSpline.AddLambda([this]()
			{
				if (!IsKeyPressed && OnOverlap)
				{
					StartTime = GetWorld()->GetTimeSeconds();

					IsKeyPressed = true;
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
		CurrentSplineTime = (GetWorld()->GetTimeSeconds() - StartTime) / Spline->Duration;

		// 속도에 따른 다음 거리 계산
		float Distance = Spline->GetSplineLength() * CurrentSplineTime;
		// 거리에 맞는 Location 구하기
		FVector Position = Spline->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
		
		MyCharacter->SetActorLocation(Position);
	}
	else
	{
		CurrentSplineTime = 0.f;
		StartTime = 0.f;
		IsKeyPressed = false;
	}
}

