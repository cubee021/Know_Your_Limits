// Copyright 2023. cubee021. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TitleScreenGameModeBase.generated.h"

/**
 * ���� ���� �� Ÿ��Ʋ ȭ�� ����
 */
UCLASS()
class PROJECT_API ATitleScreenGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

		ATitleScreenGameModeBase();

public:
	/** TitleScreenWidget */
	UPROPERTY()
		TSubclassOf<UUserWidget> TitleScreenWidgetClass; // ���� Ŭ���� ����

	UPROPERTY()
		UUserWidget* TitleScreenWidget; // ������ ���� �ּ� ����
	
};
