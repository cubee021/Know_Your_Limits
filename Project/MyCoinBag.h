// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyCoinBag.generated.h"

UCLASS()
class PROJECT_API AMyCoinBag : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyCoinBag();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
		void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& Sweepresult);

	UPROPERTY(VisibleAnywhere)
		class USoundBase* RingSound;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* CoinBag;

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* Trigger;

	bool IsOverlappedAlready = false;

};
