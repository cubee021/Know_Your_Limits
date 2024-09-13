// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameModeBase.generated.h"

/**
 * 메인메뉴 위젯 관리
 */
UCLASS()
class PROJECT_API AMainMenuGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

		AMainMenuGameModeBase();

public:
	/** MainBackgroundWidget - 메인메뉴 백그라운드 이미지 */
	UPROPERTY()
		TSubclassOf<UUserWidget> MainBackgroundWidgetClass;

	UPROPERTY()
		UUserWidget* MainBackgroundWidget;

	/** MainMenuUserWidget - 메인화면 버튼 위젯 */
	UPROPERTY()
		TSubclassOf<UUserWidget> MainMenuUserWidgetClass;

	UPROPERTY()
		UUserWidget* MainMenuUserWidget;

	/** SettingsWidget - 메인메뉴 세팅 위젯 */
	UPROPERTY()
		TSubclassOf<UUserWidget> SettingsWidgetClass;

	UPROPERTY()
		UUserWidget* SettingsWidget;

};
