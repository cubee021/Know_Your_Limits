// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedCheckActor.h"
#include "Character/MyCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ASpeedCheckActor::ASpeedCheckActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	SetRootComponent(Trigger);
}

// Called when the game starts or when spawned
void ASpeedCheckActor::BeginPlay()
{
	Super::BeginPlay();
	
	DegreeSum.Init(0, TargetFloors.Num());
	IsAligned.Init(false, TargetFloors.Num());

	// 모든 Floor의 원래 FRotator 기록
	FloorOrigin.Init(FRotator(0, 0, 0), TargetFloors.Num());
	for (int32 i = 0; i < TargetFloors.Num(); i++)
	{
		FloorOrigin[i].Pitch = TargetFloors[i]->GetActorRotation().Pitch;
		FloorOrigin[i].Yaw = TargetFloors[i]->GetActorRotation().Yaw;
		FloorOrigin[i].Roll = TargetFloors[i]->GetActorRotation().Roll;
	}
}

// Called every frame
void ASpeedCheckActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// overlap 시 캐릭터의 속도 추적
	if (OnOverlap)
	{
		if (Character->GetVelocity().Size() > SpeedLimit + 99.99f)
		{
			IsOverSpeed = true;
		}
	}

	if (IsOverSpeed)
	{
		for (int32 i = 0; i < TargetFloors.Num(); i++)
		{
			if (TargetFloors[i])
			{
				DegreeSum[i] += DeltaTime * RotationSpeed;
				if (!IsAligned[i])
				{
					// 360도 전에는 DeltaTime * RotationSpeed로 회전.
					// 360도 직전에 Slerp를 이용해 Floor를 FloorOrigin에 맞춰 틀어지지 않도록 함
					if (DegreeSum[i] < 360)
					{
						FRotator NewRotation = FRotator(DeltaTime * RotationSpeed, 0, 0);
						FQuat QuatRotation = FQuat(NewRotation);

						TargetFloors[i]->AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
					}
					else
					{
						FRotator NewRotation = FRotator(FQuat::Slerp(TargetFloors[i]->GetActorRotation().Quaternion(),
							FRotator(FloorOrigin[i].Pitch, FloorOrigin[i].Yaw, FloorOrigin[i].Roll).Quaternion(), 0.99 * DeltaTime));

						TargetFloors[i]->SetActorRotation(NewRotation);

						if (TargetFloors[i]->GetActorRotation().Equals(FRotator(FloorOrigin[i].Pitch, FloorOrigin[i].Yaw, FloorOrigin[i].Roll), 0.1f))
						{
							IsAligned[i] = true;
						}
					}
				}

				// 모두 정렬되었으면 회전 종료
				bool IsAllTrue = true;
				for (int32 j = 0; j < IsAligned.Num(); j++)
				{
					IsAllTrue = IsAllTrue && IsAligned[j];
				}

				if (IsAllTrue)
				{
					DegreeSum.Init(0, TargetFloors.Num());
					IsAligned.Init(false, TargetFloors.Num());

					IsOverSpeed = false;
				}
			}
		}
	}
}

void ASpeedCheckActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
	if (MyCharacter)
	{
		Character = MyCharacter;
		ensure(Character);

		OnOverlap = true;
	}
}

void ASpeedCheckActor::NotifyActorEndOverlap(AActor* OtherActor)
{
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
	if (MyCharacter)
	{
		OnOverlap = false;
	}
}





