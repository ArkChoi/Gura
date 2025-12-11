// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Mannequin.generated.h"

UCLASS()
class GURA_API AMannequin : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMannequin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	TObjectPtr <class UCapsuleComponent> CapsuleComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	TObjectPtr <class USkeletalMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterState")
	float MaxHP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterState")
	float CurrentHP = MaxHP;

public:
	FORCEINLINE float GetCurrentHP() { return CurrentHP; }

	FORCEINLINE void SetCurrentHP(float ChangeHP) { CurrentHP = ChangeHP; }

	FORCEINLINE float GetMaxHP() { return MaxHP; }

};
