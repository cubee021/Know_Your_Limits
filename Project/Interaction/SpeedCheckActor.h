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

	/** Current Speed�� ������ ĳ���� */
	UPROPERTY(VisibleAnywhere)
		class AMyCharacter* Character;

	bool OnOverlap = false;

protected:
	// Rotate Section

	/** ȸ����ų Floor �迭 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PublicOptions")
		TArray<AActor*> TargetFloors;

	/** ���� �ӵ�
	* ĳ������ Current Speed�� SpeedLimit �̻��� �Ǹ� TargetFloors ȸ�� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PublicOptions")
		float SpeedLimit = 1000.f;

	/** True if Character's current speed is over SpeedLimit */
	bool IsOverSpeed = false;

	/** Floor�� ȸ�� �ӵ� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PublicOptions")
		float RotationSpeed = 100.f;

	/** �� Floor�� ȸ�� ������ �� */
	TArray<float> DegreeSum;
	/** ��� Floor�� �� ������ ���� ����ġ �Ǿ����� Ȯ�� 
	* ��� True�� �� ȸ�� ���� */
	TArray<bool> IsAligned;
	/** ��� Floor�� ���� rotation ���
	* ȸ�� �������� Slerp�� Floor�� ����ġ�� ���� �� �ֵ��� ���� ���̵���� */
	TArray<FRotator> FloorOrigin;
};
