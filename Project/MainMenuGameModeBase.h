// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AMainMenuGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

		AMainMenuGameModeBase();

public:
	UPROPERTY()
		TSubclassOf<UUserWidget> HUD_Class1; // 위젯 클래스 저장

	UPROPERTY()
		UUserWidget* BackgroundWidget; // 위젯의 실제 주소 저장


	UPROPERTY()
		TSubclassOf<UUserWidget> HUD_Class2;

	UPROPERTY()
		UUserWidget* MainMenuWidget;


	UPROPERTY()
		TSubclassOf<UUserWidget> HUD_Class3;

	UPROPERTY()
		UUserWidget* MainOptionsWidget;

};
