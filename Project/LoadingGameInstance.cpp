// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadingGameInstance.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Slate.h"
#include "MoviePlayer.h"
#include "Blueprint/UserWidget.h"

ULoadingGameInstance::ULoadingGameInstance()
{

}

void ULoadingGameInstance::Init()
{
	Super::Init();

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &ULoadingGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &ULoadingGameInstance::EndLoadingScreen);

}

void ULoadingGameInstance::BeginLoadingScreen(const FString& InMapName)
{
	FLoadingScreenAttributes LoadingScreen;
	LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;

	if (Count == LoadingScreenWidgets.Num())
	{
		Count = 0;
	}

	LoadingScreenWidget = LoadingScreenWidgets[Count];
	Count++;

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), LoadingScreenWidget);
	LoadingScreen.WidgetLoadingScreen = Widget->TakeWidget();

	GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
}

void ULoadingGameInstance::EndLoadingScreen(UWorld* InLoadedWorld)
{
}