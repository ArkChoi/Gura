// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerScoreWidget.h"
#include "Components/TextBlock.h"

void UPowerScoreWidget::NativeConstruct()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UPowerScoreWidget::ProssesScoreOutput(int32 InScore)
{
	SetVisibility(ESlateVisibility::Visible);
	Score->SetText(FText::AsNumber(InScore));

	if (InScore == 0)
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}
