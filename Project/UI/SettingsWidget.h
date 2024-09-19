// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API USettingsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
		virtual void NativeConstruct();

private:
	UPROPERTY()
		class USoundClass* MasterSoundClass;

	UPROPERTY()
		class USoundClass* AmbientSoundClass;

	UPROPERTY()
		class USoundClass* EffectsSoundClass;

	UPROPERTY()
		class USoundClass* WindSoundClass;


	UPROPERTY(VisibleAnywhere)
		class USoundBase* MasterTestSound;

	UPROPERTY(VisibleAnywhere)
		class USoundBase* AmbientTestSound;

	UPROPERTY(VisibleAnywhere)
		class USoundBase* EffectsTestSound;


public:
	UPROPERTY(meta = (BindWidget))
		class UButton* btn_SavenReturn;

	UPROPERTY(meta = (BindWidget))
		class UButton* btn_SoundToDefault;

	UPROPERTY(meta = (BindWidget))
		class USlider* sldr_Master;

	UPROPERTY(meta = (BindWidget))
		class USlider* sldr_Ambient;

	UPROPERTY(meta = (BindWidget))
		class USlider* sldr_Effects;

	UPROPERTY(meta = (BindWidget))
		class USlider* sldr_Wind;


	UPROPERTY(meta = (BindWidget))
		class UCheckBox* CheckBox_Low;

	UPROPERTY(meta = (BindWidget))
		class UCheckBox* CheckBox_Medium;

	UPROPERTY(meta = (BindWidget))
		class UCheckBox* CheckBox_High;

	UPROPERTY(meta = (BindWidget))
		class UCheckBox* CheckBox_Epic;

// Sound Section
	/** Save and back to Main Menu */
	UFUNCTION()
		void Back();
	/** Set sound settings to default */
	UFUNCTION()
		void SoundToDefault();
	/** Set Master volume */
	UFUNCTION()
		void UpdateMasterVolume(float Value);
	/** Set Ambient volume */
	UFUNCTION()
		void UpdateAmbientVolume(float Value);
	/** Set Effects volume */
	UFUNCTION()
		void UpdateEffectsVolume(float Value);
	/** Set Boost wind sound volume */
	UFUNCTION()
		void UpdateWindVolume(float Value);

// Graphics Section
	UFUNCTION()
		void GraphicToLow(bool IsChecked);

	UFUNCTION()
		void GraphicToMedium(bool IsChecked);

	UFUNCTION()
		void GraphicToHigh(bool IsChecked);

	UFUNCTION()
		void GraphicToEpic(bool IsChecked);
};
