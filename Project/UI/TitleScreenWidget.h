// Copyright 2023. cubee021. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UTitleScreenWidget : public UUserWidget
{
	GENERATED_BODY()

		virtual void NativeConstruct();
	
public:
	UPROPERTY(BlueprintReadWrite, Transient, Category = "Animation", meta = (BindWidgetAnim))
		class UWidgetAnimation* FadeOut;
};
