// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetUpInputComponent();
	

}

// Look for Physics Handle
void UGrabber::FindPhysicsHandleComponent() {
	///Look for physics handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("No physics handle attached to %s"), *GetOwner()->GetName());
	}

}

// Look for Input Component
void UGrabber::SetUpInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		///Bind the input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("No Input Component attached to %s"), *GetOwner()->GetName());
	}
}

// Return the physics body in reach 
FHitResult UGrabber::GetFirstPhysicsBodyInRerach() const
{
	//DrawDebugLine(GetWorld(),
	//	PlayerViewPointLocation,
	//	LineTraceEnd,
	//	FColor(255, 0, 0),
	//	false, 0, 0,
	//	12.333);

	/// setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Ray-cast out to reach distance  // Line Trace
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetLineTraceStart(),
		GetLineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	return (Hit);
}

// Return the end of grab reach
FVector UGrabber::GetLineTraceEnd() const
{
	APlayerController*  APlayer = GetWorld()->GetFirstPlayerController();
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	APlayer->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	return (PlayerViewPointLocation + PlayerViewPointRotation.Vector()*Reach);
}

// Returns the playerview point position
FVector UGrabber::GetLineTraceStart() const
{
	APlayerController*  APlayer = GetWorld()->GetFirstPlayerController();
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	APlayer->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	return (PlayerViewPointLocation);
}

// Release the component held
void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Grab key released"));
	// Release physics handle
	PhysicsHandle->ReleaseComponent();

}

// Try and reach any actors with physics body collision channel set
void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab key pressed"));

	/// get the player viewpoint
	auto Hit = GetFirstPhysicsBodyInRerach();
	auto ComponentToGrab = Hit.GetComponent();
	auto ActorHit = Hit.GetActor();
	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(ActorHit->GetName()));

		PhysicsHandle->GrabComponentAtLocationWithRotation(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			ComponentToGrab->GetOwner()->GetActorRotation()
		);
	}

	


}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (PhysicsHandle->GrabbedComponent) {
		PhysicsHandle->SetTargetLocation(GetLineTraceEnd());
	}
	
	/// if physics handle is attached
		/// Move the object we are holding

	
}

