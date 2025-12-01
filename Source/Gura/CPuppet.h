// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPuppet.generated.h"

struct FInputActionValue;

UCLASS()
class GURA_API ACPuppet : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPuppet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Base And Movement
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	TObjectPtr <class USpringArmComponent> SpringArm;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	TObjectPtr <class UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> PowerAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> DashAction;

public:
	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	void Attack(const FInputActionValue& Value);

	UFUNCTION()
	void PowerAttack();

	void Charged(const FInputActionValue& Value);

	UFUNCTION()
	void DoRun();

	UFUNCTION()
	void UnDoRun();

	UFUNCTION()
	void Dash();

	//State
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float CharacterSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float CurrentHP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float MaxHP = 100;

	float PowerChargingTime = 0;

public:
	FORCEINLINE float GetCharacterSpeed() { return CharacterSpeed; }

	void SetCharacterSpeed(float ChangeSpeed);

	FORCEINLINE float GetCurrentHP() { return CurrentHP; }

	FORCEINLINE void SetCurrentHP(float ChangeHP) { CurrentHP = ChangeHP; }

	FORCEINLINE float GetMaxHP() { return MaxHP; }

	//Anime
protected:
	uint8 bIsRun : 1 = false;

};
