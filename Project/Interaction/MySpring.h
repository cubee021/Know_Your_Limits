// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySpring.generated.h"

UCLASS()
class PROJECT_API AMySpring : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMySpring();

	virtual void PostInitializeComponents() override;

private:
	UFUNCTION()
		void OnCharacterHit(UPrimitiveComponent* HitComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComponent,
			FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(VisibleAnywhere)
		class USoundBase* BounceSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Spring;

	UPROPERTY(VisibleAnywhere)
		UMaterial* Mat;

	UPROPERTY(VisibleAnywhere)
		class UCapsuleComponent* Trigger;

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere)
		class UWidgetComponent* Crosshair;


};
