// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Containers/LruCache.h"
#include "GameFramework/Actor.h"
#include "CacheActor.generated.h"

UCLASS()
class TEXTURESETTOMAT_API ACacheActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACacheActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

//	UPROPERTY()
	TLruCache<FString,FString> TokenCache;

	UFUNCTION(BlueprintCallable,Category="TokenActor")
	void InitTokenTocache();

	UFUNCTION(BlueprintCallable,Category="TokenActor")
	void SetTokenTocache(FString TokenValue);

	UFUNCTION(BlueprintCallable,Category="TokenActor")
	FString ReadToken(FString KeyStr);
};
