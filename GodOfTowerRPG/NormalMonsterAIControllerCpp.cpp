// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalMonsterAIControllerCpp.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ANormalMonsterAIControllerCpp::ANormalMonsterAIControllerCpp()
{
	PrimaryActorTick.bCanEverTick = true;

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception")));
	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = false;

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &ANormalMonsterAIControllerCpp::OnMycharacterDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
	SetGenericTeamId(FGenericTeamId(1));

	Attack.Add(nullptr);
	nBehaviorTerm = 2.0f;
	bPattern1 = false;
}

void ANormalMonsterAIControllerCpp::BeginPlay()
{
	Super::BeginPlay();
}

void ANormalMonsterAIControllerCpp::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	AControlledCharacter = Cast<AMonsterParentsCPP>(GetPawn());
	nBehaviorCount = Attack.Num();
	if (AControlledCharacter != nullptr)
	{
		CharacterAnimation = AControlledCharacter->GetMesh()->GetAnimInstance();
	}
}

void ANormalMonsterAIControllerCpp::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetPawn() && AControlledCharacter->aTargetActor == nullptr)
	{
		MoveToLocation(AControlledCharacter->fvDefaultLocation);
		AControlledCharacter->bIsAttack = false;
	}
	if (GetPawn() && AControlledCharacter->aTargetActor && AControlledCharacter->bConditionControlled == false)
	{
		if (bPattern1 == false)
		{
			if (FVector::Distance(AControlledCharacter->fvDefaultLocation, AControlledCharacter->aTargetActor->GetActorLocation()) < 2000.0f)
			{
				
				if (GetPawn()->GetDistanceTo(AControlledCharacter->aTargetActor) > AControlledCharacter->fAttackRange)
					MoveToActor(AControlledCharacter->aTargetActor);
				else if (GetPawn()->GetDistanceTo(AControlledCharacter->aTargetActor) <= AControlledCharacter->fAttackRange && AControlledCharacter->bIsAttack == false)
				{
					if (Attack[AControlledCharacter->nBehaviorNumber] && CharacterAnimation)
					{
						AControlledCharacter->bIsAttack = true;
						FRotator LookAtTarget = UKismetMathLibrary::FindLookAtRotation(GetPawn()->GetActorLocation(), AControlledCharacter->aTargetActor->GetActorLocation());
						GetPawn()->SetActorRotation(FRotator(0, LookAtTarget.Yaw, 0));
						CharacterAnimation->Montage_Play(Attack[AControlledCharacter->nBehaviorNumber]);
						GetWorldTimerManager().SetTimer(BehaviorTimeHandle, this, &ANormalMonsterAIControllerCpp::fTimer, 1.0f, true, 2.0f);
					}
				}
			}
			else
			{
				
				AControlledCharacter->bReturnToSpawnLocation = true;
				MoveToLocation(AControlledCharacter->fvDefaultLocation);
				AControlledCharacter->aTargetActor = nullptr;
				AControlledCharacter->nBehaviorNumber = 0;
			}
		}
	}

}

void ANormalMonsterAIControllerCpp::OnMycharacterDetected(const TArray<AActor*>& DetectedPawns)
{
	if (DetectedPawns[0])
	{
		if (UGameplayStatics::GetPlayerCharacter(GetWorld(), 0) && GetPawn())
		{
			AControlledCharacter->aTargetActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
			MoveToActor(AControlledCharacter->aTargetActor);
			AControlledCharacter->bFindTarget = true;
		}
	}
}

ETeamAttitude::Type ANormalMonsterAIControllerCpp::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (const APawn* OtherPawn = Cast<APawn>(&Other))
	{
		if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
		{
			//Create an alliance with Team with ID 10 and set all the other teams as Hostiles:
			FGenericTeamId OtherTeamID = TeamAgent->GetGenericTeamId();
			if (OtherTeamID == 1) {
				return ETeamAttitude::Friendly;
			}
			else {
				return ETeamAttitude::Hostile;
			}
		}
	}
	return ETeamAttitude::Neutral;
}

void ANormalMonsterAIControllerCpp::fTimer()
{
	int nBehaviorTermCurrent = nBehaviorTerm;
	nBehaviorTermCurrent--;
	if (!(AControlledCharacter->aTargetActor))
	{
		GetWorldTimerManager().ClearTimer(BehaviorTimeHandle);
		AControlledCharacter->nBehaviorNumber = 0;
		AControlledCharacter->bIsAttack = false;
		return;
	}
	if (--nBehaviorTermCurrent <= 0)
	{
		GetWorldTimerManager().ClearTimer(BehaviorTimeHandle);
		if (AControlledCharacter->nBehaviorNumber < nBehaviorCount)
		{
			AControlledCharacter->nBehaviorNumber++;
			if (AControlledCharacter->nBehaviorNumber >= nBehaviorCount)
			{
				AControlledCharacter->nBehaviorNumber = 0;
			}
		}
		AControlledCharacter->bIsAttack = false;
		
		nBehaviorTermCurrent = nBehaviorTerm;
	}
}

void ANormalMonsterAIControllerCpp::FReturnSpawnLocation()
{
	if (AControlledCharacter)
	{
		if (AControlledCharacter->bReturn == false)
		{
			AControlledCharacter->bReturn = true;
			MoveToLocation(AControlledCharacter->fvDefaultLocation);
		}
	}
}
