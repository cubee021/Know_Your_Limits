// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoalActor.generated.h"

#define MAX_TOTAL_SCORE 99999
/**
* View scores in GoalScoreUserWidget when player interacts with trigger
*/
UCLASS()
class PROJECT_API AGoalActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoalActor();

protected:
	virtual void PostInitializeComponents() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Interact Section
	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget)
		class UGoalScoreUserWidget* MyHUD;

	UFUNCTION()
		void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& Sweepresult);

protected:
	// Score Section
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Score)
		class AMyCharacter* MyCharacter;

	/** Get scores of MyCharacter */
	int32 GetTimeScore();
	int32 GetEnemyScore();
	int32 GetRingScore();
	int32 GetTotalScore();

protected:
	// Sound Section
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
		class USoundBase* OutroSound;

	void PlayOutroSound();
	void StopAllAmbientsInCurrentLevel();

protected:
	/** View Total Score Section
	* 
	* Total Score �� �ڸ��� �������� �����ٰ� ���ڸ����� �����ϴ� ���
	* ���� �ڵ��ε� �ϴ��� �ǵ��� ���� */

	/** ��� �ڸ����� �����ִ� �� �ɸ��� �ð�. DeltaTime ���� ��� */
	int32 Timer = 300;

	/** Start to show total scores if True */
	bool StartViewTotalScore = false;
	/** 1�� �ڸ� ���� �Ϸ� if True */
	bool IsOneComplete = false;
	/** 10�� �ڸ� ���� �Ϸ� if True */
	bool IsTenComplete = false;
	/** 100�� �ڸ� ���� �Ϸ� if True */
	bool IsHundredComplete = false;
	/** 1000�� �ڸ� ���� �Ϸ� if True */
	bool IsThousandComplete = false;

	/** �� �ڸ� ���� ���� �� ���� ���� ���� */
	int32 Mili = 0;
	int32 Thou = 0;
	int32 Hund = 0;
	int32 Ten = 0;
	int32 One = 0;

protected:
	// Move To Next Level Section
	FTimerHandle MoveToNextTimerHandle;
	/** Open next level */
	void MoveToNextLevel();

};
