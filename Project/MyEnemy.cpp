// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy.h"
#include "MyCharacter.h"
#include "MyUserWidget.h"
#include "CrosshairUserWidget.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProjectGameModeBase.h"
#include "Components/WidgetComponent.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystem.h"


// Sets default values
AMyEnemy::AMyEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Enemy = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ENEMY"));
	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("TRIGGER"));
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ARROW"));
	Crosshair = CreateDefaultSubobject<UWidgetComponent>(TEXT("CROSSHAIR"));
	Explosion = CreateDefaultSubobject<UParticleSystem>(TEXT("EXPLOSION"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/Graphics/Orb_01/Meshes/SK_Orb_01.SK_Orb_01'"));
	if (SM.Succeeded())
	{
		Enemy->SetSkeletalMesh(SM.Object);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> UW(TEXT("WidgetBlueprint'/Game/UI/BP_Crosshair.BP_Crosshair_C'"));
	if (UW.Succeeded())
	{
		Crosshair->SetWidgetClass(UW.Class);
	}
	
	static ConstructorHelpers::FObjectFinder<USoundBase> SB1(TEXT("SoundWave'/Game/Sounds/hit-to-the-can-88935.hit-to-the-can-88935'"));
	if (SB1.Succeeded())
	{
		DestroySound = SB1.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> SB2(TEXT("SoundWave'/Game/Sounds/ring_drop.ring_drop'"));
	if (SB2.Succeeded())
	{
		RingDropSound = SB2.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> SB3(TEXT("SoundWave'/Game/Sounds/target_on.target_on'"));
	if (SB3.Succeeded())
	{
		CrosshairSound = SB3.Object;
	}

	SetRootComponent(Enemy);
	Trigger->SetupAttachment(Enemy);
	Crosshair->SetupAttachment(Enemy);
	Arrow->SetupAttachment(Trigger);

	Arrow->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));

	Enemy->SetCollisionProfileName(TEXT("MyEnemy"));
	Trigger->SetCollisionProfileName(TEXT("MyEnemy"));

	Trigger->SetRelativeLocation(FVector(0.f, 0.f, 60.f));
	Trigger->SetSphereRadius(70.f);

	Enemy->SetNotifyRigidBodyCollision(true);
	Trigger->SetNotifyRigidBodyCollision(true);

	Crosshair->SetWidgetSpace(EWidgetSpace::Screen);
	Crosshair->SetVisibility(false);

}

// Called when the game starts or when spawned
void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DetectPlayer(DeltaTime);

}

void AMyEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentHit.AddDynamic(this, &AMyEnemy::OnCharacterHit);

	//Crosshair->InitWidget();

}

void AMyEnemy::OnCharacterHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
	if (MyCharacter) 
	{
		if (MyCharacter->isFalling) // 캐릭터가 점프중에 닿아야만 enemy destroy
		{
			UGameplayStatics::PlaySoundAtLocation(this, DestroySound, GetActorLocation());
			UGameplayStatics::SpawnEmitterAtLocation(this, Explosion, GetActorLocation());

			int32 newEnemyCount = MyCharacter->GetDestroyedEnemyCount();
			MyCharacter->SetDestroyedEnemyCount(++newEnemyCount);

			Destroy();

		}
		else
		{
			if (MyCharacter->GetMaxSpeed() < 600.f)
			{
				MyCharacter->GameOver();
			}
			else
			{
				UGameplayStatics::PlaySoundAtLocation(this, RingDropSound, GetActorLocation());

				MyCharacter->Damaged(this);
			}
		}
	}
}


void AMyEnemy::DetectPlayer(float DeltaTime)
{
	AMyCharacter* Pawn = Cast<AMyCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (Pawn)
	{
		if(GetDistanceTo(Pawn) < 400.f)
		{
			OnCombat = true;
			//UE_LOG(LogTemp, Warning, TEXT("OnCombat!"));

			FVector PlayerLoc = Pawn->GetActorLocation();
			FRotator PlayerRot = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), PlayerLoc) + FRotator(0.f, 270.f, 0.f);

			FRotator NewEnemyRot = FMath::RInterpTo(Enemy->GetComponentRotation(), PlayerRot, DeltaTime, 2);

			Enemy->SetRelativeRotation(NewEnemyRot);

		}
		else
		{
			OnCombat = false;
			//UE_LOG(LogTemp, Warning, TEXT("..."));

			FRotator NewRotation = FRotator(0.f, DeltaTime * 40, 0.f);
			FQuat QuatRotation = FQuat(NewRotation);

			AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);

			CrosshairOff();

		}
		
	}
}

void AMyEnemy::CrosshairOn()
{
	if (CrosshairCount == 0) // 여전히 틱으로 윰직임
	{
		//UGameplayStatics::PlaySoundAtLocation(this, CrosshairSound, GetActorLocation());

		Crosshair->SetVisibility(true);

		CrosshairCount++;
	}
	
}

void AMyEnemy::CrosshairOff()
{
	Crosshair->SetVisibility(false);

	CrosshairCount = 0;
}

