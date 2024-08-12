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


private:
	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere)
		class AMyCharacter* Character;

	UPROPERTY(EditAnywhere, Category = "PublicOptions")
		TArray<AActor*> TargetFloors;

	UPROPERTY(EditAnywhere, Category = "PublicOptions")
		float SpeedLimit = 1000.f;

	bool OnOverlap = false;

	bool IsOverSpeed = false;

	UPROPERTY(EditAnywhere, Category = "PublicOptions")
		float RotationSpeed = 100.f;

	bool IsRotationStart = true;
	bool IsHalfDone = false;

	TArray<float> DegreeSum;
	TArray<bool> IsAligned;
	TArray<FRotator> FloorOrigin;
};
