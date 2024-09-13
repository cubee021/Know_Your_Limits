// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"
#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "Components/TextBlock.h"
#include "Game/MyGameStateBase.h"
#include "Interface/MyUserWidgetInterface.h"

UMyUserWidget::UMyUserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UMyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ensure(TxtSpeedometer);
	ensure(TxtTimer);

	IMyUserWidgetInterface* Owner = Cast<IMyUserWidgetInterface>(GetOwningPlayerPawn());
	if (Owner)
	{
		Owner->UpdateWidgetSpeedometer(this);
	}
}

void UMyUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UpdateTimer();
}

void UMyUserWidget::UpdateSpeedometer(float CurrentSpeed, float MaxSpeed)
{
	const FString RingStr = FString::Printf(TEXT("%.f / %.f[km/h]"), CurrentSpeed / 10, MaxSpeed / 10);
	TxtSpeedometer->SetText(FText::FromString(RingStr));
}

void UMyUserWidget::UpdateTimer()
{
	// MilliSeconds를 구하려면 GetTimeSeconds의 소수점 아래 필요.
	// String으로 출력하기 위해 100을 곱해서 정수로 만들어야 함
	int32 IntegerFromTime = GetWorld()->GetTimeSeconds() / 1;
	int32 MilliSec = (GetWorld()->GetTimeSeconds() - IntegerFromTime) * 100;

	AMyGameStateBase* GameState = Cast<AMyGameStateBase>(GetWorld()->GetGameState());
	if (GameState)
	{
		GameState->Seconds = IntegerFromTime - (60 * GameState->CountSec);

		// 60초가 되면 1분 추가
		if (GameState->Seconds == 60 && (GetWorld()->GetTimeSeconds() - IntegerFromTime) < 0.1f)
		{
			GameState->Minutes++;
			GameState->CountSec++;
		}
	}

	const FString TimeStr = FString::Printf(TEXT("Time %02d : %02d : %02d"), GameState->Minutes, GameState->Seconds, MilliSec);
	TxtTimer->SetText(FText::FromString(TimeStr));
}
