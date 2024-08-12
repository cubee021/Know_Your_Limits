// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	// 프레임마다 한 번씩 해당 함수 추가
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UMyAnimInstance();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float MaxSpeed; // 캐릭터 최대속도

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool isDamaged; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsDead;

	void PlayAttackMontage();

	FName GetAttackMontageName(int32 SectionIndex);
	void JumpToSection(int32 SectionIndex);


private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool isFalling;


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		class USoundBase* AttackSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontage;

	UFUNCTION()
		void AnimNotify_AttackPoint();

};


