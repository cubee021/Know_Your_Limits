// Copyright 2023. cubee021. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RobbedCoinBag.generated.h"

UCLASS()
class PROJECT_API ARobbedCoinBag : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARobbedCoinBag();

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
