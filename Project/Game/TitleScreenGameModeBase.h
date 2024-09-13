// Copyright 2023. cubee021. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TitleScreenGameModeBase.generated.h"

/**
 * 게임 실행 시 타이틀 화면 관리
 */
UCLASS()
class PROJECT_API ATitleScreenGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

		ATitleScreenGameModeBase();

public:
	/** TitleScreenWidget */
	UPROPERTY()
		TSubclassOf<UUserWidget> TitleScreenWidgetClass; // 위젯 클래스 저장

	UPROPERTY()
		UUserWidget* TitleScreenWidget; // 위젯의 실제 주소 저장
	
};
