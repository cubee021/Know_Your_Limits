// Copyright Epic Games, Inc. All Rights Reserved.


#include "ProjectGameModeBase.h"
#include "MyCharacter.h" 
#include "MyUserWidget.h"
#include "MyPlayerController.h"
#include "GameOverUserWidget.h"
#include "GoalScoreUserWidget.h"
#include "CaptionWidget.h"
#include "PauseMenuUserWidget.h"

AProjectGameModeBase::AProjectGameModeBase()
{
	DefaultPawnClass = AMyCharacter::StaticClass(); // 디폴트 폰으로 MyCharacter 클래스 고정
	PlayerControllerClass = AMyPlayerController::StaticClass();

	// 블루프린트 캐릭터 연결
	static ConstructorHelpers::FClassFinder<ACharacter> AC(TEXT("Blueprint'/Game/Blueprints/BP_MyCharacter.BP_MyCharacter_C'"));
	
	if (AC.Succeeded()) // 성공 시 C++ 캐릭터에서 블루프린트로 바꾸기
	{
		DefaultPawnClass = AC.Class;
	}

	
	//ring count UI 로드
	static ConstructorHelpers::FClassFinder<UMyUserWidget> UI_HUD(TEXT("WidgetBlueprint'/Game/UI/BP_HUD.BP_HUD_C'"));
	if (UI_HUD.Succeeded())
	{
		HUD_Class = UI_HUD.Class;

		CurrentWidget = CreateWidget(GetWorld(), HUD_Class);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}

	//game over UI
	static ConstructorHelpers::FClassFinder<UGameOverUserWidget> UW(TEXT("WidgetBlueprint'/Game/UI/BP_GameOver.BP_GameOver_C'"));
	if (UW.Succeeded())
	{
		HUD_Class2 = UW.Class;
		
		CurrentWidget2 = CreateWidget(GetWorld(), HUD_Class2);
		if (CurrentWidget2)
		{
			CurrentWidget2->AddToViewport();
			CurrentWidget2->SetVisibility(ESlateVisibility::Collapsed);
		}
		
	}
	
	//goal score UI
	static ConstructorHelpers::FClassFinder<UGoalScoreUserWidget> UW2(TEXT("WidgetBlueprint'/Game/UI/BP_GoalScore.BP_GoalScore_C'"));
	if (UW2.Succeeded())
	{
		HUD_Class3 = UW2.Class;

		CurrentWidget3 = CreateWidget(GetWorld(), HUD_Class3);
		if (CurrentWidget3)
		{
			CurrentWidget3->AddToViewport();
			CurrentWidget3->SetVisibility(ESlateVisibility::Collapsed);
		}

	}

	//Caption UI
	static ConstructorHelpers::FClassFinder<UCaptionWidget> UW3(TEXT("WidgetBlueprint'/Game/UI/BP_Caption.BP_Caption_C'"));
	if (UW3.Succeeded())
	{
		HUD_Class4 = UW3.Class;

		CurrentWidget4 = CreateWidget(GetWorld(), HUD_Class4);
		if (CurrentWidget4)
		{
			CurrentWidget4->AddToViewport();
			CurrentWidget4->SetVisibility(ESlateVisibility::Collapsed);
		}

	}

	//Pause menu UI
	static ConstructorHelpers::FClassFinder<UPauseMenuUserWidget> UW4(TEXT("WidgetBlueprint'/Game/UI/BP_PauseMenu.BP_PauseMenu_C'"));
	if (UW4.Succeeded())
	{
		HUD_Class5 = UW4.Class;

		CurrentWidget5 = CreateWidget(GetWorld(), HUD_Class5);
		if (CurrentWidget5)
		{
			CurrentWidget5->AddToViewport();
			CurrentWidget5->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}


