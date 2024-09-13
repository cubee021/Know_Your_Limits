// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenuUserWidget.h"
#include "MyUserWidget.h"
#include "PlayerController/MyPlayerController.h"
#include "Character/MyCharacter.h"
#include "PauseSettingsUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Game/ProjectGameModeBase.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UPauseMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	btn_Resume->OnClicked.AddDynamic(this, &UPauseMenuUserWidget::Resume);
	btn_Restart->OnClicked.AddDynamic(this, &UPauseMenuUserWidget::Restart);
	btn_Settings->OnClicked.AddDynamic(this, &UPauseMenuUserWidget::ToOptions);
	btn_toMain->OnClicked.AddDynamic(this, &UPauseMenuUserWidget::ToMainMenu);
	
	static ConstructorHelpers::FClassFinder<UPauseSettingsUserWidget> UI_HUD(TEXT("WidgetBlueprint'/Game/UI/BP_PauseSettings.BP_PauseSettings_C'"));
	if (UI_HUD.Succeeded())
	{
		HUD_Class = UI_HUD.Class;

		PauseSettings = CreateWidget(GetWorld(), HUD_Class);
		if (PauseSettings)
		{
			PauseSettings->AddToViewport();
			PauseSettings->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UPauseMenuUserWidget::Resume()
{
	AMyPlayerController* MyController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	SetVisibility(ESlateVisibility::Collapsed);

	MyController->bShowMouseCursor = false;
	MyController->SetPause(false);
	MyController->PressedNum = 0;

}

void UPauseMenuUserWidget::Restart()
{
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{
		MyCharacter->StopTimer();
	}

	if (GetWorld()->GetName() == FString("Map_NorthenIsle_01"))
	{
		UGameplayStatics::OpenLevel(this, FName("Map_NorthenIsle_01"));
	}
	else if (GetWorld()->GetName() == FString("Map_NorthenIsle_2"))
	{
		UGameplayStatics::OpenLevel(this, FName("Map_NorthenIsle_2"));
	}

}

void UPauseMenuUserWidget::ToOptions()
{
	PauseSettings->SetVisibility(ESlateVisibility::Visible);
	SetVisibility(ESlateVisibility::Collapsed);
}

void UPauseMenuUserWidget::ToMainMenu()
{
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{
		MyCharacter->StopTimer();
	}

	AMyPlayerController* MyController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	AProjectGameModeBase* GameMode = Cast<AProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode && MyController) // 이미 있는 UI 불러오는 방법
	{
		//UMyUserWidget* MyHUD = Cast<UMyUserWidget>(GameMode->CurrentWidget);
		//if (MyHUD)
		//{
		//	MyHUD->RemoveFromViewport();
		//}

	}

	RemoveFromViewport();

	MyController->SetPause(false);
	MyController->ClientSetCameraFade(true, FColor::Black, FVector2D(0.0, 1.0), 1.5f, false, true);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			UGameplayStatics::OpenLevel(this, FName("MainMenu"));
		}), 2.f, false);

}

