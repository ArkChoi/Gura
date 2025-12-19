// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_UnPerfectGuard.h"
#include "../../CPuppet.h"

FString UAnimNotify_UnPerfectGuard::GetNotifyName_Implementation() const
{
	return TEXT("EndPerfectGuard");
}

void UAnimNotify_UnPerfectGuard::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACPuppet* BaseCharacter = Cast<ACPuppet>(MeshComp->GetOwner());
	if (BaseCharacter)
	{
		BaseCharacter->ReSetbIsPerfectGuard();
	}
}
