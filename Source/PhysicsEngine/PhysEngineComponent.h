// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysEngineComponent.generated.h"

#define GRAVITY -9.8

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PHYSICSENGINE_API UPhysEngineComponent : public UActorComponent
{
	GENERATED_BODY()

    AActor* Parent;
    FVector PlayerPos;
    FBox BoundingBox;
    
    FBox MeshBBox;

    FVector Force;
    FVector Impulse;
    
    bool isFired;

    UStaticMeshComponent* Mesh;
    
public:	
	// Sets default values for this component's properties
	UPhysEngineComponent();

    void PostInitProperties();
    void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
    
    UPROPERTY(EditAnywhere, Category = Log)
    bool EnableLog;

    UPROPERTY(EditAnywhere, Category = Physics)
    bool EnableGravity;

    UPROPERTY(EditAnywhere, Category = Physics)
    FVector Gravity;

    UPROPERTY(EditAnywhere, Category = "Physics\|Material")
    float Mass;

    UPROPERTY(EditAnywhere, Category = "Physics")
    FVector Velocity;     // стартовая Скорость снаряда (зависит от типа орудия, из котор. стреляют)

    UPROPERTY(EditAnywhere, Category = "Physics")
    float AirResist;    // Сопротивление воздуха
    
    UPROPERTY(EditAnywhere, Category = "Physics")
    float Wind;         // Ветер
    
    UPROPERTY(EditAnywhere, Category = "Physics")
    float Sk;           // Sk - коэф. площади (на сколько ветер воздействует на объект)
    
    UFUNCTION()
    void UseGravity();

    UFUNCTION()
    void showLog(float DeltaTime);

    UFUNCTION()
    void CalculateValues();
};
