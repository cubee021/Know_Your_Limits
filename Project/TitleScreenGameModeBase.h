// Copyright 2023. cubee021. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TitleScreenGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ATitleScreenGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

		ATitleScreenGameModeBase();

public:
	UPROPERTY()
		TSubclassOf<UUserWidget> HUD_Class; // 위젯 클래스 저장

	UPROPERTY()
		UUserWidget* CurrentWidget; // 위젯의 실제 주소 저장
	
};
