// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerChargeGaugeWidget.h"
#include "Components/ProgressBar.h"
#include "../../../WorldSetting/GuraPlayerController.h"
#include "../../../CPuppet.h"

void UPowerChargeGaugeWidget::NativeConstruct()
{
	//SetVisibility(ESlateVisibility::Hidden);
	AGuraPlayerController* PC = Cast<AGuraPlayerController>(GetOwningPlayer());
	if (PC)
	{
		ACPuppet* Player = Cast<ACPuppet>(PC->GetPawn());
		if (Player)
		{
			Player->ChargeGauge.AddDynamic(this, &UPowerChargeGaugeWidget::ProssesChargeGauge);
		}
	}
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
