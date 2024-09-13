// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyWEnemyAnimInstance.generated.h"

/**
 * AnimInstance of MyWalkingCharacter(Enemy)
 */
UCLASS()
class PROJECT_API UMyWEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMyWEnemyAnimInstance();

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	/** Current Speed of MyWalkingEnemy */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float Speed;
	
};
