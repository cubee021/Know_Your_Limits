// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Online.h"
#include "OnlineStats.h"
#include "GameFramework/Character.h"
#include "MyEnemy.h"
#include "MyWalkingCharacter.h"
#include "MySpring.h"
#include "MyCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FRingDashPressed);
DECLARE_MULTICAST_DELEGATE(FOnCharacterAttackEnd);

UCLASS()
class PROJECT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


/* character functions */
public:
	void UpDown(float Value);
	void LeftRight(float Value);

private:

	//점프 후 땅에 닿았는지
	virtual void Landed(const FHitResult& Hit) override;
	virtual void Jump() override;
	void DoubleJump();

public:
	//호밍어택은 스위치로 조절
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enable Skill")
		bool HomingAttackOn = false;

private:
	void ReachTarget(float DeltaTime);
	void HomingAttack();
	void SweepTrace();

	void RingDash();

public:
	void IncreaseSpeed();
	float GetMaxSpeed();

	void SetDestroyedEnemyCount(int32 NewEnemyCount);
	int32 GetDestroyedEnemyCount();

	void Damaged(AActor* AttackingEnemy);

	void GameOver();

public:
	UFUNCTION()
		void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);


/* properties, sources, variables */
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UCameraComponent* Camera;

private:
	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
		class UAudioComponent* AudioComponent;

	UPROPERTY(VisibleAnywhere)
		class USoundBase* JumpSound;

	UPROPERTY(VisibleAnywhere)
		class USoundBase* SecondJumpSound;

	UPROPERTY(VisibleAnywhere)
		class USoundBase* BoostSound;

	UPROPERTY(EditDefaultsOnly)
		class UNiagaraSystem* NS_Boost;

	UPROPERTY(VisibleAnywhere)
		class UNiagaraComponent* BoostNiagara;

	UPROPERTY()
		class UMyAnimInstance* AnimInstance;

	UPROPERTY(VisibleAnywhere)
		class AProjectGameModeBase* GameMode;

	UPROPERTY(VisibleAnywhere)
		class UMyUserWidget* MainHUD;

	UPROPERTY(VisibleAnywhere)
		class UGameOverUserWidget* GameOverHUD;

	UPROPERTY(VisibleAnywhere)
		APlayerController* PlayerController; 

	UPROPERTY(VisibleAnywhere)
		int32 CountSec = 0;

	UPROPERTY(VisibleAnywhere)
		int32 JumpCount = 0;

	UPROPERTY(VisibleAnywhere)
		int32 RingCount = 0;

	UPROPERTY(VisibleAnywhere)
		int32 DestroyedEnemyCount = 0;

	UPROPERTY()
		int32 AttackIndex = 0;

	UPROPERTY(VisibleAnywhere)
		AActor* OnLockEnemy;

	UPROPERTY(VisibleAnywhere)
		bool isEnemyLocked = false;

	UPROPERTY(VisibleAnywhere)
		FVector CurrentLocation;

	UPROPERTY(VisibleAnywhere)
		bool isStoppingInAir = false;

	UPROPERTY(VisibleAnywhere)
		int32 AutoBoostCount = 0;


public:
	UPROPERTY(VisibleAnywhere)
		int32 Minutes = 0;

	UPROPERTY(VisibleAnywhere)
		int32 Seconds = 0;

	UPROPERTY(VisibleAnywhere)
		bool isFalling;

	UPROPERTY(VisibleAnywhere)
		bool isDamaged = false;

	UPROPERTY()
		bool IsDead = false;

	UPROPERTY(VisibleAnywhere)
		bool IsAttacking;

	UPROPERTY(VisibleAnywhere)
		bool IsReadyToRespawn = false;


private:
	AMyEnemy* FlyingEnemy;

	AMyWalkingCharacter* WalkingEnemy;


private:
	FTimerHandle TimerHandle;


public:
	void StopTimer();

private:

	UPROPERTY(VisibleAnywhere)
		int32 timer_1 = 15;

	UPROPERTY(VisibleAnywhere)
		int32 timer_2 = 50;

	UPROPERTY(VisibleAnywhere)
		int32 timer_3 = 200;


/* Achievements*/
public:
	void QueryAchievements();
	void OnQueryAchievementsComplete(const FUniqueNetId& PlayerId, const bool bWasSuccessful);
	void UpdateAchievementProgress(const FString& Id, float Percent);

	FOnlineAchievementsWritePtr AchievementsWriteObjectPtr;

	void CampfireAchievement();
	void PickpocketAchievement();

/* delegate */
public:
	FRingDashPressed RingDashPressed;
	FOnCharacterAttackEnd OnCharacterAttackEnd;

};

