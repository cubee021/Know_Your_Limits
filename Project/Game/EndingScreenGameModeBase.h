// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndingScreenGameModeBase.generated.h"

/**
 * 게임 끝나고 엔딩 화면 보여주는 GameModeBase
 */
UCLASS()
class PROJECT_API AEndingScreenGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AEndingScreenGameModeBase();

public:
	/** EndingScreenWidget */
	UPROPERTY()
		TSubclassOf<UUserWidget> EndingScreenWidgetClass; // 위젯 클래스 저장

	UPROPERTY()
		UUserWidget* EndingScreenWidget; // 위젯의 실제 주소 저장
};
