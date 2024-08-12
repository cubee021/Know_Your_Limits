// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndingScreenGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AEndingScreenGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AEndingScreenGameModeBase();

public:
	UPROPERTY()
		TSubclassOf<UUserWidget> HUD_Class; // 위젯 클래스 저장

	UPROPERTY()
		UUserWidget* CurrentWidget; // 위젯의 실제 주소 저장
};
