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
		TSubclassOf<UUserWidget> HUD_Class; // ���� Ŭ���� ����

	UPROPERTY()
		UUserWidget* CurrentWidget; // ������ ���� �ּ� ����
	
};
