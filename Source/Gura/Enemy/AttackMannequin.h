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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UAnimMontage> AttackMontage;

	FTimerHandle LeftTimerHandle;

	float AttackTime = 0;

public:
	UFUNCTION()
	void Attack();

};
