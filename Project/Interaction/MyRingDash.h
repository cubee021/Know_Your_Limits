// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyRingDash.generated.h"

/**
* 플레이어 캐릭터를 spline을 따라 움직이게 하는 Actor
* 중간에 용도 변경으로 RingDash -> MoveAlongSpline 변경 필요.. 
* 
* 맵에 이미 너무 많이 배치해서 삭제 못하는 중 
*/
UCLASS()
class PROJECT_API AMyRingDash : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyRingDash();

protected:
	virtual void PostInitializeComponents() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Spline Section
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SplineController")
		USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SplineController")
		class USplineComponent* Spline;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SplineController")
		class UBoxComponent* Trigger;

	/** Character to move */
	UPROPERTY(VisibleAnywhere)
		class AMyCharacter* MyCharacter;

	/** Spline을 따라 캐릭터 이동이 시작되는 시점 */
	float StartTime;
	/** 캐릭터 이동이 경과된 시간 */
	float CurrentSplineTime;

protected:
	// Interact Section
	UFUNCTION()
		void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& Sweepresult);

	/** Check if Player Charcter is in the Trigger box */
	virtual void NotifyActorBeginOverlap(AActor* OtherActor);
	/** Check if Player Charcter is out of Trigger box */
	virtual void NotifyActorEndOverlap(AActor* OtherActor);

	/** True if player character is currently in the Trigger Box */
	bool OnOverlap = false;

protected:
	void MoveAlongSpline(float DeltaTime);

	/** True if Player's MoveAlongSpline key is pressed */
	bool IsKeyPressed = false;

};
