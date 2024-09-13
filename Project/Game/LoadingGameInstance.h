// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LoadingGameInstance.generated.h"

/**
 * ������ �ٲ� �� ��� ��Ÿ���� �ε� ȭ��
 */
UCLASS()
class PROJECT_API ULoadingGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	ULoadingGameInstance();

	virtual void Init() override;

public:
	UFUNCTION()
		virtual void BeginLoadingScreen(const FString& InMapName);

	UFUNCTION()
		virtual void EndLoadingScreen(UWorld* InLoadedWorld);

protected:
	/** Loading widgets that will be used */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loading Screen")
		TArray<TSubclassOf<class UUserWidget>> LoadingScreenWidgets;

	/** Loading widget currently selected */
	UPROPERTY()
		TSubclassOf<class UUserWidget> LoadingScreenWidget;

	/** Current index of LoadingScreenWidgets */
	int32 Index = 0;
};
