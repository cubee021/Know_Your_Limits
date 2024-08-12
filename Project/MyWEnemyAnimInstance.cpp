// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWEnemyAnimInstance.h"

UMyWEnemyAnimInstance::UMyWEnemyAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("AnimMontage'/Game/Animations/Alien_Robot_Skeleton_Montage.Alien_Robot_Skeleton_Montage'"));

	if (AM.Succeeded())
	{
		AttackMontage = AM.Object;
	}
}

void UMyWEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner(); // 캐릭터 지정
	if (IsValid(Pawn))
	{
		Speed = Pawn->GetVelocity().Size(); // 프레임마다 캐릭터 속도 갱신

	}

}

void UMyWEnemyAnimInstance::PlayAttackMontage()
{
	if (!Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage, 1.f);
	}

}

