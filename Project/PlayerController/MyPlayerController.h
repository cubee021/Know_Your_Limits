// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

public:
	// Pause Menu Section
	/** Open/close pause menu */
	void PauseMenu();

	/** If pressed once - open pause menu, if pressed twice - close pause menu */
	int32 PressedNum;

protected:
	/** Player HUD (Timer, Current Speed) */
	// ���� Ŭ���� ����
	UPROPERTY()
		TSubclassOf<class UMyUserWidget> MyUserWidgetClass; 
	// ������ ���� �ּ� ����
	UPROPERTY()
		UUserWidget* MyUserWidget; 
};
