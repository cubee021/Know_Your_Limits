// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyEnemy.generated.h"

UCLASS()
class PROJECT_API AMyEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;


/* enemy funtions */
private:
	UFUNCTION()
		void OnCharacterHit(UPrimitiveComponent* HitComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComponent,
			FVector NormalImpulse, const FHitResult& Hit);

public:
	void DetectPlayer(float DeltaTime);

	void CrosshairOn();
	void CrosshairOff();


/* properties, sources, variables */
protected:
	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* Enemy;

private:

	UPROPERTY(VisibleAnywhere)
		class USphereComponent* Trigger;

	UPROPERTY(VisibleAnywhere)
		class UArrowComponent* Arrow;

	UPROPERTY(VisibleAnywhere)
		class UWidgetComponent* Crosshair;

	UPROPERTY(VisibleAnywhere)
		class USoundBase* DestroySound;

	UPROPERTY(VisibleAnywhere)
		class USoundBase* RingDropSound;

	UPROPERTY(VisibleAnywhere)
		class USoundBase* CrosshairSound;

	UPROPERTY(VisibleAnywhere)
		int32 CrosshairCount = 0;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class UParticleSystem* Explosion;

	UPROPERTY(VisibleAnywhere)
		bool OnCombat;
	

};
