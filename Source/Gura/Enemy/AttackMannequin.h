// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mannequin.h"
#include "AttackMannequin.generated.h"

/**
 * 
 */
UCLASS()
class GURA_API AAttackMannequin : public AMannequin
{
	GENERATED_BODY()

public:
	AAttackMannequin();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UAnimMontage> AttackMontage;

public:
	UFUNCTION()
	void Attack();

};
