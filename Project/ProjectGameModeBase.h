// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API AProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

		AProjectGameModeBase();


public:
	UPROPERTY()
		TSubclassOf<UUserWidget> HUD_Class; // 위젯 클래스 저장

	UPROPERTY()
		UUserWidget* CurrentWidget; // 위젯의 실제 주소 저장


	UPROPERTY()
		TSubclassOf<UUserWidget> HUD_Class2;

	UPROPERTY()
		UUserWidget* CurrentWidget2;


	UPROPERTY()
		TSubclassOf<UUserWidget> HUD_Class3; 

	UPROPERTY()
		UUserWidget* CurrentWidget3; 


	UPROPERTY()
		TSubclassOf<UUserWidget> HUD_Class4;

	UPROPERTY()
		UUserWidget* CurrentWidget4;


	UPROPERTY()
		TSubclassOf<UUserWidget> HUD_Class5;

	UPROPERTY()
		UUserWidget* CurrentWidget5;

};
