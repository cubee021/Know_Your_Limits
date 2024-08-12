// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "PauseMenuUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectGameModeBase.h"

AMyPlayerController::AMyPlayerController()
{
	PressedNum = 0;
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("PauseMenu"), EInputEvent::IE_Pressed, this, &AMyPlayerController::PauseMenu);
}

void AMyPlayerController::PauseMenu()
{
	AProjectGameModeBase* GameMode = Cast<AProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode) // 이미 있는 UI 불러오는 방법
	{
		UPauseMenuUserWidget* PauseMenu = Cast<UPauseMenuUserWidget>(GameMode->CurrentWidget5);
		if (PauseMenu)
		{
			if (PressedNum % 2 == 0)
			{
				PauseMenu->SetVisibility(ESlateVisibility::Visible);

				//bShowMouseCursor = true;

				UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
				UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetPause(true);

				PressedNum++;

			}
			else
			{
				PauseMenu->SetVisibility(ESlateVisibility::Collapsed);

				//bShowMouseCursor = false;

				UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;
				UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetPause(false);

				PressedNum = 0;
			}

		}
	}

}

