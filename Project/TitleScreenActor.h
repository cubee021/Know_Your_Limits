// Copyright 2023. cubee021. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TitleScreenActor.generated.h"

UCLASS()
class PROJECT_API ATitleScreenActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATitleScreenActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FTimerHandle TimerHandle;
};


