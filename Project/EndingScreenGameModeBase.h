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
		TSubclassOf<UUserWidget> HUD_Class; // ���� Ŭ���� ����

	UPROPERTY()
		UUserWidget* CurrentWidget; // ������ ���� �ּ� ����
};
