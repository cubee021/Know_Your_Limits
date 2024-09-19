// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyRing.generated.h"

/**
* 캐릭터가 획득하면 Max Speed 증가
* Ring -> Coin으로 이름 변경(해야되는데 혼용중)
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
	/** 플레이어와 오버랩 시 플레이어의 속도 증가 */
	UFUNCTION()
		void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& Sweepresult);

	FTimerHandle RespawnTimerHandle;
	/** 코인 습득 후 리스폰까지 걸리는 시간 */
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
