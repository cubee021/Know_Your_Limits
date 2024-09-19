// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ViewTarget.generated.h"

/**
* 캐릭터가 트리거 overlap 시 카메라가 이동 설정 위치로 이동
* 게임에서는 쓰이지 않음
*/
UCLASS()
class PROJECT_API AViewTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AViewTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, 
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp, 
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/*
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, 
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp, 
			int32 OtherBodyIndex);
	*/
	

private:
	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* OverlapBox;

	UPROPERTY(EditAnywhere, Category = "ViewTarget")
		AActor* CameraLocation;

	UPROPERTY(VisibleAnywhere)
		APlayerController* PlayerController;

	UPROPERTY(EditAnywhere, Category = "ViewTarget")
		float BlendTime = 1.f;
};
