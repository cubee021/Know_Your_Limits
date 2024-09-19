// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySpring.generated.h"

/**
* 캐릭터가 밟고 뛰어오르는 스프링
*/
UCLASS()
class PROJECT_API AMySpring : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMySpring();

protected:
	virtual void PostInitializeComponents() override;

public:
	// Interact Section
	UPROPERTY(VisibleAnywhere)
		class UCapsuleComponent* Trigger;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh)
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh)
		UMaterial* Material;

protected:
	UFUNCTION()
		void OnCharacterHit(UPrimitiveComponent* HitComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComponent,
			FVector NormalImpulse, const FHitResult& Hit);

	/** 캐릭터 띄우는 속도 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Velocity)
		float BounceVelocity = 1500.f;

protected:
	// Sound Section
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Sound)
		class USoundBase* BounceSound;

	void PlayBounceSound();
};
