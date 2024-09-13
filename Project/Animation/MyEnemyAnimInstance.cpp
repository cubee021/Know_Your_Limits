// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemyAnimInstance.h"
#include "Character/MyCharacter.h"
#include "Character/MyEnemy.h"
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
}
