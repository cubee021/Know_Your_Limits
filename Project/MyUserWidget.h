// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* CollectedRing;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* txt_Time;

};
