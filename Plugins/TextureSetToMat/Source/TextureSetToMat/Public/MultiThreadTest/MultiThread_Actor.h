// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MultiThread_Actor.generated.h"

UCLASS()
class TEXTURESETTOMAT_API AMultiThread_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMultiThread_Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	/* Calculates prime numbers in the game thread */
	UFUNCTION(BlueprintCallable, Category = MultiThreading)
    void CalculatePrimeNumbers(int32 UpperLimit);

	/* Calculates prime numbers in a background thread */
	UFUNCTION(BlueprintCallable, Category = MultiThreading)
    void CalculatePrimeNumbersAsync();

	/* The max prime number */
	UPROPERTY(EditAnywhere, Category = MultiThreading)
	int32 MaxPrime=50000;
};
