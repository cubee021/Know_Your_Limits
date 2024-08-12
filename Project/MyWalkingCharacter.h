// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyWalkingCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEnd);

UCLASS()
class PROJECT_API AMyWalkingCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyWalkingCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;


/* character functions */
private:
	UFUNCTION()
		void OnCharacterHit(UPrimitiveComponent* HitComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComponent,
			FVector NormalImpulse, const FHitResult& Hit);

public:
	void Attack();

	void CrosshairOn();
	void CrosshairOff();

public:
	UFUNCTION()
		void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void SetCharacterMaxSpeed(float NewMaxSpeed);

/* properties, sources, variables */
private:
	UPROPERTY(VisibleAnywhere)
		class UCapsuleComponent* Trigger;

	UPROPERTY(VisibleAnywhere)
		class UWidgetComponent* Crosshair;

	UPROPERTY(VisibleAnywhere)
		class USoundBase* DestroySound;

	UPROPERTY(VisibleAnywhere)
		class USoundBase* RingDropSound;

	UPROPERTY(VisibleAnywhere)
		class USoundBase* HitSound;

	UPROPERTY(VisibleAnywhere)
		UAnimSequence* DeathAnimation;

	UPROPERTY()
		class UMyWEnemyAnimInstance* AnimInstance;

	UPROPERTY()
		class AMyCharacter* Pawn;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class UParticleSystem* Explosion;

	bool isDestroyed = false;

private:
	bool IsAttacking = false;

	bool IsAlreadyAttacked = false;

private:
	FTimerHandle TimerHandle;


/* delegate */
public:
	FOnAttackEnd OnAttackEnd;

};
