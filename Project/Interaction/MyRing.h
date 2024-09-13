// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyRing.generated.h"

UCLASS()
class PROJECT_API AMyRing : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyRing();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	virtual void PostInitializeComponents() override;

private:
	/** 플레이어와 오버랩 시 플레이어의 속도 증가 */
	UFUNCTION()
		void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& Sweepresult);

	UPROPERTY(VisibleAnywhere)
		class USoundBase* RingSound;

	UPROPERTY(VisibleAnywhere)
		class UParticleSystem* Sparkle;

public:
	// Called every Frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* Trigger; // collision 감지


};
