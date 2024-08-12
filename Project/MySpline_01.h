// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySpline_01.generated.h"

UCLASS()
class PROJECT_API AMySpline_01 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMySpline_01();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SplineController")
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SplineController")
		class USplineComponent* Spline;

	UPROPERTY(VisibleAnywhere)
		TSubclassOf<class AActor> ActorToMoveClass;

	UPROPERTY(VisibleAnywhere)
		class AActor* ActorToMove;

	UPROPERTY(EditAnywhere, Category = "SplineController")
		float TotalPathTime = 10.f;

	UPROPERTY(EditAnywhere, Category = "SplineController")
		bool bSplineInLoop;

	bool bCanMoveActor;

	float StartTime;

	UPROPERTY(EditAnywhere, Category = "FloatingFloor")
		FQuat FloorDegree;

	UPROPERTY(EditAnywhere, Category = "FloatingFloor")
		FVector FloorSize;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
