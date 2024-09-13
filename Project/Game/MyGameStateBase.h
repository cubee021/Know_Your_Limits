// Copyright 2023. cubee021. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AMyGameStateBase();

public:
	/** ���� ���� �� ����� ���� ���� (0 ~ ���� ������) */
	int32 CountSec;
	/** ���� ���� �� ����� �� (0 ~ 60) */
	int32 Minutes;
	/** ���� ���� �� ����� �� (0 ~ 60) */
	int32 Seconds;
};
