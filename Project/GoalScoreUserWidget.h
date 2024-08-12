// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GoalScoreUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UGoalScoreUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* txt_TimeScore;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* txt_EnemyScore;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* txt_RingScore;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* txt_Total;

};
