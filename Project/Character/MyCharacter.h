// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Online.h"
#include "OnlineStats.h"
#include "GameFramework/Character.h"
#include "Interaction/MySpring.h"
#include "Interface/MyUserWidgetInterface.h"
#include "MyCharacter.generated.h"

#define MAXIMUM_MAX_SPEED 3000.f
#define START_MAX_SPEED 1000.f
#define DAMAGED_MAX_SPEED 600.f

#define BOOST_SPEED 1999.f

DECLARE_MULTICAST_DELEGATE(FOnFlyAlongSpline);
DECLARE_MULTICAST_DELEGATE(FOnRespawnReady);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCurrentSpeedChange, float /*InCurrentSpeed*/, float /*InMaxSpeed*/);

UCLASS()
class PROJECT_API AMyCharacter : public ACharacter, public IMyUserWidgetInterface
{
	GENERATED_BODY()

public:
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Broadcast Spline trigger that player pressed the key to FlyAlongSpline */
	FOnFlyAlongSpline OnFlyAlongSpline;
	/** Broadcast if current speed has changed */
	FOnCurrentSpeedChange OnCurrentSpeedChange;
	/** Broadcast if this MyCharacter is ready to respawn */
	FOnRespawnReady OnRespawnReady;

public:
	// Camera Section 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class USpringArmComponent* SpringArm;

public:
	// Audio Section
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Audio)
		class UAudioComponent* AudioComponent;

protected:
	// Character Control Section
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Audio)
		class USoundBase* JumpSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Audio)
		class USoundBase* DoubleJumpSound;

	void UpDown(float Value);
	void LeftRight(float Value);
	virtual void Landed(const FHitResult& Hit) override;
	virtual void Jump() override;
	void DoubleJump();

	void PlayJumpSound();
	void PlayDoubleJumpSound();

	/** Count how many times Jump key is pressed. Turn to 0 if landed */
	int32 JumpCount = 0;
	/** Count how many enemies player has killed */
	int32 DestroyedEnemyCount = 0;

protected:
	// Attack Section
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Audio)
		class USoundBase* AttackSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Montage)
		UAnimMontage* AttackMontage;

	/** 캐릭터 공격 동작.
	* 캐릭터 파괴는 점프해서 하므로 실질적인 공격은 아님 */
	void Attack();
	void PlayAttackMontage();
	void PlayAttackSound();

	FName GetAttackMontageName(int32 SectionIndex);

	/** Current index of Montage section */
	int32 SectionIndex = 0;

protected:
	// Boost Section
	/** 지속되는 Boost Sound 관리 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Audio)
		class USoundBase* BoostSound;

	/** Character automatically start boost niagara effect and sound depends on BOOST_SPEED */
	void AutoBoost();
	void StartAutoBoostEffects();

	/** True if character is on boost */
	bool IsBoosting = false;

protected:
	// Fly Along Spline Section
	/** If key pressed, brodcast to spline to move character along */
	void FlyAlongSpline();

protected:
	// Homing Attack Section
	/** 
	* 소닉 대표 기술 Homing attack 구현 - 스팀 출시로는 부적절해서 사용x 
	* 공중에서 키를 누르면 연속으로 근처의 적에게 빠르게 날아가 공격 
	*/
	void HomingAttack();
	/** Find nearest MyEnemy or WalkingEnemy */
	void OverlappingEnemyTrace();
	/** Drag this character to the nearest enemy */
	void ReachTarget(float DeltaTime);

	/** True if Character can homing attack. 디폴트는 false */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = HomingAttack)
		bool HomingAttackOn = false;

	/** Result of SweepTrace. Nearest enemy */
	AActor* OnLockEnemy;
	/** True if the nearest enemy is set to OnLockEnemy */
	bool IsEnemyLocked = false;
	/** Character current location. Use this to get close to OnLockEnemy */
	FVector CurrentLocation;

	/** True if player pressed Homing Attack key */
	bool IsHomingAttackKeyPressed = false;
	/** True if character is attacking */
	bool IsAttacking;

public:
	// Character State Section
	bool IsFalling();

	/** Character max speed */
	void IncreaseMaxSpeed();
	const float GetMaxSpeed();
	void SetMaxSpeed(float NewMaxSpeed);

	/** Character current speed */
	const float GetCurrentSpeed();

	/** Total enemies destroyed by Character */
	void SetDestroyedEnemyCount(int32 NewEnemyCount);
	const int32 GetDestroyedEnemyCount();

public:
	// Damage, GameOver Section
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Audio)
		class USoundBase* DamageSound;

	/** Speed decrease when damaged by enemies */
	void Damaged(FVector EnemyLocation);
	void PlayDamageSound();

	/** Restart from saved location when dead */
	void GameOver();
	void Respawn();

	FTimerHandle DamageTimerHandle;
	FTimerHandle GameOverTimerHandle;
	FTimerHandle RespawnTimerHandle;

	/** True is character is currently on damage */
	bool IsDamaged = false;
	bool IsDead = false;

public:
	// Montage Section
	UFUNCTION()
		void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	/** Current index of attack montage */
	UPROPERTY()
		int32 AttackIndex = 0;

public:
	// Niagara Section 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Effect)
		class UNiagaraComponent* BoostNiagara;
	/** Effect when character boost */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Effect)
		class UNiagaraSystem* NS_Boost;

public:
	// UI Section
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI)
		class UGameOverUserWidget* GameOverWidget;

	/** Update Current speed and Max speed of MyUserWidget */
	virtual void UpdateWidgetSpeedometer(class UMyUserWidget* MyUserWidget) override;

public:
	/** Game Over 위젯이 나온 상태에서 Pause menu::RestartCurrentStage 시,
	* GameOverTimerHandle이 잔류하여 튕기는 현상 발생
	* 
	* 새 레벨을 부르기 전에 아래 함수로 멈춰줘야 함
	*/
	void StopTimer();

public:
	// Steam Achievements
	/** 온라인 서브 시스템 연결해서 플레이어의 achievements를 불러옴 */
	void QueryAchievements();
	/** achievements를 불러왔는지 여부 체크 */
	void OnQueryAchievementsComplete(const FUniqueNetId& PlayerId, const bool bWasSuccessful);
	/** 상태가 InProgress인 각 achievement의 진행 상황을 스팀에 업데이트  */
	void UpdateAchievementProgress(const FString& Id, float Percent);

	/** 해당 Achievement의 상태를 수정한 데이터 담은 포인터 */
	FOnlineAchievementsWritePtr AchievementsWriteObjectPtr;

	/** Achievement 1 - ACH_CAMPFIRE */
	void CampfireAchievement();
	/** Achievement 2 - ACH_PICKPOCKET */
	void PickpocketAchievement();

};

