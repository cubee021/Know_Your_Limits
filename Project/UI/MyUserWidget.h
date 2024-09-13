// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * Character HUD
 */
UCLASS()
class PROJECT_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UMyUserWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void UpdateSpeedometer(float CurrentSpeed, float MaxSpeed);
	void UpdateTimer();

public:
	/** Current speed and Max speed */
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TxtSpeedometer;
	/** Timer on player */
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TxtTimer;

};
