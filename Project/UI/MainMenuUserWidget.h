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

public:
	UPROPERTY(meta = (BindWidget))
		class UButton* btn_Start;

	UPROPERTY(meta = (BindWidget))
		class UButton* btn_Settings;

	UPROPERTY(meta = (BindWidget))
		class UButton* btn_Exit;

	UFUNCTION()
		virtual void NativeConstruct();

	UFUNCTION()
		void StartGame();

	UFUNCTION()
		void ToSettings();

	UFUNCTION()
		void ExitGame();

};
