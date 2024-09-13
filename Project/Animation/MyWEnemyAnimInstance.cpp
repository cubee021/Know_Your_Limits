// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWEnemyAnimInstance.h"

UMyWEnemyAnimInstance::UMyWEnemyAnimInstance()
{
}

void UMyWEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		Speed = Pawn->GetVelocity().Size();
	}
}

