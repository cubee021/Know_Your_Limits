// Fill out your copyright notice in the Description page of Project Settings.


#include "MySpline_01.h"
#include "Components/SplineComponent.h"

// Sets default values
AMySpline_01::AMySpline_01()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("SPLINE"));

	RootComponent = SceneComponent;
	Spline->SetupAttachment(SceneComponent);

	Spline->Duration = 10.f;
	Spline->bDrawDebug = true;

	static ConstructorHelpers::FClassFinder<AActor> AA(TEXT("Blueprint'/Game/Blueprints/BP_FloatingFloor.BP_FloatingFloor_C'"));
	if (AA.Succeeded())
	{
		ActorToMoveClass = AA.Class;
	}

	ActorSize = FVector(1.f, 1.f, 1.f);
}

// Called when the game starts or when spawned
void AMySpline_01::BeginPlay()
{
	Super::BeginPlay();

	if (ActorToMoveClass)
	{
		// ¿ùµå¿¡ ActorToMove Spawn
		ActorToMove = GetWorld()->SpawnActor<AActor>(ActorToMoveClass, Spline->GetComponentTransform());
		if (ActorToMove)
		{
			ActorToMove->SetActorRotation(ActorRotation);
			ActorToMove->SetActorScale3D(ActorSize);

			StartTime = GetWorld()->GetTimeSeconds();
			bCanMoveActor = true;
		}
	}
}

// Called every frame
void AMySpline_01::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ActorToMove && bCanMoveActor)
	{
		float CurrentSplineTime = (GetWorld()->GetTimeSeconds() - StartTime) / Spline->Duration;

		float Distance = Spline->GetSplineLength() *CurrentSplineTime;

		FVector Position = Spline->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
		ActorToMove->SetActorLocation(Position);

		if (CurrentSplineTime >= 1.0f)
		{
			if (bSplineInLoop)
			{
				bCanMoveActor = true;

				StartTime = GetWorld()->GetTimeSeconds();

				CurrentSplineTime = (GetWorld()->GetTimeSeconds() - StartTime) / Spline->Duration;
			}
		}
	}
}

