// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void Tick(float deltatime) override;

private: 
	ATank* GetControlledTank() const;
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector&) const;
<<<<<<< HEAD
	bool GetLookDirection(FVector&) const;
	bool GetLookVectorHitLocation(FVector&, FVector)const;

	float LineTraceRange = 1000000;



=======
	
>>>>>>> parent of baae862... Player controller getting direction of point area
	UPROPERTY(EditAnywhere)
		float CrossHairXLocation = .5f;

	UPROPERTY(EditAnywhere)
		float CrossHairYLocation = .33333f;

};
