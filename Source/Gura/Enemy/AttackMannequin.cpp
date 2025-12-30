// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackMannequin.h"

AAttackMannequin::AAttackMannequin()
{

}

void AAttackMannequin::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(
		LeftTimerHandle,
		this,
		&AAttackMannequin::Attack,
		5.0f,
		true,
		0.f);
}

void AAttackMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AAttackMannequin::Attack()
{
	if (!GetCanPlayAnimMontage())
	{
		return;
	}

	PlayAnimMontage(AttackMontage, 1.0f);
}
