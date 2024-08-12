// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuUserWidget.h"
#include "MainMenuGameModeBase.h"
#include "SettingsWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Button.h"

void UMainMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	btn_Start->OnClicked.AddDynamic(this, &UMainMenuUserWidget::StartGame);
	btn_Settings->OnClicked.AddDynamic(this, &UMainMenuUserWidget::ToSettings);
	btn_Exit->OnClicked.AddDynamic(this, &UMainMenuUserWidget::ExitGame);
}

void UMainMenuUserWidget::StartGame()
{
	UGameplayStatics::OpenLevel(this, FName("Map_NorthenIsle_01"));

}

void UMainMenuUserWidget::ToSettings()
{
	AMainMenuGameModeBase* GameMode = Cast<AMainMenuGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode) // 이미 있는 UI 불러오는 방법
	{
		USettingsWidget* Options = Cast<USettingsWidget>(GameMode->MainOptionsWidget);
		if (Options)
		{
			Options->SetVisibility(ESlateVisibility::Visible);
		}

		SetVisibility(ESlateVisibility::Collapsed);
	}

}

void UMainMenuUserWidget::ExitGame()
{
	UKismetSystemLibrary::QuitGame(this, 0, EQuitPreference::Quit, false);
}
