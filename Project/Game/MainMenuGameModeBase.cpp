// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameModeBase.h"
#include "UI/MainMenuUserWidget.h"
#include "UI/MainBackgroundWidget.h"
#include "UI/SettingsWidget.h"
#include "Interaction/MainMenuPawn.h"

AMainMenuGameModeBase::AMainMenuGameModeBase()
{
	DefaultPawnClass = AMainMenuPawn::StaticClass();

	static ConstructorHelpers::FClassFinder<UMainBackgroundWidget> UI_HUD1(TEXT("WidgetBlueprint'/Game/UI/BP_MainMenuBackGround.BP_MainMenuBackGround_C'"));
	if (UI_HUD1.Succeeded())
	{
		MainBackgroundWidgetClass = UI_HUD1.Class;

		MainBackgroundWidget = CreateWidget(GetWorld(), MainBackgroundWidgetClass);
		if (MainBackgroundWidget)
		{
			MainBackgroundWidget->AddToViewport();
			
		}
	}

	static ConstructorHelpers::FClassFinder<UMainMenuUserWidget> UI_HUD2(TEXT("WidgetBlueprint'/Game/UI/BP_MainMenu.BP_MainMenu_C'"));
	if (UI_HUD2.Succeeded())
	{
		MainMenuUserWidgetClass = UI_HUD2.Class;

		MainMenuUserWidget = CreateWidget(GetWorld(), MainMenuUserWidgetClass);
		if (MainMenuUserWidget)
		{
			MainMenuUserWidget->AddToViewport();

		}
	}

	static ConstructorHelpers::FClassFinder<USettingsWidget> UI_HUD3(TEXT("WidgetBlueprint'/Game/UI/BP_Settings.BP_Settings_C'"));
	if (UI_HUD3.Succeeded())
	{
		SettingsWidgetClass = UI_HUD3.Class;

		SettingsWidget = CreateWidget(GetWorld(), SettingsWidgetClass);
		if (SettingsWidget)
		{
			SettingsWidget->AddToViewport();
			SettingsWidget->SetVisibility(ESlateVisibility::Collapsed);

		}
	}

}

