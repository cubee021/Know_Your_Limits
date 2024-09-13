// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyEnemy.generated.h"

/*
* ���ڸ����� ���ٰ� �÷��̾ �ٰ����� �����ϴ� enemy
*/
UCLASS()
class PROJECT_API AMyEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyEnemy();

protected:
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere)
		class USphereComponent* Trigger;

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* Mesh;

	/** ����Ʈ���� MyEnemy�� �� ǥ�� */
	UPROPERTY(VisibleAnywhere)
		class UArrowComponent* Arrow;

protected:
	// Enemy State Section
	UFUNCTION()
	void OnCharacterHit(UPrimitiveComponent* HitComponent, 
		AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Skill Section
	/** Check every Tick if player is near this actor */
	bool DetectPlayer();
	/** �÷��̾� detect ������ ���ڸ� ȸ�� */
	void Patrol(float DeltaTime);
	/** �÷��̾ ���� �Ÿ��� ������ �÷��̾� ���� */
	void FocusOnPlayer(float DeltaTime);

	/* Location of detected player */
	FVector DetectedPlayerLocation;

public:
	/** True if enemy detected player */
	UPROPERTY(VisibleAnywhere)
		bool OnCombat;

protected:
	// Destroy Section
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Audio)
		class USoundBase* DestroySound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Particle)
		class UParticleSystem* Explosion;

	void EnemyDestroy();
	void StartDestroyEffects();
	
};
