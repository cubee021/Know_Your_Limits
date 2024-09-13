// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectGameModeBase.generated.h"

/**
 * �ΰ���(���� �÷��� ��) ���� ����
 */
UCLASS()
class PROJECT_API AProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AProjectGameModeBase();


public:
	/** GameOverUserWidget - ���� ���� �� �˸� ���� */
	UPROPERTY()
		TSubclassOf<UUserWidget> GameOverUserWidgetClass;

	UPROPERTY()
		UUserWidget* GameOverUserWidget;

	/** GoalScoreUserWidget - �� ���ھ� ǥ�� ���� */
	UPROPERTY()
		TSubclassOf<UUserWidget> GoalScoreUserWidgetClass;

	UPROPERTY()
		UUserWidget* GoalScoreUserWidget;

	/** CaptionWidget - Ʃ�丮�� ĸ�� ���� */
	UPROPERTY()
		TSubclassOf<UUserWidget> CaptionWidgetClass;

	UPROPERTY()
		UUserWidget* CaptionWidget;

	/** PauseMenuUserWidget - ���� �÷��� �� pause menu ���� */
	UPROPERTY()
		TSubclassOf<UUserWidget> PauseMenuUserWidgetClass;

	UPROPERTY()
		UUserWidget* PauseMenuUserWidget;

};
