// Copyright 2023. cubee021. All rights reserved.


#include "TitleScreenGameModeBase.h"
#include "UI/TitleScreenWidget.h"

ATitleScreenGameModeBase::ATitleScreenGameModeBase()
{
	//DefaultPawnClass = AMainMenuPawn::StaticClass();

	static ConstructorHelpers::FClassFinder<UTitleScreenWidget> UI_HUD(TEXT("WidgetBlueprint'/Game/UI/BP_TitleScreen.BP_TitleScreen_C'"));
	if (UI_HUD.Succeeded())
	{
		TitleScreenWidgetClass = UI_HUD.Class;

		TitleScreenWidget = CreateWidget(GetWorld(), TitleScreenWidgetClass);
		if (TitleScreenWidget)
		{
			TitleScreenWidget->AddToViewport();

		}
	}
}