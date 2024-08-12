// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoalActor.generated.h"

UCLASS()
class PROJECT_API AGoalActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoalActor();

	virtual void PostInitializeComponents() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
		void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& Sweepresult);

private:
	int32 GetTimeScore();

	int32 GetEnemyScore();

	int32 GetRingScore();

	int32 GetTotalScore();

private:
	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere)
		class AMyCharacter* MyCharacter;

	UPROPERTY(VisibleAnywhere)
		class UGoalScoreUserWidget* MyHUD;

	UPROPERTY(VisibleAnywhere)
		class USoundBase* OutroSound;

	UPROPERTY(VisibleAnywhere)
		FTimerHandle TimerHandle;

	UPROPERTY(VisibleAnywhere)
		int32 TotalCnt = 0;

	UPROPERTY(VisibleAnywhere)
		int32 Timer = 300;

	UPROPERTY(VisibleAnywhere)
		bool IsOverlapped = false;

	UPROPERTY(VisibleAnywhere)
		bool IsOneComplete = false;

	UPROPERTY(VisibleAnywhere)
		bool IsTenComplete = false;

	UPROPERTY(VisibleAnywhere)
		bool IsHundredComplete = false;

	UPROPERTY(VisibleAnywhere)
		bool IsThousandComplete = false;

private:
	UPROPERTY(VisibleAnywhere)
		int32 Mili = 0;

	UPROPERTY(VisibleAnywhere)
		int32 Thou = 0;

	UPROPERTY(VisibleAnywhere)
		int32 Hund = 0;

	UPROPERTY(VisibleAnywhere)
		int32 Ten = 0;

	UPROPERTY(VisibleAnywhere)
		int32 One = 0;

	FString CurrentMap;

};
