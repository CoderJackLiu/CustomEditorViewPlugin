// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SR_LineTraceCom.generated.h"


UCLASS( Blueprintable,BlueprintType,ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SR_EDITOR_API USR_LineTraceCom : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USR_LineTraceCom();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable,/*BlueprintImplementableEvent,*/BlueprintNativeEvent, Category = "Lidar Point Cloud", meta = (Keywords = "raycast",DisplayName = "SendLineTrace"))
	void SendLineTrace();
};
