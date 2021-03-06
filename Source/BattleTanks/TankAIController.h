// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	
public:


private: 
	void BeginPlay() override;
	void Tick(float deltatime) override;

	void AimTowardsPlayer() const;


	ATank* GetControlledTank() const;
	ATank* GetPlayerTank() const;
	
};
