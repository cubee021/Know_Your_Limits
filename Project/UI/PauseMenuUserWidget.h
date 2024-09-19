// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UPauseMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
		virtual void NativeConstruct();

public:
	/** PauseSettings À§Á¬ »ý¼º */
	UPROPERTY()
		TSubclassOf<UUserWidget> PauseSettingsClass;

	UPROPERTY()
		UUserWidget* PauseSettings;

public:
	UPROPERTY(meta = (BindWidget))
		class UButton* btn_Resume;

	UPROPERTY(meta = (BindWidget))
		class UButton* btn_Restart;

	UPROPERTY(meta = (BindWidget))
		class UButton* btn_Settings;

	UPROPERTY(meta = (BindWidget))
		class UButton* btn_toMain;

	/** Back to game */
	UFUNCTION()
		void Resume();
	/** Restart current State */
	UFUNCTION()
		void Restart();
	/** Open Options */
	UFUNCTION()
		void ToOptions();
	/** Back to Main Menu */
	UFUNCTION()
		void ToMainMenu();

protected:
	FTimerHandle OpenLevelTimerHandle;

	
};
