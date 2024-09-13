// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndingScreenGameModeBase.generated.h"

/**
 * ���� ������ ���� ȭ�� �����ִ� GameModeBase
 */
UCLASS()
class PROJECT_API AEndingScreenGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AEndingScreenGameModeBase();

public:
	/** EndingScreenWidget */
	UPROPERTY()
		TSubclassOf<UUserWidget> EndingScreenWidgetClass; // ���� Ŭ���� ����

	UPROPERTY()
		UUserWidget* EndingScreenWidget; // ������ ���� �ּ� ����
};
