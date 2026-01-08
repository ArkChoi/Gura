// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PunchMachine.generated.h"

class UStaticMeshComponent;
class UPhysicsConstraintComponent;
class USceneComponent;

UCLASS()
class GURA_API APunchMachine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APunchMachine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	TObjectPtr <USceneComponent> Scene;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	TObjectPtr <UStaticMeshComponent> Plane;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	TObjectPtr <UStaticMeshComponent> Body;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	TObjectPtr <UPhysicsConstraintComponent> PhysicsConstraint;

public:
	UFUNCTION()
	void ProcessOnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(NetMulticast, Unreliable)
	void S2A_PlayImpulse();
	void S2A_PlayImpulse_Implementation();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", Replicated)
	FVector ImpulseForce;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
