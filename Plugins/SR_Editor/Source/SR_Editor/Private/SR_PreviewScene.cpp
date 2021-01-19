#include "SR_PreviewScene.h"

FSR_PreviewScene::FSR_PreviewScene(ConstructionValues CVS)
{
}

FSR_PreviewScene::~FSR_PreviewScene()
{
}

void FSR_PreviewScene::AddComponent(UActorComponent* Component, const FTransform& LocalToWorld, bool bAttachToRoot)
{
}

void FSR_PreviewScene::RemoveComponent(UActorComponent* Component)
{
}

void FSR_PreviewScene::AddReferencedObjects(FReferenceCollector& Collector)
{
}

FString FSR_PreviewScene::GetReferencerName() const
{
}

ULineBatchComponent* FSR_PreviewScene::GetLineBatcher() const
{
	return LineBatcher;
}

void FSR_PreviewScene::ClearLineBatcher()
{
}

void FSR_PreviewScene::UpdateCaptureContents()
{
}

FRotator FSR_PreviewScene::GetLightDirection()
{
}

void FSR_PreviewScene::SetLightDirection(const FRotator& InLightDir)
{
}

void FSR_PreviewScene::SetLightBrightness(float LightBrightness)
{
}

void FSR_PreviewScene::SetLightColor(const FColor& LightColor)
{
}

void FSR_PreviewScene::SetSkyBrightness(float SkyBrightness)
{
}

void FSR_PreviewScene::SetSkyCubemap(UTextureCube* Cubemap)
{
}

FLinearColor FSR_PreviewScene::GetBackgroundColor() const
{
}

void FSR_PreviewScene::LoadSettings(const TCHAR* Section)
{
}

void FSR_PreviewScene::SaveSettings(const TCHAR* Section)
{
}
