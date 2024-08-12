// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemyAnimInstance.h"
#include "MyCharacter.h"
#include "MyEnemy.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

void UMyEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AMyCharacter* Pawn = Cast<AMyCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	AMyEnemy* Enemy = Cast<AMyEnemy>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyEnemy::StaticClass()));
	
	if (Pawn)
	{
		if (Enemy)
		{
			isOnCombat = Enemy->OnCombat;
		}

	}

	/*
	TArray<AActor*> ActorsToFind;
	if (UWorld* World = GetWorld())
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyEnemy::StaticClass(), ActorsToFind);
	}


	if (Pawn)
	{
		for (AActor* MyEnemy : ActorsToFind)
		{
			AMyEnemy* Enemy = Cast<AMyEnemy>(MyEnemy);

			if (Enemy)
			{

			}
		}
	}
	*/
}
