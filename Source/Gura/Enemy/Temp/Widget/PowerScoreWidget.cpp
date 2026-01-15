// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerScoreWidget.h"
#include "Components/TextBlock.h"
#include "../PunchMachine.h"
#include "Kismet/GameplayStatics.h"

void UPowerScoreWidget::NativeConstruct()
{
	//SetVisibility(ESlateVisibility::Hidden);

	TArray<AActor*> ActorArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APunchMachine::StaticClass(), ActorArray);
	for (AActor* Actor : ActorArray)
	{
		APunchMachine* Machine = Cast<APunchMachine>(Actor);
		if (Machine)
		{
			Machine->ScoreOutput.AddDynamic(this, &UPowerScoreWidget::ProssesScoreOutput);
		}
	}
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
