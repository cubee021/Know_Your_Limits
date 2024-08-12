// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CrosshairUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UCrosshairUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
		class UImage* Img_Crosshair;
	
};
