// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmbientController.generated.h"

UCLASS()
class PROJECT_API AAmbientController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmbientController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void StopAmbient();

	bool IsAmbientPlaying();

private:
	UPROPERTY(VisibleAnywhere)
		class UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere)
		class USoundBase* Ambient;



};
