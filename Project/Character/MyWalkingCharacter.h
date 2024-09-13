// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyWalkingCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEnd);

/*
* 지정 구역을 돌아다니다 플레이어를 따라오는 AI enemy
* Enemy인데 Character로 이름을 잘못붙임..
*/
UCLASS()
class PROJECT_API AMyWalkingCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyWalkingCharacter();

	FOnAttackEnd OnAttackEnd;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Trigger)
		class UCapsuleComponent* Trigger;

public:
	// Attack Section
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Montage)
		UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Audio)
		class USoundBase* AttackSound;

	void Attack();
	void PlayAttackMontage();
	void PlayAttackSound();

protected:
	// Walking Character State Section
	UFUNCTION()
		void OnCharacterHit(UPrimitiveComponent* HitComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComponent,
			FVector NormalImpulse, const FHitResult& Hit);

	FTimerHandle DestroyTimerHandle;

	/** True if Walking Character is attacking player */
	bool IsAttacking = false;
	/** True if Walking Character is already attacked by player.
	* Prevents Walking Character from player attack more than one time*/
	bool IsAlreadyAttacked = false;

public:
	/** Set Max speed of this character */
	void SetCharacterMaxSpeed(float NewMaxSpeed);

public:
	// Montage Section
	UFUNCTION()
		void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

protected:
	// Destroy Section
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Animation)
		UAnimSequence* DeadAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Particle)
		class UParticleSystem* Explosion;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Audio)
		class USoundBase* DestroySound;

	void PlayDeadAnimation();
	void PlayDestroyEffects();

public:
	/** True if Walking Character is Destroyed */
	bool isDestroyed = false;

};
