// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameModeBase.generated.h"

/**
 * ���θ޴� ���� ����
 */
UCLASS()
class PROJECT_API AMainMenuGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

		AMainMenuGameModeBase();

public:
	/** MainBackgroundWidget - ���θ޴� ��׶��� �̹��� */
	UPROPERTY()
		TSubclassOf<UUserWidget> MainBackgroundWidgetClass;

	UPROPERTY()
		UUserWidget* MainBackgroundWidget;

	/** MainMenuUserWidget - ����ȭ�� ��ư ���� */
	UPROPERTY()
		TSubclassOf<UUserWidget> MainMenuUserWidgetClass;

	UPROPERTY()
		UUserWidget* MainMenuUserWidget;

	/** SettingsWidget - ���θ޴� ���� ���� */
	UPROPERTY()
		TSubclassOf<UUserWidget> SettingsWidgetClass;

	UPROPERTY()
		UUserWidget* SettingsWidget;

};
