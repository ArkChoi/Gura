// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerScoreWidget.h"
#include "Components/TextBlock.h"

void UPowerScoreWidget::ProssesScoreOutput(int32 InScore)
{
	Score->SetText(FText::AsNumber(InScore));
}
