// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LoadingGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API ULoadingGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	ULoadingGameInstance();

	virtual void Init() override;

	UFUNCTION()
		virtual void BeginLoadingScreen(const FString& InMapName);

	UFUNCTION()
		virtual void EndLoadingScreen(UWorld* InLoadedWorld);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loading Screen")
		TArray<TSubclassOf<class UUserWidget>> LoadingScreenWidgets;

private:
	UPROPERTY()
		TSubclassOf<class UUserWidget> LoadingScreenWidget;

	int32 Count = 0;
};
