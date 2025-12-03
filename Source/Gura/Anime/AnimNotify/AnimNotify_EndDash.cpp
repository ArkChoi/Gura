// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_EndDash.h"
#include "../../CPuppet.h"

FString UAnimNotify_EndDash::GetNotifyName_Implementation() const
{
	return TEXT("EndDash");
}

void UAnimNotify_EndDash::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACPuppet* BaseCharacter = Cast<ACPuppet>(MeshComp->GetOwner());
	if (BaseCharacter)
	{
		BaseCharacter->EndDash();
	}
}