// Fill out your copyright notice in the Description page of Project Settings.


#include "GuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"

AGuraPlayerController::AGuraPlayerController()
{
}

void AGuraPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			InputSystem->AddMappingContext(InputMapping, 0);
		}
	}
}

void AGuraPlayerController::OnUnPossess()
{
	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			InputSystem->RemoveMappingContext(InputMapping);
		}
	}

	Super::OnUnPossess();
}
