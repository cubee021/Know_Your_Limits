// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy.h"
#include "MyCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystem.h"
#include "DrawDebugHelpers.h"


// Sets default values
AMyEnemy::AMyEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("TRIGGER"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ARROW"));
	Explosion = CreateDefaultSubobject<UParticleSystem>(TEXT("EXPLOSION"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/Graphics/Orb_01/Meshes/SK_Orb_01.SK_Orb_01'"));
	if (SM.Succeeded())
	{
		Mesh->SetSkeletalMesh(SM.Object);
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> SB1(TEXT("SoundWave'/Game/Sounds/hit-to-the-can-88935.hit-to-the-can-88935'"));
	if (SB1.Succeeded())
	{
		DestroySound = SB1.Object;
	}

	SetRootComponent(Trigger);
	Mesh->SetupAttachment(Trigger);
	Arrow->SetupAttachment(Trigger);

	Arrow->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));

	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	Trigger->SetCollisionProfileName(TEXT("MyEnemy"));

	Trigger->SetRelativeLocation(FVector(0.f, 0.f, 60.f));
	Trigger->SetSphereRadius(70.f);
}

void AMyEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentHit.AddDynamic(this, &AMyEnemy::OnCharacterHit);
}

// Called every frame
void AMyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DetectPlayer())
	{
		FocusOnPlayer(DeltaTime);
	}
	else
	{
		Patrol(DeltaTime);
	}
}

void AMyEnemy::OnCharacterHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
	if (MyCharacter) 
	{
		// 플레이어가 점프중에 닿으면 enemy destroy, 아닐 경우 플레이어 damage
		if (MyCharacter->IsFalling())
		{
			MyCharacter->SetDestroyedEnemyCount(MyCharacter->GetDestroyedEnemyCount() + 1);

			EnemyDestroy();

		}
		else
		{
			if (MyCharacter->GetMaxSpeed() < DAMAGED_MAX_SPEED)
			{
				MyCharacter->GameOver();
			}
			else
			{
				MyCharacter->Damaged(GetActorLocation());
			}
		}
	}
}

bool AMyEnemy::DetectPlayer()
{
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Detect), false, this);

	const float DetectRadius = 1000.f;

	const FVector Center = GetActorLocation();
	
	bool HitDetected = GetWorld()->OverlapMultiByChannel(OverlapResults, Center, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel4, FCollisionShape::MakeSphere(DetectRadius), Params);
	if (HitDetected)
	{
		for (auto& OverlapResult : OverlapResults)
		{
			DetectedPlayerLocation = OverlapResult.GetActor()->GetActorLocation();
		}

		return true;
	}
	else
	{
		return false;
	}

	//DrawDebugSphere(GetWorld(), Center, DetectRadius, 16, FColor::Green, false, 10.f);
}

void AMyEnemy::Patrol(float DeltaTime)
{
	OnCombat = false;
	//UE_LOG(LogTemp, Warning, TEXT("..."));

	FRotator NewRotation = FRotator(0.f, DeltaTime * 40, 0.f);
	FQuat QuatRotation = FQuat(NewRotation);

	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}

void AMyEnemy::FocusOnPlayer(float DeltaTime)
{
	OnCombat = true;
	//UE_LOG(LogTemp, Warning, TEXT("OnCombat!"));

	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), DetectedPlayerLocation) + FRotator(0.f, 270.f, 0.f);
	FRotator NewEnemyRotation = FMath::RInterpTo(GetActorRotation(), LookAtRotation, DeltaTime, 2);

	SetActorRotation(NewEnemyRotation);
}

void AMyEnemy::EnemyDestroy()
{
	StartDestroyEffects();

	Destroy();
}

void AMyEnemy::StartDestroyEffects()
{
	UGameplayStatics::PlaySoundAtLocation(this, DestroySound, GetActorLocation());
	UGameplayStatics::SpawnEmitterAtLocation(this, Explosion, GetActorLocation());
}

