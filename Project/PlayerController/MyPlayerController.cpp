// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "UI/MyUserWidget.h"
#include "UI/PauseMenuUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Game/ProjectGameModeBase.h"

AMyPlayerController::AMyPlayerController()
{
	static ConstructorHelpers::FClassFinder<UMyUserWidget> MyUserWidgetRef(TEXT("WidgetBlueprint'/Game/UI/BP_HUD.BP_HUD_C'"));
	if (MyUserWidgetRef.Class)
	{
		MyUserWidgetClass = MyUserWidgetRef.Class;
	}

	PressedNum = 0;
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MyUserWidget = CreateWidget(this, MyUserWidgetClass);
	if (MyUserWidget)
	{
		MyUserWidget->AddToViewport();
	}
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("PauseMenu"), EInputEvent::IE_Pressed, this, &AMyPlayerController::PauseMenu);
}

void AMyPlayerController::PauseMenu()
{
	AProjectGameModeBase* GameMode = Cast<AProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		UPauseMenuUserWidget* PauseMenu = Cast<UPauseMenuUserWidget>(GameMode->PauseMenuUserWidget);
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

