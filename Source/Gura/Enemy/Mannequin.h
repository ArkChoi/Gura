// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
//#include "GenericTeamAgentInterface.h"
#include "Mannequin.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeHP, const float, InHP);

UCLASS()
class GURA_API AMannequin : public ACharacter
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

public:
	FOnChangeHP OnChangeHP;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterState")
	float MaxHP = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterState")
	float CurrentHP = MaxHP;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TObjectPtr <class UWidgetComponent> WidgetHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterState")
	float MaxGroggy = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterState")
	float CurrentGroggy = 0;

public:
	FORCEINLINE float GetCurrentHP() { return CurrentHP; }

	FORCEINLINE void SetCurrentHP(float ChangeHP) { CurrentHP = ChangeHP; }

	FORCEINLINE float GetMaxHP() { return MaxHP; }

	FORCEINLINE float GetCurrentGroggy() { return CurrentGroggy; }

	FORCEINLINE void SetCurrentGroggy(float ChangeGroggy) { CurrentGroggy = ChangeGroggy; }

	FORCEINLINE float GetMaxGroggy() { return MaxGroggy; }

public:
	UFUNCTION()
	void ProcessOnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser );

public:
	void RecoverHP();

	//Anim
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UAnimMontage> StunMontage;
};
