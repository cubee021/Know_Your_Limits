// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectGameModeBase.generated.h"

/**
 * 인게임(레벨 플레이 중) 위젯 관리
 */
UCLASS()
class PROJECT_API AProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AProjectGameModeBase();


public:
	/** GameOverUserWidget - 게임 오버 시 알림 위젯 */
	UPROPERTY()
		TSubclassOf<UUserWidget> GameOverUserWidgetClass;

	UPROPERTY()
		UUserWidget* GameOverUserWidget;

	/** GoalScoreUserWidget - 골 스코어 표시 위젯 */
	UPROPERTY()
		TSubclassOf<UUserWidget> GoalScoreUserWidgetClass;

	UPROPERTY()
		UUserWidget* GoalScoreUserWidget;

	/** CaptionWidget - 튜토리얼 캡션 위젯 */
	UPROPERTY()
		TSubclassOf<UUserWidget> CaptionWidgetClass;

	UPROPERTY()
		UUserWidget* CaptionWidget;

	/** PauseMenuUserWidget - 레벨 플레이 중 pause menu 위젯 */
	UPROPERTY()
		TSubclassOf<UUserWidget> PauseMenuUserWidgetClass;

	UPROPERTY()
		UUserWidget* PauseMenuUserWidget;

};
