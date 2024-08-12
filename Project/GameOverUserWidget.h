// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UGameOverUserWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Txt_TryAgain;


};
