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

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	TObjectPtr <class USpringArmComponent> SpringArm;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	TObjectPtr <class UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> LookAction;

public:
	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Look(const FInputActionValue& Value);

protected:
	float CharacterSpeed = 300.f;

public:
	FORCEINLINE float GetCharacterSpeed() { return CharacterSpeed; }

	void SetCharacterSpeed(float ChangeSpeed);
};
