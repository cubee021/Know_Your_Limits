// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyRingDash.generated.h"

UCLASS()
class PROJECT_API AMyRingDash : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyRingDash();

	virtual void PostInitializeComponents() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SplineController")
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SplineController")
		class USplineComponent* Spline;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SplineController")
		class UBoxComponent* Trigger;

protected:

	UPROPERTY(EditAnywhere, Category = "SplineController")
		float TotalPathTime = 10.f;


	float StartTime;

	float CurrentSplineTime;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
		class AMyCharacter* MyCharacter;

private:
	UFUNCTION()
		void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& Sweepresult);

	virtual void NotifyActorBeginOverlap(AActor* OtherActor);
	virtual void NotifyActorEndOverlap(AActor* OtherActor);

	UPROPERTY(VisibleAnywhere)
		bool bRingDash = false;

	void MoveAlongSpline(float DeltaTime);

	bool OnOverlap = false;

};
