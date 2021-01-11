// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SR_LineTraceCom.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "SR_LineTraceActor.generated.h"

UCLASS()
class SR_EDITOR_API ASR_LineTraceActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASR_LineTraceActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = mesh)
	USR_LineTraceCom* LineTraceCom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = mesh)
	USceneComponent* DefaultScen;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = mesh)
	USplineComponent* SplineCom;

	
	
};
