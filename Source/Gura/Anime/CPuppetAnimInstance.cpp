// Fill out your copyright notice in the Description page of Project Settings.


#include "CPuppetAnimInstance.h"
#include "../CPuppet.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"

void UCPuppetAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (ACPuppet* Player = Cast<ACPuppet>(TryGetPawnOwner()))
	{
		GroundSpeed = Player->GetCharacterMovement()->Velocity.Size2D();
		Direction = UKismetAnimationLibrary::CalculateDirection(Player->GetCharacterMovement()->Velocity, Player->GetActorRotation());
		bIsDash = Player->GetbIsDash();
	}
}
