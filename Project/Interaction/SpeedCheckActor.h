// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpeedCheckActor.generated.h"

UCLASS()
class PROJECT_API ASpeedCheckActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpeedCheckActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor);
	virtual void NotifyActorEndOverlap(AActor* OtherActor);

protected:
	// Interact Section
	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* Trigger;

	/** Current Speed를 추적할 캐릭터 */
	UPROPERTY(VisibleAnywhere)
		class AMyCharacter* Character;

	bool OnOverlap = false;

protected:
	// Rotate Section

	/** 회전시킬 Floor 배열 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PublicOptions")
		TArray<AActor*> TargetFloors;

	/** 제한 속도
	* 캐릭터의 Current Speed가 SpeedLimit 이상이 되면 TargetFloors 회전 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PublicOptions")
		float SpeedLimit = 1000.f;

	/** True if Character's current speed is over SpeedLimit */
	bool IsOverSpeed = false;

	/** Floor의 회전 속도 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PublicOptions")
		float RotationSpeed = 100.f;

	/** 각 Floor의 회전 각도의 합 */
	TArray<float> DegreeSum;
	/** 모든 Floor가 한 바퀴를 돌고 원위치 되었는지 확인 
	* 모두 True일 때 회전 종료 */
	TArray<bool> IsAligned;
	/** 모든 Floor의 원래 rotation 기록
	* 회전 마지막에 Slerp가 Floor를 원위치로 돌릴 수 있도록 돕는 가이드라인 */
	TArray<FRotator> FloorOrigin;
};
