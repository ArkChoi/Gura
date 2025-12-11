// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_ComboReset.h"
#include "../../CPuppet.h"

FString UAnimNotify_ComboReset::GetNotifyName_Implementation() const
{
	return TEXT("ComboReset");
}

void UAnimNotify_ComboReset::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACPuppet* BaseCharacter = Cast<ACPuppet>(MeshComp->GetOwner());
	if (BaseCharacter)
	{
		if (BaseCharacter->GetbIsComboAttack())
		{
			BaseCharacter->PlayComboMontage(BaseCharacter->GetComboCount());
			return;
		}
		BaseCharacter->SetComboCount(1);
	}
}
