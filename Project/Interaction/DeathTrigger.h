// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DeathTrigger.generated.h"

/**
* Game Over when Character interacts with trigger
*/
UCLASS()
class PROJECT_API ADeathTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADeathTrigger();

protected:
	virtual void PostInitializeComponents() override;

protected:
	// Interact Section
	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* Trigger;

	UFUNCTION()
		void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& Sweepresult);


};
