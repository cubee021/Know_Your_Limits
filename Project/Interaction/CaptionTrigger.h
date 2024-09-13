// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CaptionTrigger.generated.h"

/**
* Caption appears when the player interacts trigger
*/
UCLASS()
class PROJECT_API ACaptionTrigger : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACaptionTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:
	//Interact Section
	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* Trigger;

	/** Caption widget */
	UPROPERTY(VisibleAnywhere)
		class UCaptionWidget* MyHUD;

protected:
	UFUNCTION()
		void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& Sweepresult);

	void OnDurationEnd();

	FTimerHandle DurationTimerHandle;

	/** How long this caption will be shown */
	float CaptionDuration = 3.f;

	/** True if this caption is already shown once */
	bool IsAlreadyShown = false;
	/** True if sound is already played once */
	bool IsSoundPlayedOnce = false;

protected:
	// String Section
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "String")
		FString WriteCaptionHere;

	void SetCaptionText();

protected:
	// Sound Section
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		class USoundBase* CaptionSound;

	/** Play sound if true when caption appears */
	UPROPERTY(EditAnywhere, Category = "Sound")
		bool CaptionSoundOn = true;

	void PlayCaptionSound();
};
