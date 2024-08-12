// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameModeBase.h"
#include "MainMenuUserWidget.h"
#include "MainBackgroundWidget.h"
#include "SettingsWidget.h"
#include "MainMenuPawn.h"

AMainMenuGameModeBase::AMainMenuGameModeBase()
{
	DefaultPawnClass = AMainMenuPawn::StaticClass();

	static ConstructorHelpers::FClassFinder<UMainBackgroundWidget> UI_HUD1(TEXT("WidgetBlueprint'/Game/UI/BP_MainMenuBackGround.BP_MainMenuBackGround_C'"));
	if (UI_HUD1.Succeeded())
	{
		HUD_Class1 = UI_HUD1.Class;

		BackgroundWidget = CreateWidget(GetWorld(), HUD_Class1);
		if (BackgroundWidget)
		{
			BackgroundWidget->AddToViewport();
			
		}
	}

	static ConstructorHelpers::FClassFinder<UMainMenuUserWidget> UI_HUD2(TEXT("WidgetBlueprint'/Game/UI/BP_MainMenu.BP_MainMenu_C'"));
	if (UI_HUD2.Succeeded())
	{
		HUD_Class2 = UI_HUD2.Class;

		MainMenuWidget = CreateWidget(GetWorld(), HUD_Class2);
		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();

		}
	}

	static ConstructorHelpers::FClassFinder<USettingsWidget> UI_HUD3(TEXT("WidgetBlueprint'/Game/UI/BP_Settings.BP_Settings_C'"));
	if (UI_HUD3.Succeeded())
	{
		HUD_Class3 = UI_HUD3.Class;

		MainOptionsWidget = CreateWidget(GetWorld(), HUD_Class3);
		if (MainOptionsWidget)
		{
			MainOptionsWidget->AddToViewport();
			MainOptionsWidget->SetVisibility(ESlateVisibility::Collapsed);

		}
	}

}

