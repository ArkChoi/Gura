// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_EnemyBaseAttack.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../../../Enemy/Mannequin.h"
#include "kismet/GameplayStatics.h"
#include "../../../DamageType/StrikeDamageType.h"

FString UAnimNotify_EnemyBaseAttack::GetNotifyName_Implementation() const
{
	return TEXT("EnemyBaseAttack");
}

void UAnimNotify_EnemyBaseAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AMannequin* Mannequin = Cast<AMannequin>(MeshComp->GetOwner());
	if (Mannequin)
	{
		FVector TempVector = Mannequin->GetActorLocation();
		TArray<TEnumAsByte<EObjectTypeQuery>> TempArray;
		TEnumAsByte<EObjectTypeQuery> Pawn = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn);
		TempArray.Add(Pawn);
		TArray<AActor*> IgnoreActor;
		IgnoreActor.Add(Mannequin);
		FHitResult ResultHit;

		UKismetSystemLibrary::SphereTraceSingleForObjects(Mannequin->GetWorld(), TempVector, TempVector, 100.f, TempArray, false, IgnoreActor, EDrawDebugTrace::ForDuration, ResultHit, true);

		if (ResultHit.bBlockingHit)
		{
			UGameplayStatics::ApplyDamage(ResultHit.GetActor(), 10.f, Mannequin->GetController(), Mannequin, UStrikeDamageType::StaticClass());
		}
	}
}
