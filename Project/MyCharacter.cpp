// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "MyEnemy.h"
#include "MyWalkingCharacter.h"
#include "MyUserWidget.h"
#include "GameOverUserWidget.h"
#include "ProjectGameModeBase.h"
#include "MyAnimInstance.h"
#include "MyRingDash.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerInput.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"
#include "Components/AudioComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "MySaveGame.h"
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
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AUDIO"));

	// 계층구조 설정
	SpringArm->SetupAttachment(GetCapsuleComponent()); // 캐릭터에 스프링암 부착
	Camera->SetupAttachment(SpringArm); // 스프링암에 카메라 부착

	// 스프링암 길이 및 각도 설정
	SpringArm->TargetArmLength = 500.f;
	SpringArm->SetRelativeRotation(FRotator(-35.f, 0.f, 0.f));
	SpringArm->bUsePawnControlRotation = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);

	Camera->bUsePawnControlRotation = false;

	// 캐릭터 위치 및 각도 설정
	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	// 캐릭터 메시 불러오기
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
		SecondJumpSound = SB2.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> SB3(TEXT("SoundWave'/Game/Sounds/wind-blowing-75240.wind-blowing-75240'"));
	if (SB3.Succeeded())
	{
		BoostSound = SB3.Object;
	}

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS(TEXT("NiagaraSystem'/Game/Graphics/BlinkAndDashVFX/VFX_Niagara/NS_Dash_Mana.NS_Dash_Mana'"));
	if (NS.Succeeded())
	{
		NS_Boost = NS.Object;
	}

	GetCharacterMovement()->MaxWalkSpeed = 1000.f;

	isFalling = GetCharacterMovement()->IsFalling();

}


// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	QueryAchievements();

	PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		if (PlayerController->PlayerCameraManager)
		{
			PlayerController->PlayerCameraManager->ViewPitchMin = -40.0;
			PlayerController->PlayerCameraManager->ViewPitchMax = 30.0;
		}
	}

	AnimInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
	AnimInstance->OnMontageEnded.AddDynamic(this, &AMyCharacter::OnAttackMontageEnded);

	GameMode = Cast<AProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		MainHUD = Cast<UMyUserWidget>(GameMode->CurrentWidget);
		GameOverHUD = Cast<UGameOverUserWidget>(GameMode->CurrentWidget2);

	}
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update if character is falling 
	isFalling = GetCharacterMovement()->IsFalling();
	
	// Update timer and speedometer HUD
	if (MainHUD)
	{
		int32 IntegerFromTime = GetWorld()->GetTimeSeconds() / 1;
		int32 MilliSec = (GetWorld()->GetTimeSeconds() - IntegerFromTime) * 100;

		Seconds = IntegerFromTime - (60 * CountSec);

		if (Seconds == 60 && (GetWorld()->GetTimeSeconds() - IntegerFromTime) < 0.1f)
		{
			Minutes++;
			CountSec++;

		}

		const FString TimeStr = FString::Printf(TEXT("Time %02d : %02d : %02d"), Minutes, Seconds, MilliSec);
		MainHUD->txt_Time->SetText(FText::FromString(TimeStr));

		const FString RingStr = FString::Printf(TEXT("%.f / %.f[km/h]"), GetVelocity().Size()/10, GetCharacterMovement()->MaxWalkSpeed/10);
		MainHUD->CollectedRing->SetText(FText::FromString(RingStr));
	}
	
	// Update if there is an enemy to homing attack or not 
	if (HomingAttackOn)
	{
		if (!isEnemyLocked)
		{
			SweepTrace();
		}
		else
		{
			ReachTarget(DeltaTime);

			// Character afloats for a while after destroying enemy 
			if (isStoppingInAir)
			{
				SetActorLocation(CurrentLocation);
				timer_1 -= DeltaTime;

				if (timer_1 < 0)
				{
					LaunchCharacter(FVector(0.f, 0.f, 500.f), false, true);

					isEnemyLocked = false;
					isStoppingInAir = false;
					timer_1 = 15;
				}
			}

		}
	}
	

	// Update if character is damaged
	if (isDamaged)
	{
		if (timer_2 > 0)
		{
			timer_2 -= DeltaTime;
		}
		else
		{
			EnableInput(PlayerController);
			isDamaged = false;
			timer_2 = 50;
		}
	}

	// Update if character is dead
	if (IsReadyToRespawn)
	{
		if (timer_3 > 0)
		{
			timer_3 -= DeltaTime;
		}
		else
		{
			IsDead = false;
			IsReadyToRespawn = false;
			GetCharacterMovement()->MaxWalkSpeed = 1000.f;
			GameOverHUD->SetVisibility(ESlateVisibility::Collapsed);
			EnableInput(PlayerController);
			timer_3 = 200;
		}
	}

	// Auto boost
	if (GetVelocity().Size() > 1999.f)
	{
		if (AutoBoostCount == 0)
		{
			if (!isFalling)
			{
				AudioComponent->SetSound(BoostSound);
				AudioComponent->Play();

				BoostNiagara = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NS_Boost,
					GetActorLocation(), GetActorRotation());
				BoostNiagara->Activate();

				AutoBoostCount++;
			}
		}
	}
	else
	{
		if (AutoBoostCount == 1)
		{
			AudioComponent->FadeOut(2.f, 0.f);

			AutoBoostCount = 0;

		}


	}
	
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

	PlayerInputComponent->BindAction(TEXT("HomingAttack"), EInputEvent::IE_Pressed, this, &AMyCharacter::HomingAttack);
	PlayerInputComponent->BindAction(TEXT("HomingAttack"), EInputEvent::IE_Released, this, &AMyCharacter::HomingAttack);

	PlayerInputComponent->BindAction(TEXT("RingDash"), EInputEvent::IE_Pressed, this, &AMyCharacter::RingDash);

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

	UGameplayStatics::PlaySoundAtLocation(this, JumpSound, GetActorLocation());

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
			if (GetVelocity().Size() > 1999.f)
			{
				AudioComponent->SetSound(BoostSound);
				AudioComponent->Play();

				BoostNiagara = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NS_Boost,
					GetActorLocation(), GetActorRotation());
				BoostNiagara->Activate();

				LaunchCharacter(FVector(GetCapsuleComponent()->GetForwardVector().X * 3000.f, 
					GetCapsuleComponent()->GetForwardVector().Y * 3000.f, 500.f), true, true);

				AutoBoostCount = 1;
			}
			else
			{
				UGameplayStatics::PlaySoundAtLocation(this, SecondJumpSound, GetActorLocation());

				LaunchCharacter(FVector(GetCapsuleComponent()->GetForwardVector().X * 1000.f,
					GetCapsuleComponent()->GetForwardVector().Y * 1000.f, 500.f), true, true);
			}
		}
	}
}

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
		isStoppingInAir = true;
	}
}

void AMyCharacter::HomingAttack()
{
	if (IsAttacking)
	{
		return;
	}

	AnimInstance->PlayAttackMontage();
	AnimInstance->JumpToSection(AttackIndex);
	AttackIndex = (AttackIndex + 1) % 2;
	
	IsAttacking = true;

	if (OnLockEnemy != NULL)
	{
		isEnemyLocked = true;
	}
}

void AMyCharacter::SweepTrace()
{
	TArray<FHitResult> OutHits;

	FVector Start = GetTransform().GetLocation();
	FVector End = GetTransform().GetLocation();

	FCollisionShape MyColSphere = FCollisionShape::MakeSphere(500.f);
	FCollisionQueryParams CollisionParams; // ignore
	FCollisionObjectQueryParams CollisionObjectTypes; // detect

	CollisionParams.AddIgnoredActor(this);

	CollisionObjectTypes.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel3);

	//DrawDebugSphere(GetWorld(), Start, MyColSphere.GetSphereRadius(), 100, FColor::Purple, true);

	bool isHit = GetWorld()->SweepMultiByObjectType(OutHits, Start, End, FQuat::Identity, CollisionObjectTypes, MyColSphere, CollisionParams); // toggle quat :  FQuat::Identity

	AActor* ActorToProcess;
	if (isHit) //충돌 시 outhits 배열에 목록 저장
	{
		
		for (int32 i = 0; i < OutHits.Num(); ++i) //하나씩 꺼내서
		{
			ActorToProcess = OutHits[i].GetActor(); //actortoprocess에 지정
			if (ActorToProcess)
			{
				if (dynamic_cast<AActor*>(ActorToProcess)) //만약 actor면 이하 수행
				{
					OnLockEnemy = (AActor*)ActorToProcess;

					if (OnLockEnemy->IsA(AMyEnemy::StaticClass()))
					{
						FlyingEnemy = (AMyEnemy*)OnLockEnemy;

						FlyingEnemy->CrosshairOn();

					}

					if (OnLockEnemy->IsA(AMyWalkingCharacter::StaticClass()))
					{
						WalkingEnemy = (AMyWalkingCharacter*)OnLockEnemy;

						WalkingEnemy->CrosshairOn();
					}
					
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Hit Result: %s"), *OnLockEnemy->GetName()));

				}
			}
		}

	}
	else
	{
		OnLockEnemy = NULL;
	}
	
}

void AMyCharacter::RingDash()
{
	RingDashPressed.Broadcast();
}

void AMyCharacter::IncreaseSpeed()
{
	if (GetCharacterMovement()->MaxWalkSpeed == 3000.f)
	{
		return;
	}

	GetCharacterMovement()->MaxWalkSpeed += 100.f;

}

float AMyCharacter::GetMaxSpeed()
{
	return GetCharacterMovement()->MaxWalkSpeed;
}

void AMyCharacter::SetDestroyedEnemyCount(int32 NewEnemyCount)
{
	DestroyedEnemyCount = NewEnemyCount;
}

int32 AMyCharacter::GetDestroyedEnemyCount()
{
	return DestroyedEnemyCount;
}

void AMyCharacter::Damaged(AActor* AttackingEnemy)
{
	isDamaged = true;

	LaunchCharacter((GetActorLocation() - AttackingEnemy->GetActorLocation()) * 15.f, true, false);

	if (GetCharacterMovement()->MaxWalkSpeed > 600.f)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.f;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed -= 100.f;
	}
	

	DisableInput(PlayerController);
}

void AMyCharacter::GameOver()
{
	DisableInput(PlayerController);
	
	IsDead = true;
	//IsOnLambda = true;
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			if (GameOverHUD)
			{
				GameOverHUD->SetVisibility(ESlateVisibility::Visible);

				if (UMySaveGame* LoadGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("SaveSlot1"), 0)))
				{
					TeleportTo(LoadGame->PlayerLastLocation, LoadGame->PlayerLastRotation);
					//SetActorLocation(LoadGame->PlayerLastLocation);
					//SetActorRotation(LoadGame->PlayerLastRotation);
				}
			}
			
			IsReadyToRespawn = true;

		}), 3.f, false);


}

void AMyCharacter::StopTimer()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
}

void AMyCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
	OnCharacterAttackEnd.Broadcast(); // 이거 어따 쓰는겨
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

