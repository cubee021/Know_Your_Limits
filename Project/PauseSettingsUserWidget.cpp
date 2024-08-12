// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseSettingsUserWidget.h"
#include "MySaveGame.h"
#include "PauseMenuUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Sound/SoundClass.h"
#include "Sound/SoundMix.h"
#include "GameFramework/GameUserSettings.h"
#include "Components/CheckBox.h"
#include "ProjectGameModeBase.h"

void UPauseSettingsUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	btn_SavenReturn->OnClicked.AddDynamic(this, &UPauseSettingsUserWidget::Back);
	btn_SoundToDefault->OnClicked.AddDynamic(this, &UPauseSettingsUserWidget::SoundToDefault);
	sldr_Master->OnValueChanged.AddDynamic(this, &UPauseSettingsUserWidget::UpdateMasterVolume);
	sldr_Ambient->OnValueChanged.AddDynamic(this, &UPauseSettingsUserWidget::UpdateAmbientVolume);
	sldr_Effects->OnValueChanged.AddDynamic(this, &UPauseSettingsUserWidget::UpdateEffectsVolume);
	sldr_Wind->OnValueChanged.AddDynamic(this, &UPauseSettingsUserWidget::UpdateWindVolume);
	CheckBox_Low->OnCheckStateChanged.AddDynamic(this, &UPauseSettingsUserWidget::GraphicToLow);
	CheckBox_Medium->OnCheckStateChanged.AddDynamic(this, &UPauseSettingsUserWidget::GraphicToMedium);
	CheckBox_High->OnCheckStateChanged.AddDynamic(this, &UPauseSettingsUserWidget::GraphicToHigh);
	CheckBox_Epic->OnCheckStateChanged.AddDynamic(this, &UPauseSettingsUserWidget::GraphicToEpic);


	static ConstructorHelpers::FObjectFinder<USoundClass> SC(TEXT("SoundClass'/Game/Sounds/SoundClasses/MasterVolume.MasterVolume'"));
	if (SC.Succeeded())
	{
		MasterSoundClass = SC.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundClass> SC1(TEXT("SoundClass'/Game/Sounds/SoundClasses/Ambient.Ambient'"));
	if (SC1.Succeeded())
	{
		AmbientSoundClass = SC1.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundClass> SC2(TEXT("SoundClass'/Game/Sounds/SoundClasses/OtherEffects.OtherEffects'"));
	if (SC2.Succeeded())
	{
		EffectsSoundClass = SC2.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundClass> SC3(TEXT("SoundClass'/Game/Sounds/SoundClasses/WindEffect.WindEffect'"));
	if (SC3.Succeeded())
	{
		WindSoundClass = SC3.Object;
	}


	static ConstructorHelpers::FObjectFinder<USoundBase> SB(TEXT("SoundWave'/Game/Sounds/jingle1.jingle1'"));
	if (SB.Succeeded())
	{
		MasterTestSound = SB.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> SB1(TEXT("SoundWave'/Game/Sounds/piano_sound_test.piano_sound_test'"));
	if (SB1.Succeeded())
	{
		AmbientTestSound = SB1.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> SB2(TEXT("SoundWave'/Game/Sounds/spring_sound.spring_sound'"));
	if (SB2.Succeeded())
	{
		EffectsTestSound = SB2.Object;
	}
	
	if (UMySaveGame* LoadGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("SaveSlot1"), 0)))
	{
		sldr_Master->SetValue(LoadGame->MasterSoundValue);
		sldr_Ambient->SetValue(LoadGame->AmbientSoundValue);
		sldr_Effects->SetValue(LoadGame->EffectsSoundValue);
		sldr_Wind->SetValue(LoadGame->WindSoundValue);

		CheckBox_Low->SetCheckedState(LoadGame->IsLowQualityCheck);
		CheckBox_Medium->SetCheckedState(LoadGame->IsMediumQualityCheck);
		CheckBox_High->SetCheckedState(LoadGame->IsHighQualityCheck);
		CheckBox_Epic->SetCheckedState(LoadGame->IsEpicQualityCheck);
	}
	
	if (CheckBox_Low->GetCheckedState() == ECheckBoxState::Unchecked && CheckBox_Medium->GetCheckedState() == ECheckBoxState::Unchecked
		&& CheckBox_High->GetCheckedState() == ECheckBoxState::Unchecked && CheckBox_Epic->GetCheckedState() == ECheckBoxState::Unchecked)
	{
		CheckBox_Epic->SetCheckedState(ECheckBoxState::Checked);
		GraphicToEpic(true);
		SoundToDefault();
	}
	
}

void UPauseSettingsUserWidget::Back()
{
	
	UMySaveGame* SaveGame = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	if (SaveGame)
	{
		SaveGame->MasterSoundValue = MasterSoundClass->Properties.Volume;
		SaveGame->AmbientSoundValue = AmbientSoundClass->Properties.Volume;
		SaveGame->EffectsSoundValue = EffectsSoundClass->Properties.Volume;
		SaveGame->WindSoundValue = WindSoundClass->Properties.Volume;

		SaveGame->IsLowQualityCheck = CheckBox_Low->GetCheckedState();
		SaveGame->IsMediumQualityCheck = CheckBox_Medium->GetCheckedState();
		SaveGame->IsHighQualityCheck = CheckBox_High->GetCheckedState();
		SaveGame->IsEpicQualityCheck = CheckBox_Epic->GetCheckedState();

		if (!UGameplayStatics::SaveGameToSlot(SaveGame, TEXT("SaveSlot1"), 0)) 
		{
			UE_LOG(LogTemp, Error, TEXT("Checkpoint Error : File Save falied"));
		}
	}
	
	AProjectGameModeBase* GameMode = Cast<AProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode) // 이미 있는 UI 불러오는 방법
	{
		UPauseMenuUserWidget* MyHUD = Cast<UPauseMenuUserWidget>(GameMode->CurrentWidget5);
		if (MyHUD)
		{
			MyHUD->SetVisibility(ESlateVisibility::Visible);
			SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UPauseSettingsUserWidget::SoundToDefault()
{
	MasterSoundClass->Properties.Volume = 1.f;
	AmbientSoundClass->Properties.Volume = 1.f;
	EffectsSoundClass->Properties.Volume = 1.f;
	WindSoundClass->Properties.Volume = 1.f;

	sldr_Master->SetValue(1.f);
	sldr_Ambient->SetValue(1.f);
	sldr_Effects->SetValue(1.f);
	sldr_Wind->SetValue(1.f);

}


void UPauseSettingsUserWidget::UpdateMasterVolume(float Value)
{
	MasterSoundClass->Properties.Volume = Value;
	UGameplayStatics::PlaySound2D(GetWorld(), MasterTestSound);

}

void UPauseSettingsUserWidget::UpdateAmbientVolume(float Value)
{
	AmbientSoundClass->Properties.Volume = Value;
	UGameplayStatics::PlaySound2D(GetWorld(), AmbientTestSound);

}

void UPauseSettingsUserWidget::UpdateEffectsVolume(float Value)
{
	EffectsSoundClass->Properties.Volume = Value;
	UGameplayStatics::PlaySound2D(GetWorld(), EffectsTestSound);

}

void UPauseSettingsUserWidget::UpdateWindVolume(float Value)
{
	WindSoundClass->Properties.Volume = Value;
}

void UPauseSettingsUserWidget::GraphicToLow(bool IsChecked)
{
	if (IsChecked)
	{
		UGameUserSettings* GameuserSettings = UGameUserSettings::GetGameUserSettings();
		GameuserSettings->SetOverallScalabilityLevel(0);
		GameuserSettings->ApplySettings(true);

		CheckBox_Medium->SetCheckedState(ECheckBoxState::Unchecked);
		CheckBox_High->SetCheckedState(ECheckBoxState::Unchecked);
		CheckBox_Epic->SetCheckedState(ECheckBoxState::Unchecked);

	}
}

void UPauseSettingsUserWidget::GraphicToMedium(bool IsChecked)
{
	if (IsChecked)
	{
		UGameUserSettings* GameuserSettings = UGameUserSettings::GetGameUserSettings();
		GameuserSettings->SetOverallScalabilityLevel(1);
		GameuserSettings->ApplySettings(true);

		CheckBox_Low->SetCheckedState(ECheckBoxState::Unchecked);
		CheckBox_High->SetCheckedState(ECheckBoxState::Unchecked);
		CheckBox_Epic->SetCheckedState(ECheckBoxState::Unchecked);

	}
}

void UPauseSettingsUserWidget::GraphicToHigh(bool IsChecked)
{
	if (IsChecked)
	{
		UGameUserSettings* GameuserSettings = UGameUserSettings::GetGameUserSettings();
		GameuserSettings->SetOverallScalabilityLevel(2);
		GameuserSettings->ApplySettings(true);

		CheckBox_Low->SetCheckedState(ECheckBoxState::Unchecked);
		CheckBox_Medium->SetCheckedState(ECheckBoxState::Unchecked);
		CheckBox_Epic->SetCheckedState(ECheckBoxState::Unchecked);

	}
}

void UPauseSettingsUserWidget::GraphicToEpic(bool IsChecked)
{
	if (IsChecked)
	{
		UGameUserSettings* GameuserSettings = UGameUserSettings::GetGameUserSettings();
		GameuserSettings->SetOverallScalabilityLevel(3);
		GameuserSettings->ApplySettings(true);

		CheckBox_Low->SetCheckedState(ECheckBoxState::Unchecked);
		CheckBox_Medium->SetCheckedState(ECheckBoxState::Unchecked);
		CheckBox_High->SetCheckedState(ECheckBoxState::Unchecked);

	}
}


