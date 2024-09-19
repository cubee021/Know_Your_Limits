// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySpline_01.generated.h"

/**
* ������ Actor�� spline�� ���� �����̰� �ϴ� Actor 
* MySpline_01 -> MoveActorSpline���� �̸� ���� �ʿ�
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

	/** Spline�� ���� ĳ���� �̵��� ���۵Ǵ� ���� */
	float StartTime;

protected:
	// Actor To Move Section

	/* Splin�� ���� ������ Actor Class
	* �����ڷ� ĳ���Ͱ� �ö� �� �ִ� ���� ���� */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ActorToMove)
		TSubclassOf<class AActor> ActorToMoveClass;

	/** Spline�� ���� ������ Actor */
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
