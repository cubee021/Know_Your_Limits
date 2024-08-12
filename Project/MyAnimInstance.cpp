// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MyCharacter.h"
#include "Kismet/GameplayStatics.h"

UMyAnimInstance::UMyAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("AnimMontage'/Game/Animations/Character_Montage.Character_Montage'"));
	if (AM.Succeeded())
	{
		AttackMontage = AM.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> SB1(TEXT("SoundWave'/Game/Sounds/whoosh-transitions-sfx-01-118227.whoosh-transitions-sfx-01-118227'"));
	if (SB1.Succeeded())
	{
		AttackSound = SB1.Object;
	}
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner(); // 캐릭터 지정
	if (IsValid(Pawn))
	{
		MaxSpeed = Pawn->GetVelocity().Size(); // 프레임마다 캐릭터 속도 갱신

		auto Character = Cast<AMyCharacter>(Pawn);
		if (Character)
		{
			isFalling = Character->GetMovementComponent()->IsFalling(); 

			isDamaged = Character->isDamaged;

			IsDead = Character->IsDead;

		}
	}
}

void UMyAnimInstance::PlayAttackMontage()
{
	if (!Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage, 1.f);
	}

}

FName UMyAnimInstance::GetAttackMontageName(int32 SectionIndex)
{
	return FName(*FString::Printf(TEXT("Attack%d"), SectionIndex));
}

void UMyAnimInstance::JumpToSection(int32 SectionIndex)
{
	FName Name = GetAttackMontageName(SectionIndex);
	Montage_JumpToSection(Name, AttackMontage);
}

void UMyAnimInstance::AnimNotify_AttackPoint()
{
	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		UGameplayStatics::PlaySoundAtLocation(this, AttackSound, Pawn->GetActorLocation());
	}
}
