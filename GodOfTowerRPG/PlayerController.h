// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "MYPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PAKAGELAST_API AMYPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
	AMYPlayerController();
private:

	FGenericTeamId TeamId;

	FGenericTeamId GetGenericTeamId() const;
};
