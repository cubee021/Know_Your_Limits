// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CaptionTrigger.generated.h"

UCLASS()
class PROJECT_API ACaptionTrigger : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACaptionTrigger();

	virtual void PostInitializeComponents() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& Sweepresult);


public:
	UPROPERTY(EditAnywhere, Category = "Caption")
		FString WriteCaptionHere;

	UPROPERTY(EditAnywhere, Category = "Caption")
		bool CaptionSoundOn = true;

private:
	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere)
		class AProjectGameModeBase* GameMode;

	UPROPERTY(VisibleAnywhere)
		class UCaptionWidget* MyHUD;

	UPROPERTY(VisibleAnywhere)
		class USoundBase* CaptionSound;

	int32 Timer = 230;

	bool StartTimer = false;

	bool IsShowedOnce = false;

	bool IsSoundPlayedOnce = false;


};
