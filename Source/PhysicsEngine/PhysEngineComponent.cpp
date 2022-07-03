// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysEngineComponent.h"

// Sets default values for this component's properties
UPhysEngineComponent::UPhysEngineComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    EnableLog = true;
    EnableGravity = true;
    Gravity = FVector(0, 0, GRAVITY);
    Mass = 50;
    
    Parent = GetOwner();
    if (Parent != nullptr) {
        PlayerPos = Parent->GetActorLocation();
        BoundingBox = Parent->GetComponentsBoundingBox();
    }
}


// Called when the game starts
void UPhysEngineComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPhysEngineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    Force = FVector(0, 0, 0);
    
    if(isFired) {
        CalculateValues();
        Force += Impulse;
    }
    
    CalculateValues();
    UseGravity();
    
    float X = (((AirResist + Wind) * Sk) + Gravity.GetComponentForAxis(EAxis::X));// * DeltaTime;
    float Y = (((AirResist + Wind) * Sk) + Gravity.GetComponentForAxis(EAxis::Y));// * DeltaTime;
    float Z = (((AirResist + Wind) * Sk) + Gravity.GetComponentForAxis(EAxis::Z));// * DeltaTime;
    
    Force.Set(X, Y, Z);
//    Force += (Gravity + ((AirResist + Wind) * Sk));// * DeltaTime;
    
    PlayerPos = Parent->GetActorLocation();
    Parent->SetActorLocation(PlayerPos + Force);
    
    showLog(DeltaTime);
}


void UPhysEngineComponent::PostInitProperties()
{
    Super::PostInitProperties();

    CalculateValues();
}

void UPhysEngineComponent::CalculateValues() {
    float X = Mass * Velocity.GetComponentForAxis(EAxis::X);
    float Y = Mass * Velocity.GetComponentForAxis(EAxis::Y);
    float Z = Mass * Velocity.GetComponentForAxis(EAxis::Z);
    
    Impulse.Set(X, Y, Z);
}

#if WITH_EDITOR
void UPhysEngineComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    CalculateValues();

    Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

void UPhysEngineComponent::UseGravity() {
    if (!EnableGravity) {
        Gravity = FVector(0, 0, 0);
    }
}

void UPhysEngineComponent::showLog(float DeltaTime) {
    if(EnableLog && Parent) {
        PlayerPos = Parent->GetActorLocation();
        BoundingBox = Parent->GetComponentsBoundingBox();
        
//        GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Red, FString::Printf(TEXT("bbox: %s"), *BoundingBox.ToString()));
//        GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Red, FString::Printf(TEXT("bbox Volume: %f"), BoundingBox.GetVolume()));
        
        GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Red, FString::Printf(TEXT("Gravity: %s"), *Gravity.ToString()));
        GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Red, FString::Printf(TEXT("Impulse: %s"), *Impulse.ToString()));
        GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Red, FString::Printf(TEXT("Force: %s"), *Force.ToString()));
        
        GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Green, FString::Printf(TEXT("pos: %s"), *PlayerPos.ToString()));
    }
}

