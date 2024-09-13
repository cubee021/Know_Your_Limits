// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Character/MyCharacter.h"
#include "Kismet/GameplayStatics.h"

UMyAnimInstance::UMyAnimInstance()
{
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		auto Character = Cast<AMyCharacter>(Pawn);
		if (Character)
		{
			CurrentSpeed = Character->GetCurrentSpeed();

			isFalling = Character->IsFalling(); 

			isDamaged = Character->IsDamaged;

			IsDead = Character->IsDead;

		}
	}
}

