// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyRingDash.generated.h"

/**
* �÷��̾� ĳ���͸� spline�� ���� �����̰� �ϴ� Actor
* �߰��� �뵵 �������� RingDash -> MoveAlongSpline ���� �ʿ�.. 
* 
* �ʿ� �̹� �ʹ� ���� ��ġ�ؼ� ���� ���ϴ� �� 
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

	/** Spline�� ���� ĳ���� �̵��� ���۵Ǵ� ���� */
	float StartTime;
	/** ĳ���� �̵��� ����� �ð� */
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
