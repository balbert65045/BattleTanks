// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ATank* ControlledTank = GetControlledTank();
	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Tank %s Found"), *ControlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Not Found"));
	}

	ATank* PlayerTank = GetPlayerTank();

	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Tank %s found player: %s"), *ControlledTank->GetName(), *PlayerTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank %s could not find player"), *ControlledTank->GetName());
	}
	//UE_LOG(LogTemp, Warning, TEXT("Player Tank Begin Play"));
}


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}



