// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../CPuppet.h"
#include "CPuppetAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class GURA_API UCPuppetAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	float GroundSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	float Direction;
};
