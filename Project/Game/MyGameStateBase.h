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
	/** 게임 시작 후 경과된 초의 총합 (0 ~ 종료 전까지) */
	int32 CountSec;
	/** 게임 시작 후 경과된 분 (0 ~ 60) */
	int32 Minutes;
	/** 게임 시작 후 경과된 초 (0 ~ 60) */
	int32 Seconds;
};
