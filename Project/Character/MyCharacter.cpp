// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "MyEnemy.h"
#include "MyWalkingCharacter.h"
#include "UI/MyUserWidget.h"
#include "UI/GameOverUserWidget.h"
#include "Game/ProjectGameModeBase.h"
#include "Animation/MyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PlayerInput.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Save/MySaveGame.h"
#include "DrawDebugHelpers.h"
#include "Online.h"
#include "OnlineSubsystem.h"

#define ACH_CAMPFIRE FString("ACH_CAMPFIRE")
#define ACH_PICKPOCKET FString("ACH_PICKPOCKET")

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	SpringArm->SetupAttachment(GetCapsuleComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	Camera->SetupAttachment(SpringArm);

	// 3인칭 카메라 설정
	SpringArm->TargetArmLength = 500.f;
	SpringArm->SetRelativeRotation(FRotator(-35.f, 0.f, 0.f));
	SpringArm->bUsePawnControlRotation = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);

	Camera->bUsePawnControlRotation = false;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> US(TEXT("SkeletalMesh'/Game/Graphics/LPCreaturesPack1/Creatures/Mesh/LizardMinion/LizardMinion.LizardMinion'"));
	if (US.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(US.Object);
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> SB1(TEXT("SoundWave'/Game/Sounds/whoosh-6316.whoosh-6316'"));
	if (SB1.Succeeded())
	{
		JumpSound = SB1.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> SB2(TEXT("SoundWave'/Game/Sounds/character_Attack1.character_Attack1'"));
	if (SB2.Succeeded())
	{
		DoubleJumpSound = SB2.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> SB3(TEXT("SoundWave'/Game/Sounds/ring_drop.ring_drop'"));
	if (SB3.Succeeded())
	{
		DamageSound = SB3.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> SB4(TEXT("SoundWave'/Game/Sounds/wind-blowing-75240.wind-blowing-75240'"));
	if (SB4.Succeeded())
	{
		BoostSound = SB4.Object;
	}

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS(TEXT("NiagaraSystem'/Game/Graphics/BlinkAndDashVFX/VFX_Niagara/NS_Dash_Mana.NS_Dash_Mana'"));
	if (NS.Succeeded())
	{
		NS_Boost = NS.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("AnimMontage'/Game/Animations/Character_Montage.Character_Montage'"));
	if (AM.Succeeded())
	{
		AttackMontage = AM.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> SB5(TEXT("SoundWave'/Game/Sounds/whoosh-transitions-sfx-01-118227.whoosh-transitions-sfx-01-118227'"));
	if (SB5.Succeeded())
	{
		AttackSound = SB5.Object;
	}

	// 캐릭터 Mesh 위치 및 각도 설정
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AUDIO"));

	GetCharacterMovement()->MaxWalkSpeed = START_MAX_SPEED;
}


// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	QueryAchievements();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		if (PlayerController->PlayerCameraManager)
		{
			PlayerController->PlayerCameraManager->ViewPitchMin = -40.0;
			PlayerController->PlayerCameraManager->ViewPitchMax = 30.0;
		}
	}

	UMyAnimInstance* AnimInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
	AnimInstance->OnMontageEnded.AddDynamic(this, &AMyCharacter::OnAttackMontageEnded);

	AProjectGameModeBase* GameMode = Cast<AProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameOverWidget = Cast<UGameOverUserWidget>(GameMode->GameOverUserWidget);
	}
}

void AMyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	OnRespawnReady.AddUObject(this, &AMyCharacter::Respawn);
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 매 Tick마다 current speed 업데이트 
	OnCurrentSpeedChange.Broadcast(GetCurrentSpeed(), GetMaxSpeed());
	
	// Homing Attack if true
	if (HomingAttackOn)
	{
		if (IsEnemyLocked && IsHomingAttackKeyPressed)
		{
			ReachTarget(DeltaTime);
		}
		else
		{
			OverlappingEnemyTrace();
		}
	}
	
	// Check every tick if over or under BOOST_SPEED
	AutoBoost();
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMyCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMyCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("Yaw"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AMyCharacter::DoubleJump);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Released, this, &AMyCharacter::DoubleJump);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Released, this, &AMyCharacter::StopJumping);

	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AMyCharacter::Attack);
	PlayerInputComponent->BindAction(TEXT("HomingAttack"), EInputEvent::IE_Pressed, this, &AMyCharacter::HomingAttack);

	PlayerInputComponent->BindAction(TEXT("FlyAlongSpline"), EInputEvent::IE_Pressed, this, &AMyCharacter::FlyAlongSpline);

}


void AMyCharacter::UpDown(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
	
}

void AMyCharacter::LeftRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);

	}
}

void AMyCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	JumpCount = 0;
}

void AMyCharacter::Jump()
{
	Super::Jump();

	PlayJumpSound();

	JumpMaxHoldTime = 0.5f;
}

void AMyCharacter::DoubleJump()
{
	if (!GetCharacterMovement()->IsFalling())
	{
		Jump();
	}
	else
	{
		JumpCount++; // 스페이스바 release때 한 번, 다시 누를때 한 번

		if (JumpCount == 2)
		{
			// 더블점프 시 BOOST_SPEED를 넘었다면 AutoBoost
			if (GetVelocity().Size() > BOOST_SPEED)
			{
				StartAutoBoostEffects();

				LaunchCharacter(FVector(GetCapsuleComponent()->GetForwardVector().X * 3000.f, 
					GetCapsuleComponent()->GetForwardVector().Y * 3000.f, 500.f), true, true);

				IsBoosting = true;
			}
			else
			{
				PlayDoubleJumpSound();

				LaunchCharacter(FVector(GetCapsuleComponent()->GetForwardVector().X * 1000.f,
					GetCapsuleComponent()->GetForwardVector().Y * 1000.f, 500.f), true, true);
			}
		}
	}
}

void AMyCharacter::PlayJumpSound()
{
	UGameplayStatics::PlaySoundAtLocation(this, JumpSound, GetActorLocation());
}

void AMyCharacter::PlayDoubleJumpSound()
{
	UGameplayStatics::PlaySoundAtLocation(this, DoubleJumpSound, GetActorLocation());
}

// Proceed when HomingAttackOn = true only
void AMyCharacter::ReachTarget(float DeltaTime)
{
	if (GetDistanceTo(OnLockEnemy) > 130.f && OnLockEnemy)
	{
		CurrentLocation = GetActorLocation();

		FVector Direction = OnLockEnemy->GetActorLocation() - CurrentLocation;


		CurrentLocation += Direction * 10.f * DeltaTime;

		SetActorLocation(CurrentLocation);
	}
	else
	{
		IsEnemyLocked = false;
		OnLockEnemy = nullptr;

		IsHomingAttackKeyPressed = false;
	}
}

// Proceed when HomingAttackOn = true only
void AMyCharacter::HomingAttack()
{
	if (IsAttacking)
	{
		return;
	}

	if (::IsValid(OnLockEnemy))
	{
		IsHomingAttackKeyPressed = true;
		IsEnemyLocked = true;
	}
}

// Proceed when HomingAttackOn = true only
void AMyCharacter::OverlappingEnemyTrace()
{
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(EnemyTrace), false, this);

	const float SearchRadius = 1000.f;
	const FVector Center = GetActorLocation();

	bool HitDetected = GetWorld()->OverlapMultiByChannel(OverlapResults, Center, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel4, FCollisionShape::MakeSphere(SearchRadius), Params);
	if (HitDetected)
	{
		for (auto& OverlapResult : OverlapResults)
		{
			if (OnLockEnemy == nullptr)
			{
				AMyEnemy* MyEnemy = Cast<AMyEnemy>(OverlapResult.GetActor());
				if (MyEnemy)
				{
					OnLockEnemy = OverlapResult.GetActor();
					return;
				}

				AMyWalkingCharacter* MyWalkingCharacter = Cast<AMyWalkingCharacter>(OverlapResult.GetActor());
				if (MyWalkingCharacter)
				{
					OnLockEnemy = OverlapResult.GetActor();
					return;
				}
			}
		}
	}
	else
	{
		OnLockEnemy = nullptr;
	}
	
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Hit Result: %s"), *OnLockEnemy->GetName()));
}

void AMyCharacter::FlyAlongSpline()
{
	OnFlyAlongSpline.Broadcast();
}

void AMyCharacter::Attack()
{
	PlayAttackMontage();
	PlayAttackSound();
}

void AMyCharacter::PlayAttackMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if(AnimInstance)
	{
		AnimInstance->StopAllMontages(0.f);
		AnimInstance->Montage_Play(AttackMontage);

		// Montage 총 인덱스 수. Montage에 애니메이션 추가하면 번호 바꿔줘야 함
		int TotalIndex = 2;

		SectionIndex = FMath::RandRange(0, TotalIndex - 1);

		FName Name = GetAttackMontageName(SectionIndex);
		AnimInstance->Montage_JumpToSection(Name, AttackMontage);
	}
}

void AMyCharacter::PlayAttackSound()
{
	UGameplayStatics::PlaySoundAtLocation(this, AttackSound, GetActorLocation());
}

FName AMyCharacter::GetAttackMontageName(int32 InSectionIndex)
{
	return FName(*FString::Printf(TEXT("Attack%d"), InSectionIndex));
}

void AMyCharacter::AutoBoost()
{
	if (GetVelocity().Size() > BOOST_SPEED)
	{
		if (!IsBoosting)
		{
			if (!IsFalling())
			{
				StartAutoBoostEffects();

				IsBoosting = true;
			}
		}
	}
	else
	{
		if (IsBoosting)
		{
			AudioComponent->FadeOut(2.f, 0.f);

			IsBoosting = false;
		}
	}
}

void AMyCharacter::StartAutoBoostEffects()
{
	AudioComponent->SetSound(BoostSound);
	AudioComponent->Play();

	BoostNiagara = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NS_Boost,
		GetActorLocation(), GetActorRotation());
	BoostNiagara->Activate();
}

bool AMyCharacter::IsFalling()
{
	return GetCharacterMovement()->IsFalling();
}

void AMyCharacter::IncreaseMaxSpeed()
{
	if (GetMaxSpeed() == MAXIMUM_MAX_SPEED)
	{
		return;
	}

	SetMaxSpeed(GetMaxSpeed() + 100.f);
}

void AMyCharacter::SetMaxSpeed(float NewMaxSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewMaxSpeed;
}

const float AMyCharacter::GetCurrentSpeed()
{
	return GetVelocity().Size();
}

const float AMyCharacter::GetMaxSpeed()
{
	return GetCharacterMovement()->MaxWalkSpeed;
}

void AMyCharacter::SetDestroyedEnemyCount(int32 NewEnemyCount)
{
	DestroyedEnemyCount = NewEnemyCount;
}

const int32 AMyCharacter::GetDestroyedEnemyCount()
{
	return DestroyedEnemyCount;
}

void AMyCharacter::Damaged(FVector EnemyLocation)
{
	if (!IsDamaged)
	{
		PlayDamageSound();

		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		LaunchCharacter((GetActorLocation() - EnemyLocation) * 20.f, true, false);
		IsDamaged = true;

		GetWorldTimerManager().SetTimer(DamageTimerHandle, FTimerDelegate::CreateLambda([&]()
			{
				GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
				IsDamaged = false;
			}
		), 1.5f, false);

		// Max speed가 600보다 크면 600으로 낮추기. 600부터는 100씩 차감
		if (GetMaxSpeed() > DAMAGED_MAX_SPEED)
		{
			SetMaxSpeed(DAMAGED_MAX_SPEED);
		}
		else
		{
			SetMaxSpeed(FMath::Clamp(GetMaxSpeed() - 100.f, 0.f, MAXIMUM_MAX_SPEED));
		}
	}
}

void AMyCharacter::PlayDamageSound()
{
	UGameplayStatics::PlaySoundAtLocation(this, DamageSound, GetActorLocation());
}

void AMyCharacter::GameOver()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	IsDead = true;
	
	// 플레이어 dead animation 후에 Game Over 화면 띄우기
	GetWorld()->GetTimerManager().SetTimer(GameOverTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			if (GameOverWidget)
			{
				GameOverWidget->SetVisibility(ESlateVisibility::Visible);

				if (UMySaveGame* LoadGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("SaveSlot1"), 0)))
				{
					TeleportTo(LoadGame->PlayerLastLocation, LoadGame->PlayerLastRotation);
				}
			}
			
			OnRespawnReady.Broadcast();

		}), 3.f, false);
}

void AMyCharacter::Respawn()
{
	// Game Over화면 지속 후 없어지면 플레이어 활동 재개 
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, FTimerDelegate::CreateLambda([&]()
		{

			IsDead = false;
			SetMaxSpeed(START_MAX_SPEED);
			GameOverWidget->SetVisibility(ESlateVisibility::Collapsed);
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

		}), 3.f, false);
}

void AMyCharacter::UpdateWidgetSpeedometer(UMyUserWidget* MyUserWidget)
{
	if (MyUserWidget)
	{
		MyUserWidget->UpdateSpeedometer(GetCurrentSpeed(), GetMaxSpeed());
		OnCurrentSpeedChange.AddUObject(MyUserWidget, &UMyUserWidget::UpdateSpeedometer);
	}
}

void AMyCharacter::StopTimer()
{
	GetWorldTimerManager().ClearTimer(GameOverTimerHandle);
}

void AMyCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
}

void AMyCharacter::QueryAchievements()
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();

	if (OnlineSub)
	{
		IOnlineIdentityPtr Identity = OnlineSub->GetIdentityInterface();

		if (Identity.IsValid())
		{
			
			TSharedPtr<const FUniqueNetId> UserId = Identity->GetUniquePlayerId(0);

		
			IOnlineAchievementsPtr Achievements = OnlineSub->GetAchievementsInterface();

			if (Achievements.IsValid())
			{
				
				Achievements->QueryAchievements(*UserId.Get(), FOnQueryAchievementsCompleteDelegate::CreateUObject(this, &AMyCharacter::OnQueryAchievementsComplete));
			}
		}
	}
}

void AMyCharacter::OnQueryAchievementsComplete(const FUniqueNetId& PlayerId, const bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		GLog->Log("achievements were cached");
		UE_LOG(LogTemp, Warning, TEXT("achievements were cached"));
	}
	else
	{
		GLog->Log("failed to cache achievements");
		UE_LOG(LogTemp, Warning, TEXT("failed to cache achievements"));
	}
}

void AMyCharacter::UpdateAchievementProgress(const FString& Id, float Percent)
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();

	if (OnlineSub)
	{
		IOnlineIdentityPtr Identity = OnlineSub->GetIdentityInterface();

		if (Identity.IsValid())
		{
			TSharedPtr<const FUniqueNetId> UserId = Identity->GetUniquePlayerId(0);

			IOnlineAchievementsPtr Achievements = OnlineSub->GetAchievementsInterface();


			if (Achievements.IsValid() && (!AchievementsWriteObjectPtr.IsValid() || !AchievementsWriteObjectPtr->WriteState != EOnlineAsyncTaskState::InProgress))
			{
				AchievementsWriteObjectPtr = MakeShareable(new FOnlineAchievementsWrite());
				AchievementsWriteObjectPtr->SetFloatStat(*Id, Percent);

				FOnlineAchievementsWriteRef AchievementsWriteObjectRef = AchievementsWriteObjectPtr.ToSharedRef();
				Achievements->WriteAchievements(*UserId, AchievementsWriteObjectRef);
			}
		}
	}
}

void AMyCharacter::CampfireAchievement()
{
	UpdateAchievementProgress(ACH_CAMPFIRE, 100.f);
}

void AMyCharacter::PickpocketAchievement()
{
	UpdateAchievementProgress(ACH_PICKPOCKET, 100.f);
}

