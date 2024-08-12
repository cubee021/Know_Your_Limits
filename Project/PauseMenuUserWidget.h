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
	UPROPERTY()
		TSubclassOf<UUserWidget> HUD_Class; // ���� Ŭ���� ����

	UPROPERTY()
		UUserWidget* PauseSettings; // ������ ���� �ּ� ����

public:
	UPROPERTY(meta = (BindWidget))
		class UButton* btn_Resume;

	UPROPERTY(meta = (BindWidget))
		class UButton* btn_Restart;

	UPROPERTY(meta = (BindWidget))
		class UButton* btn_Settings;

	UPROPERTY(meta = (BindWidget))
		class UButton* btn_toMain;

	UFUNCTION()
		void Resume();

	UFUNCTION()
		void Restart();

	UFUNCTION()
		void ToOptions();

	UFUNCTION()
		void ToMainMenu();


private:
	FTimerHandle TimerHandle;

	
};
