// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWalkingCharacter.h"
#include "MyCharacter.h"
#include "Animation/MyWEnemyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerController/MyAIController.h"
#include "Particles/ParticleSystem.h"

// Sets default values
AMyWalkingCharacter::AMyWalkingCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Explosion = CreateDefaultSubobject<UParticleSystem>(TEXT("EXPLOSION"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/Graphics/Alien_Robot/Meshes/SK_Alien_Robot_Armor.SK_Alien_Robot_Armor'"));
	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> SB1(TEXT("SoundWave'/Game/Sounds/metalboom3-92559.metalboom3-92559'"));
	if (SB1.Succeeded())
	{
		DestroySound = SB1.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("AnimMontage'/Game/Animations/Alien_Robot_Skeleton_Montage.Alien_Robot_Skeleton_Montage'"));
	if (AM.Succeeded())
	{
		AttackMontage = AM.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> SB3(TEXT("SoundWave'/Game/Sounds/punch.punch'"));
	if (SB3.Succeeded())
	{
		AttackSound = SB3.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence> AS(TEXT("AnimSequence'/Game/Graphics/Alien_Robot/Animations/Anim_Death.Anim_Death'"));
	if (AS.Succeeded())
	{
		DeadAnimation = AS.Object;
	}

	Trigger = GetCapsuleComponent();

	Trigger->SetCapsuleSize(50.f, 100.f);
	Trigger->SetNotifyRigidBodyCollision(true);

	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	GetCharacterMovement()->MaxWalkSpeed = 300.f;

	// Set AI
	AIControllerClass = AMyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorld;
}

// Called when the game starts or when spawned
void AMyWalkingCharacter::BeginPlay()
{
	Super::BeginPlay();

	UMyWEnemyAnimInstance* AnimInstance = Cast<UMyWEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->OnMontageEnded.AddDynamic(this, &AMyWalkingCharacter::OnAttackMontageEnded);
	}
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
		// 플레이어가 점프중에 닿으면 enemy destroy, 아니면 플레이어 damage
		if (MyCharacter->IsFalling())
		{
			if (!IsAlreadyAttacked)
			{
				PlayDeadAnimation();
				PlayDestroyEffects();

				MyCharacter->SetDestroyedEnemyCount(MyCharacter->GetDestroyedEnemyCount() + 1);

				IsAlreadyAttacked = true;

				// Dead animation 후 destroy
				GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, FTimerDelegate::CreateLambda([&]()
					{
						isDestroyed = true;

						Destroy();

					}), 1.8f, false);
			}
		}
		else
		{
			if (MyCharacter->GetMaxSpeed() < DAMAGED_MAX_SPEED)
			{
				// Dead Walking Character가 플레이어 쪽으로 끌려와 여러번 GameOver되는 일 가끔 발생!
				MyCharacter->GameOver();
			}
			else
			{
				PlayAttackSound();
				MyCharacter->Damaged(GetActorLocation());
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

	PlayAttackMontage();

	IsAttacking = true;
}

void AMyWalkingCharacter::PlayAttackMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		if (!AnimInstance->Montage_IsPlaying(AttackMontage))
		{
			AnimInstance->Montage_Play(AttackMontage, 1.f);
		}
	}
}

void AMyWalkingCharacter::PlayAttackSound()
{
	UGameplayStatics::PlaySoundAtLocation(this, AttackSound, GetActorLocation());
}

void AMyWalkingCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
	OnAttackEnd.Broadcast();
}

void AMyWalkingCharacter::PlayDeadAnimation()
{
	GetMesh()->PlayAnimation(DeadAnimation, false);
}

void AMyWalkingCharacter::PlayDestroyEffects()
{
	UGameplayStatics::PlaySoundAtLocation(this, DestroySound, GetActorLocation());
	UGameplayStatics::SpawnEmitterAtLocation(this, Explosion, GetActorLocation());
}

void AMyWalkingCharacter::SetCharacterMaxSpeed(float NewMaxSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewMaxSpeed;
}
