// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHPWidget.generated.h"

class UProgressBar;
class APawn;
/**
 * 
 */
UCLASS( Abstract )
class GURA_API UEnemyHPWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (BindWidget))
	TObjectPtr<UProgressBar> EnemyHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Owner")
	TObjectPtr<APawn> OwnerPawn;

public:
	FORCEINLINE APawn* GetOwnerPawn() { return OwnerPawn; }

	FORCEINLINE void SetOwnerPawn(APawn* InOwnerPawn) { OwnerPawn = InOwnerPawn; }

public:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable)
	void ProssesChangeHP(float InHP);
};
