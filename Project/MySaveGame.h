// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()


public:
	UMySaveGame();

	UPROPERTY()
		FVector PlayerLastLocation;

	UPROPERTY()
		FRotator PlayerLastRotation;


	UPROPERTY()
		float MasterSoundValue;

	UPROPERTY()
		float AmbientSoundValue;

	UPROPERTY()
		float EffectsSoundValue;

	UPROPERTY()
		float WindSoundValue;


	UPROPERTY()
		ECheckBoxState IsLowQualityCheck;

	UPROPERTY()
		ECheckBoxState IsMediumQualityCheck;

	UPROPERTY()
		ECheckBoxState IsHighQualityCheck;

	UPROPERTY()
		ECheckBoxState IsEpicQualityCheck;
	
};
