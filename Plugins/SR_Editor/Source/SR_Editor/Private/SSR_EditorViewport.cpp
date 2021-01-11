// Fill out your copyright notice in the Description page of Project Settings.


#include "SSR_EditorViewport.h"

#include "AdvancedPreviewScene.h"
#include "SlateOptMacros.h"
#include "SR_EditorViewportClient.h"
#include "SR_LineTraceActor.h"
#include "Components/DirectionalLightComponent.h"

#include "Components/SkyLightComponent.h"
#include "Atmosphere/AtmosphericFogComponent.h"
#include "Engine/StaticMeshActor.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSR_EditorViewport::Construct(const FArguments& InArgs)
{
	CustomAsset = InArgs._CustomAsset.Get();
	{
		FAdvancedPreviewScene::ConstructionValues ViewConstructionValues;
		ViewConstructionValues.bCreatePhysicsScene = false;
		ViewConstructionValues.LightBrightness = 3;
		ViewConstructionValues.SkyBrightness = 1;

		PreviewScene = MakeShareable(new FAdvancedPreviewScene(ViewConstructionValues));
		PreviewScene->SetFloorVisibility(false);
		PreviewScene->SetFloorOffset(-100000);
	}
    
	USkyLightComponent* Skylight = NewObject<USkyLightComponent>();
	PreviewScene->AddComponent(Skylight, FTransform::Identity);
	
	UAtmosphericFogComponent *AtmosphericFog = NewObject<UAtmosphericFogComponent>();
	PreviewScene->AddComponent(AtmosphericFog, FTransform::Identity);
    
	PreviewScene->DirectionalLight->SetMobility(EComponentMobility::Movable);
	PreviewScene->DirectionalLight->CastShadows = true;
	PreviewScene->DirectionalLight->CastStaticShadows = true;
	PreviewScene->DirectionalLight->CastDynamicShadows = true;
	PreviewScene->DirectionalLight->SetIntensity(3);
	SEditorViewport::Construct(SEditorViewport::FArguments());
    
	PreviewMeshComponent = NewObject<UStaticMeshComponent>(GetTransientPackage(), NAME_None, RF_Transient );
    
	SetPreviewMesh(CustomAsset);
}

SSR_EditorViewport::~SSR_EditorViewport()
{
}

TSharedRef<FEditorViewportClient> SSR_EditorViewport::MakeEditorViewportClient()
{
	EditorViewportClient = MakeShareable(new FSR_EditorViewportClient(*PreviewScene, CustomAsset));
	return EditorViewportClient.ToSharedRef();
}

void SSR_EditorViewport::SetPreviewMesh(UStaticMesh* InStaticMesh) const
{
	FComponentReregisterContext RegisterContext( PreviewMeshComponent );
	PreviewMeshComponent->SetStaticMesh(InStaticMesh);
	const FTransform Transform = FTransform::Identity;
	PreviewScene->AddComponent( PreviewMeshComponent, Transform );
	EditorViewportClient->SetPreviewMesh(InStaticMesh, PreviewMeshComponent);
}

void SSR_EditorViewport::SpawnDefaultActors()
{
	
	AActor* MeshActor=GetWorld()->SpawnActor<AActor>(AStaticMeshActor::StaticClass(),FTransform(FRotator(0),FVector(1000,0,0),FVector(1)));
	

	GetWorld()->SpawnActor<ASR_LineTraceActor>();

	
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
