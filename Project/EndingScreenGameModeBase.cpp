// Fill out your copyright notice in the Description page of Project Settings.


#include "EndingScreenGameModeBase.h"
#include "EndingScreenWidget.h"

AEndingScreenGameModeBase::AEndingScreenGameModeBase()
{
	//DefaultPawnClass = AMainMenuPawn::StaticClass();

	static ConstructorHelpers::FClassFinder<UEndingScreenWidget> UI_HUD(TEXT("WidgetBlueprint'/Game/UI/BP_EndingScreen.BP_EndingScreen_C'"));
	if (UI_HUD.Succeeded())
	{
		HUD_Class = UI_HUD.Class;

		CurrentWidget = CreateWidget(GetWorld(), HUD_Class);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();

		}
	}
}