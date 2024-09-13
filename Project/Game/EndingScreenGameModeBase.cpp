// Fill out your copyright notice in the Description page of Project Settings.


#include "EndingScreenGameModeBase.h"
#include "UI/EndingScreenWidget.h"

AEndingScreenGameModeBase::AEndingScreenGameModeBase()
{
	//DefaultPawnClass = AMainMenuPawn::StaticClass();

	static ConstructorHelpers::FClassFinder<UEndingScreenWidget> UI_HUD(TEXT("WidgetBlueprint'/Game/UI/BP_EndingScreen.BP_EndingScreen_C'"));
	if (UI_HUD.Succeeded())
	{
		EndingScreenWidgetClass = UI_HUD.Class;

		EndingScreenWidget = CreateWidget(GetWorld(), EndingScreenWidgetClass);
		if (EndingScreenWidget)
		{
			EndingScreenWidget->AddToViewport();
		}
	}
}