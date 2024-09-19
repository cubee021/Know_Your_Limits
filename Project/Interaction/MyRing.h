// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyRing.generated.h"

/**
* ĳ���Ͱ� ȹ���ϸ� Max Speed ����
* Ring -> Coin���� �̸� ����(�ؾߵǴµ� ȥ����)
*/
UCLASS()
class PROJECT_API AMyRing : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyRing();

protected:
	virtual void PostInitializeComponents() override;

public:
	// Called every Frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation)
		float RotateSpeed = 70.f;
public:
	// Interact Section
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UBoxComponent* Trigger;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh)
		UStaticMeshComponent* Mesh;

protected:
	/** �÷��̾�� ������ �� �÷��̾��� �ӵ� ���� */
	UFUNCTION()
		void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& Sweepresult);

	FTimerHandle RespawnTimerHandle;
	/** ���� ���� �� ���������� �ɸ��� �ð� */
	float RespawnTime = 10.f;

protected:
	// Sound Section
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Sound)
		class USoundBase* RingSound;

	void PlayRingSound();

protected:
	// Particle Section
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Particle)
		class UParticleSystem* SparkleParticle;

	void PlaySparkleParticle();

};
