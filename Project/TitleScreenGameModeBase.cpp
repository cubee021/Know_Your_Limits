// Copyright 2023. cubee021. All rights reserved.


#include "TitleScreenGameModeBase.h"
#include "TitleScreenWidget.h"

ATitleScreenGameModeBase::ATitleScreenGameModeBase()
{
	//DefaultPawnClass = AMainMenuPawn::StaticClass();

	static ConstructorHelpers::FClassFinder<UTitleScreenWidget> UI_HUD(TEXT("WidgetBlueprint'/Game/UI/BP_TitleScreen.BP_TitleScreen_C'"));
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