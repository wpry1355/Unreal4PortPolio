// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterParentsCPP.h"
#include "NormalMonsterAIControllerCpp.h"

// Sets default values
AMonsterParentsCPP::AMonsterParentsCPP()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	aTargetActor = nullptr;
	bFindTarget = false;
	fvDefaultLocation = FVector(0);
	fAttackRange = 150;
	bIsAttack = false;
	bReturn = false;
	nBehaviorNumber = 0;
	bConditionControlled = false;
	bReturnToSpawnLocation = false;
}

// Called when the game starts or when spawned
void AMonsterParentsCPP::BeginPlay()
{
	Super::BeginPlay();
	fvDefaultLocation = GetActorLocation();
}

// Called every frame
void AMonsterParentsCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonsterParentsCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

