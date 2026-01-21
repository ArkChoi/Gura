// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	SetReplicates(true);
	SetReplicateMovement(true);
	bNetLoadOnClient = true;
	bNetUseOwnerRelevancy = true;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::PlayAttack()
{
	if (AttackMontage)
	{

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayAttack"));
	}
}

void AWeaponBase::PlayChargeAttack()
{
	if (ChargeAttackMontage)
	{

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayChargeAttack"));
	}
}

