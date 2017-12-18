// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
<<<<<<< HEAD
#include "Engine/World.h"
#include "Public/DrawDebugHelpers.h"
#include "Gameframework/Actor.h"
=======

>>>>>>> parent of baae862... Player controller getting direction of point area

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	GetControlledTank();
	//UE_LOG(LogTemp, Warning, TEXT("Player Tank Begin Play"));
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();

}


void ATankPlayerController::AimTowardsCrosshair() 
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; //OUT parameter

	if (GetSightRayHitLocation(HitLocation)) 
	{
<<<<<<< HEAD
		GetControlledTank()->AimAt(HitLocation);
		//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
=======
		UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
>>>>>>> parent of baae862... Player controller getting direction of point area
	}
}

// GetWorldLocation of linetrace through crosshair
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
<<<<<<< HEAD
	FVector LookDirection;
	if (GetLookDirection(LookDirection))
	{
		GetLookVectorHitLocation(OutHitLocation, LookDirection);
	}

	// Line-trace along the look direction (up to max range)
	//OutHitLocation = FVector(0.f, 0.f, 0.f);
	return true;
}

bool  ATankPlayerController::GetLookVectorHitLocation(FVector& OutHitLocation, FVector LookDirection) const {

	FHitResult HitResult;

	FVector LineTraceStart = PlayerCameraManager->GetCameraLocation();
	FVector LineTraceEnd = LineTraceStart + LookDirection * LineTraceRange;

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		LineTraceStart,
		LineTraceEnd,
		ECC_Visibility)) 
	{
		OutHitLocation = HitResult.Location;
		return(true);
	}

	return(false);
	
}

bool ATankPlayerController::GetLookDirection(FVector& LookDirection) const {
=======
>>>>>>> parent of baae862... Player controller getting direction of point area
	//Find crosshair position
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);

	FVector2D ScreenLocation = FVector2D(ViewPortSizeX * CrossHairXLocation, ViewPortSizeY * CrossHairYLocation);

	//UE_LOG(LogTemp, Warning, TEXT("Screen Location: %s"), *ScreenLocation.ToString());
	//deproject screen position to a world direction
	// Line-trace along the look direction (up to max range)
	OutHitLocation = FVector(0.f, 0.f, 0.f);
	return true;
}

ATank* ATankPlayerController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());
}




