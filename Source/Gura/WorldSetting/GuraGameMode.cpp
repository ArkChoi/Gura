// Fill out your copyright notice in the Description page of Project Settings.


#include "GuraGameMode.h"
#include "../CPuppet.h"
#include "GuraPlayerController.h"

AGuraGameMode::AGuraGameMode()
{
	DefaultPawnClass = ACPuppet::StaticClass();
	PlayerControllerClass = AGuraPlayerController::StaticClass();
}
