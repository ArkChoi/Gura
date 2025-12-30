// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_EndGroggy.h"
#include "../../../Enemy/Mannequin.h"

FString UAnimNotify_EndGroggy::GetNotifyName_Implementation() const
{
	return TEXT("EndGroggy");
}

void UAnimNotify_EndGroggy::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AMannequin* Enemy = Cast<AMannequin>(MeshComp->GetOwner());
	if (Enemy)
	{
		Enemy->ReSetbIsGroggy();
		Enemy->SetCurrentGroggy(Enemy->GetMaxGroggy());
	}
}
