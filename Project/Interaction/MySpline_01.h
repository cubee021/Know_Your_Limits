// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySpline_01.generated.h"

/**
* 지정한 Actor를 spline에 따라 움직이게 하는 Actor 
* MySpline_01 -> MoveActorSpline으로 이름 정정 필요
*/
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

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// Spline Section
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SplineController")
		USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SplineController")
		class USplineComponent* Spline;

	/** True if this spline loops */
	UPROPERTY(EditAnywhere, Category = "SplineController")
		bool bSplineInLoop;

	/** Spline을 따라 캐릭터 이동이 시작되는 시점 */
	float StartTime;

protected:
	// Actor To Move Section

	/* Splin을 따라 움직일 Actor Class
	* 생성자로 캐릭터가 올라설 수 있는 발판 설정 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ActorToMove)
		TSubclassOf<class AActor> ActorToMoveClass;

	/** Spline을 따라 움직일 Actor */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ActorToMove)
		class AActor* ActorToMove;

	/** Rotation of an Actor */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ActorToMove)
		FQuat ActorRotation;
	/** Size of an Actor */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ActorToMove)
		FVector ActorSize;

	/** True if ActorToMove is spawned and ready to move */
	bool bCanMoveActor;

};
