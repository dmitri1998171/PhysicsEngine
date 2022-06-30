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
    Density = 1000;
    
    Parent = GetOwner();
    if (Parent != nullptr) {
        PlayerPos = Parent->GetActorLocation();
        BoundingBox = Parent->GetComponentsBoundingBox();
    }

    Mass = Density * BoundingBox.GetVolume();
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

	
    CalculateValues();

    UseGravity();
    showLog(DeltaTime);
}


void UPhysEngineComponent::PostInitProperties()
{
    Super::PostInitProperties();

    CalculateValues();
}

void UPhysEngineComponent::CalculateValues() {
    Mass = Density * BoundingBox.GetVolume();
}

#if WITH_EDITOR
void UPhysEngineComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    CalculateValues();

    Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

void UPhysEngineComponent::UseGravity() {
    if (EnableGravity) {
        PlayerPos = Parent->GetActorLocation();
        Parent->SetActorLocation(PlayerPos + Gravity);
    }
}

void UPhysEngineComponent::showLog(float DeltaTime) {
    if(EnableLog && Parent) {
        PlayerPos = Parent->GetActorLocation();
        BoundingBox = Parent->GetComponentsBoundingBox();

        GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Red, FString::Printf(TEXT("bbox: %s"), *BoundingBox.ToString()));
        GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Red, FString::Printf(TEXT("bbox Volume: %f"), BoundingBox.GetVolume()));
        GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Red, FString::Printf(TEXT("Mass: %f"), Mass));
        
        GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Green, FString::Printf(TEXT("pos: %s"), *PlayerPos.ToString()));
    }
}
