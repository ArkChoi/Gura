// Fill out your copyright notice in the Description page of Project Settings.

//현재 의미 없는 코드임..

#include "AnimNotify_AttackChoose.h"
#include "../../CPuppet.h"

FString UAnimNotify_AttackChoose::GetNotifyName_Implementation() const
{
	return TEXT("AttackChoose");
}

void UAnimNotify_AttackChoose::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACPuppet* BaseCharacter = Cast<ACPuppet>(MeshComp->GetOwner());
	if (BaseCharacter)
	{
		if (BaseCharacter->GetbIsAttackCharge())
		{

		}
		else
		{

		}

		BaseCharacter->ReSetbIsAttackCharge();
	}
}