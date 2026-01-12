// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PowerChargeGaugeWidget.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class GURA_API UPowerChargeGaugeWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (BindWidget))
	TObjectPtr<UProgressBar> Gauge;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Owner")
	TObjectPtr<AActor> Owner;

public:
	FORCEINLINE AActor* GetOwner() { return Owner; }

	FORCEINLINE void SetOwner(AActor* InOwner) { Owner = InOwner; }

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void ProssesChargeGauge(float InGauge);

	void ReSetWidget();
};
