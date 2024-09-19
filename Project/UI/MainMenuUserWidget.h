// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UMainMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION()
		virtual void NativeConstruct();

public:
	UPROPERTY(meta = (BindWidget))
		class UButton* btn_Start;

	UPROPERTY(meta = (BindWidget))
		class UButton* btn_Settings;

	UPROPERTY(meta = (BindWidget))
		class UButton* btn_Exit;

	/** Open level 1 */
	UFUNCTION()
		void StartGame();
	/** Open Settings */
	UFUNCTION()
		void ToSettings();
	/** Quit game */
	UFUNCTION()
		void ExitGame();

};
