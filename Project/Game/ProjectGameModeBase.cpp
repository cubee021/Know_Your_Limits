// Copyright Epic Games, Inc. All Rights Reserved.


#include "ProjectGameModeBase.h"
#include "Character/MyCharacter.h" 
#include "PlayerController/MyPlayerController.h"
#include "MyGameStateBase.h"
#include "UI/GameOverUserWidget.h"
#include "UI/GoalScoreUserWidget.h"
#include "UI/CaptionWidget.h"
#include "UI/PauseMenuUserWidget.h"

AProjectGameModeBase::AProjectGameModeBase()
{
	//DefaultPawnClass = AMyCharacter::StaticClass();

	static ConstructorHelpers::FClassFinder<ACharacter> AC(TEXT("Blueprint'/Game/Blueprints/BP_MyCharacter.BP_MyCharacter_C'"));
	if (AC.Succeeded())
	{
		DefaultPawnClass = AC.Class;
	}

	PlayerControllerClass = AMyPlayerController::StaticClass();
	GameStateClass = AMyGameStateBase::StaticClass();

	// Widget Section
	static ConstructorHelpers::FClassFinder<UGameOverUserWidget> UW(TEXT("WidgetBlueprint'/Game/UI/BP_GameOver.BP_GameOver_C'"));
	if (UW.Succeeded())
	{
		GameOverUserWidgetClass = UW.Class;
		
		GameOverUserWidget = CreateWidget(GetWorld(), GameOverUserWidgetClass);
		if (GameOverUserWidget)
		{
			GameOverUserWidget->AddToViewport();
			GameOverUserWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	
	static ConstructorHelpers::FClassFinder<UGoalScoreUserWidget> UW2(TEXT("WidgetBlueprint'/Game/UI/BP_GoalScore.BP_GoalScore_C'"));
	if (UW2.Succeeded())
	{
		GoalScoreUserWidgetClass = UW2.Class;

		GoalScoreUserWidget = CreateWidget(GetWorld(), GoalScoreUserWidgetClass);
		if (GoalScoreUserWidget)
		{
			GoalScoreUserWidget->AddToViewport();
			GoalScoreUserWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

	//Caption UI
	static ConstructorHelpers::FClassFinder<UCaptionWidget> UW3(TEXT("WidgetBlueprint'/Game/UI/BP_Caption.BP_Caption_C'"));
	if (UW3.Succeeded())
	{
		CaptionWidgetClass = UW3.Class;

		CaptionWidget = CreateWidget(GetWorld(), CaptionWidgetClass);
		if (CaptionWidget)
		{
			CaptionWidget->AddToViewport();
			CaptionWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

	//Pause menu UI
	static ConstructorHelpers::FClassFinder<UPauseMenuUserWidget> UW4(TEXT("WidgetBlueprint'/Game/UI/BP_PauseMenu.BP_PauseMenu_C'"));
	if (UW4.Succeeded())
	{
		PauseMenuUserWidgetClass = UW4.Class;

		PauseMenuUserWidget = CreateWidget(GetWorld(), PauseMenuUserWidgetClass);
		if (PauseMenuUserWidget)
		{
			PauseMenuUserWidget->AddToViewport();
			PauseMenuUserWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}


