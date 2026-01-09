// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PowerScoreWidget.generated.h"

class UTextBlock;
class AActor;

/**
 * 
 */
UCLASS()
class GURA_API UPowerScoreWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (BindWidget))
	TObjectPtr<UTextBlock> Score;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Owner")
	TObjectPtr<AActor> Owner;

public:
	FORCEINLINE AActor* GetOwner() { return Owner; }

	FORCEINLINE void SetOwner(AActor* InOwner) { Owner = InOwner; }

public:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable)
	void ProssesScoreOutput(int32 InScore);


};
