// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_EndImpulse.h"
#include "../../CPuppet.h"

FString UAnimNotify_EndImpulse::GetNotifyName_Implementation() const
{
	return TEXT("EndImpulse");
}

void UAnimNotify_EndImpulse::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACPuppet* BaseCharacter = Cast<ACPuppet>(MeshComp->GetOwner());
	if (BaseCharacter)
	{
		BaseCharacter->EndImpulse();
	}
}