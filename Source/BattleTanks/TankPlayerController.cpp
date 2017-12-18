// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "Public/DrawDebugHelpers.h"
#include "Gameframework/Actor.h"

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
		GetControlledTank()->AimAt(HitLocation);
		//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
	}
}

// GetWorldLocation of linetrace through crosshair
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
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
	//Find crosshair position
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);

	FVector2D ScreenLocation = FVector2D(ViewPortSizeX * CrossHairXLocation, ViewPortSizeY * CrossHairYLocation);

	FVector WorldLocation;
	return (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection));
}

ATank* ATankPlayerController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());
}




