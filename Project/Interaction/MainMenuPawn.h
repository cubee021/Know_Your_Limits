// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MainMenuPawn.generated.h"

/**
* 메인 메뉴에서 마우스 클릭을 사용하기 위해 만든 폰
*/
UCLASS()
class PROJECT_API AMainMenuPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMainMenuPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
