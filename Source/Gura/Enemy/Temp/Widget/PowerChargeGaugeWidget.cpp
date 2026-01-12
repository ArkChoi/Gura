// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerChargeGaugeWidget.h"
#include "Components/ProgressBar.h"

void UPowerChargeGaugeWidget::NativeConstruct()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UPowerChargeGaugeWidget::ProssesChargeGauge(float InGauge)
{
	if (Gauge)
	{ 
		SetVisibility(ESlateVisibility::Visible);
		Gauge->SetPercent(InGauge);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Found Gauge"));
	}
	if (InGauge == 0)
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}
