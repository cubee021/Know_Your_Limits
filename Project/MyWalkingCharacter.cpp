// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWalkingCharacter.h"
#include "MyCharacter.h"
#include "MyUserWidget.h"
#include "MyWEnemyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectGameModeBase.h"
#include "MyAIController.h"
#include "Components/WidgetComponent.h"
#include "Particles/ParticleSystem.h"

// Sets default values
AMyWalkingCharacter::AMyWalkingCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Crosshair = CreateDefaultSubobject<UWidgetComponent>(TEXT("CROSSHAIR"));
	Explosion = CreateDefaultSubobject<UParticleSystem>(TEXT("EXPLOSION"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/Graphics/Alien_Robot/Meshes/SK_Alien_Robot_Armor.SK_Alien_Robot_Armor'"));
	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> UW(TEXT("WidgetBlueprint'/Game/UI/BP_Crosshair.BP_Crosshair_C'"));
	if (UW.Succeeded())
	{
		Crosshair->SetWidgetClass(UW.Class);
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> SB1(TEXT("SoundWave'/Game/Sounds/metalboom3-92559.metalboom3-92559'"));
	if (SB1.Succeeded())
	{
		DestroySound = SB1.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> SB2(TEXT("SoundWave'/Game/Sounds/ring_drop.ring_drop'"));
	if (SB2.Succeeded())
	{
		RingDropSound = SB2.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> SB3(TEXT("SoundWave'/Game/Sounds/punch.punch'"));
	if (SB3.Succeeded())
	{
		HitSound = SB3.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence> AS(TEXT("AnimSequence'/Game/Graphics/Alien_Robot/Animations/Anim_Death.Anim_Death'"));
	if (AS.Succeeded())
	{
		DeathAnimation = AS.Object;
	}

	Crosshair->SetupAttachment(GetMesh());
	Crosshair->SetWidgetSpace(EWidgetSpace::Screen);
	Crosshair->SetVisibility(false);

	Trigger = GetCapsuleComponent();

	Trigger->SetCapsuleSize(50.f, 100.f);
	Trigger->SetNotifyRigidBodyCollision(true);

	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	GetCharacterMovement()->MaxWalkSpeed = 300.f;

	AIControllerClass = AMyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorld;

}

// Called when the game starts or when spawned
void AMyWalkingCharacter::BeginPlay()
{
	Super::BeginPlay();

	Pawn = Cast<AMyCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	
	AnimInstance = Cast<UMyWEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	AnimInstance->OnMontageEnded.AddDynamic(this, &AMyWalkingCharacter::OnAttackMontageEnded);
}

// Called every frame
void AMyWalkingCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Pawn)
	{
		if (GetDistanceTo(Pawn) >= 400.f)
		{
			CrosshairOff();
		}
	}

}

// Called to bind functionality to input
void AMyWalkingCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyWalkingCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentHit.AddDynamic(this, &AMyWalkingCharacter::OnCharacterHit);
}

void AMyWalkingCharacter::OnCharacterHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
	if (MyCharacter)
	{
		if (MyCharacter->isFalling) // 캐릭터가 점프중에 닿아야만 enemy destroy
		{
			if (!IsAlreadyAttacked)
			{
				UGameplayStatics::PlaySoundAtLocation(this, DestroySound, GetActorLocation());
				UGameplayStatics::SpawnEmitterAtLocation(this, Explosion, GetActorLocation());

				int32 newEnemyCount = MyCharacter->GetDestroyedEnemyCount();
				MyCharacter->SetDestroyedEnemyCount(++newEnemyCount);

				GetMesh()->PlayAnimation(DeathAnimation, false);

				IsAlreadyAttacked = true;

				GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
					{
						isDestroyed = true;

						Destroy();

					}), 1.8f, false);
			}

		}
		else
		{
			if (MyCharacter->GetMaxSpeed() < 600.f)
			{
				// 신호 여러번 잡혀서 오류 날 수 있음
				MyCharacter->GameOver();
			}
			else
			{
				UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
				UGameplayStatics::PlaySoundAtLocation(this, RingDropSound, GetActorLocation());

				MyCharacter->Damaged(this);
			}
		}
	}
}

void AMyWalkingCharacter::Attack()
{
	if (IsAttacking)
	{
		return;
	}

	AnimInstance = Cast<UMyWEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->PlayAttackMontage();
	}

	IsAttacking = true;
}

void AMyWalkingCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
	OnAttackEnd.Broadcast();
}

void AMyWalkingCharacter::SetCharacterMaxSpeed(float NewMaxSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewMaxSpeed;
}

void AMyWalkingCharacter::CrosshairOn()
{
	Crosshair->SetVisibility(true);
}

void AMyWalkingCharacter::CrosshairOff()
{
	Crosshair->SetVisibility(false);
}