// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GuraPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GURA_API AGuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AGuraPlayerController();

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<class UInputMappingContext> InputMapping;

};
