// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MonsterParentsCPP.h"
#include "Animation/AnimInstance.h"
#include "NormalMonsterAIControllerCpp.generated.h"

/**
 * 
 */
UCLASS()
class PAKAGELAST_API ANormalMonsterAIControllerCpp : public AAIController
{
	GENERATED_BODY()
public:
	ANormalMonsterAIControllerCpp();

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float AISightRadius = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float AISightAge = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float AILoseSightRadius = AISightRadius + 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float AIFieldOfView = 180.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		class UAISenseConfig_Sight* SightConfig;
	UFUNCTION(BlueprintCallable)
		void OnMycharacterDetected(const TArray<AActor*>& DetectedPawns);


	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AIMontage)
		TArray<UAnimMontage*> Attack;

	int nBehaviorTerm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AMonsterParentsCPP* AControlledCharacter;
	UAnimInstance* CharacterAnimation;
	FTimerHandle BehaviorTimeHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bPattern1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int nBehaviorCount;

	void fTimer();
	void FReturnSpawnLocation();
};

