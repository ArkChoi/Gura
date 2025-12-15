// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackMannequin.h"

AAttackMannequin::AAttackMannequin()
{

}

void AAttackMannequin::Attack()
{
	FString SectionName = FString::Printf(TEXT("1"));
	PlayAnimMontage(AttackMontage, 1.0f, FName(*SectionName));
}
