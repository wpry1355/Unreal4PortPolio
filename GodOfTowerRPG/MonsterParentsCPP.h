// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonsterParentsCPP.generated.h"

UCLASS()
class PAKAGELAST_API AMonsterParentsCPP : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonsterParentsCPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = aTarget)
		AActor* aTargetActor;

	bool bIsAttack;
	bool bFindTarget;
	bool bReturn;
	int nBehaviorNumber;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Range)
		float fAttackRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = return)
		bool bReturnToSpawnLocation;
	UPROPERTY(BlueprintReadWrite)
		bool bConditionControlled;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector fvDefaultLocation;
};
