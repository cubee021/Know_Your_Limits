// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyCoinBag.generated.h"

/**
* 플레이어가 닿으면 랜덤으로 코인 제공(Max Speed 증가)
*/
UCLASS()
class PROJECT_API AMyCoinBag : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyCoinBag();

protected:
	virtual void PostInitializeComponents() override;

public:
	// Interact Section
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Trigger)
		class UBoxComponent* Trigger;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh)
		UStaticMeshComponent* Mesh;

protected:
	UFUNCTION()
		virtual void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& Sweepresult);

	/** Prevents Character overlaps more than one time */
	bool IsOverlappedAlready = false;

protected:
	// Sound Section
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Sound)
		class USoundBase* RingSound;

	void PlayRingSound();

};
