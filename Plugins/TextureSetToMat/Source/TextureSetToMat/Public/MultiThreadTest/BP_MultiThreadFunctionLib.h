// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BP_MultiThreadFunctionLib.generated.h"

/**
 * 
 */
UCLASS()
class TEXTURESETTOMAT_API UBP_MultiThreadFunctionLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable,Category="", meta = (DisplayName = "Calculate Prime Numbers"))
	static void CalculatePrimeNumbers(int32 UpperLimit);
	
	// UFUNCTION(BlueprintCallable,Category="", meta = (DisplayName = "Calculate Prime Numbers Asyn"))
	// static void CalculatePrimeNumbersAsyn(int32 UpperLimit);
	
	
};
