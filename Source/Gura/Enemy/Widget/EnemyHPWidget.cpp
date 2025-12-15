// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHPWidget.h"
#include "../Mannequin.h"
#include "Components/ProgressBar.h"
#include "GameFramework/Pawn.h"

void UEnemyHPWidget::NativeOnInitialized() //왜 작동 안해요?
{
	Super::NativeOnInitialized();

	/*AMannequin* Mannequin = Cast<AMannequin>(GetOwnerPawn());
	if (Mannequin)
	{
		float PercentHP = Mannequin->GetCurrentHP() / Mannequin->GetMaxHP();
		EnemyHP->SetPercent(PercentHP);

		UE_LOG(LogTemp, Warning, TEXT("AddDynamic"));
		Mannequin->OnChangeHP.AddDynamic(this, &UEnemyHPWidget::ProssesChangeHP);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NonMannequin"));
	}*/
}

void UEnemyHPWidget::ProssesChangeHP(float InHP)
{
	if (EnemyHP)
	{
		EnemyHP->SetPercent(InHP);
	}
}
