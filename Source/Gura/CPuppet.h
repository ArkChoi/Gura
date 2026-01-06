// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPuppet.generated.h"

struct FInputActionValue;

class UAnimMontage;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> GuardAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> LockOnAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", Replicated)
	TObjectPtr<class AMannequin> LockEnemy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", Replicated)
	FVector2D MovementValue;

public:
	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	void Attack(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable)
	void C2S_Attack();
	void C2S_Attack_Implementation();

	UFUNCTION()
	void PlayComboMontage(int32 InComboCount);

	UFUNCTION(NetMulticast, Unreliable)
	void S2A_PlayComboMontage();
	void S2A_PlayComboMontage_Implementation();

	UFUNCTION()
	void PowerAttack();

	UFUNCTION(Server, Reliable)
	void C2S_PowerAttack();
	void C2S_PowerAttack_Implementation();

	UFUNCTION()
	void Charged(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable)
	void C2S_Charged();
	void C2S_Charged_Implementation();

	UFUNCTION()
	void DoRun();

	UFUNCTION(Server, Reliable)
	void C2S_DoRun();
	void C2S_DoRun_Implementation();

	UFUNCTION()
	void ResetWalk();

	UFUNCTION(Server, Reliable)
	void C2S_ResetWalk();
	void C2S_ResetWalk_Implementation();

	UFUNCTION()
	void Dash();

	UFUNCTION(Server, Reliable)
	void C2S_Dash();
	void C2S_Dash_Implementation();

	UFUNCTION()
	void PerfectGuard();

	UFUNCTION(Server, Reliable)
	void C2S_PerfectGuard();
	void C2S_PerfectGuard_Implementation();

	UFUNCTION()
	void DoGuard();

	UFUNCTION(Server, Reliable)
	void C2S_DoGuard();
	void C2S_DoGuard_Implementation();

	UFUNCTION()
	void UnDoGuard();

	UFUNCTION(Server, Reliable)
	void C2S_UnDoGuard();
	void C2S_UnDoGuard_Implementation();

	UFUNCTION()
	void OnLockOn();

	UFUNCTION(Server, Reliable)
	void C2S_OnLockOn();
	void C2S_OnLockOn_Implementation();

	//State
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float CharacterSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float CurrentHP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float MaxHP = 100;

	float PowerChargingTime = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", Replicated)
	int32 ComboCount = 1;

public:
	FORCEINLINE float GetCharacterSpeed() { return CharacterSpeed; }

	void SetCharacterSpeed(float ChangeSpeed);

	FORCEINLINE float GetCurrentHP() { return CurrentHP; }

	FORCEINLINE void SetCurrentHP(float ChangeHP) { CurrentHP = ChangeHP; }

	FORCEINLINE float GetMaxHP() { return MaxHP; }

	void ReSetComboCount();

	FORCEINLINE int32 GetComboCount() { return ComboCount; }

	//Anime
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	uint8 bIsRun : 1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	uint8 bIsDash : 1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim", Replicated)
	uint8 bIsGuard : 1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim", Replicated)
	uint8 bIsComboAttack : 1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	uint8 bIsImpulse : 1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	uint8 bIsPerfectGuard : 1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim", Replicated)
	uint8 bIsAttack : 1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim", Replicated)
	uint8 bIsAttackCharge : 1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim", Replicated)
	uint8 bIsLockOn : 1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UAnimMontage> DashMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UAnimMontage> ChargeAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UAnimMontage> HitMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UAnimMontage> PerfectGuardMontage;

public:
	FORCEINLINE float GetbIsDash() { return bIsDash; }

	FORCEINLINE float GetbIsGuard() { return bIsGuard; }

	FORCEINLINE float GetbIsComboAttack() { return bIsComboAttack; }

	FORCEINLINE float GetbIsPerfectGuard() { return bIsPerfectGuard; }

	FORCEINLINE void ReSetbIsPerfectGuard() { bIsPerfectGuard = false; }

	FORCEINLINE float GetbIsAttack() { return bIsAttack; }

	FORCEINLINE void ReSetbIsAttack() { bIsAttack = false; }

	FORCEINLINE float GetbIsAttackCharge() { return bIsAttackCharge; }

	FORCEINLINE void ReSetbIsAttackCharge() { bIsAttackCharge = false; }

	FORCEINLINE float GetbIsLockOn() { return bIsLockOn; }

	FORCEINLINE void ReSetbIsLockOn() { bIsLockOn = false; }

	void ReSetbIsComboAttack();

	void EndDash();

	void EndImpulse();

	void ReSetStatus();

	bool GetCanPlayAnimMontage();

public:
	UFUNCTION()
	void ProcessOnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
