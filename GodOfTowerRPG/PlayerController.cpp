// Fill out your copyright notice in the Description page of Project Settings.


#include "MYPlayerController.h"

AMYPlayerController::AMYPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	TeamId = FGenericTeamId(0);
}

FGenericTeamId AMYPlayerController::GetGenericTeamId() const
{
	return TeamId;
}