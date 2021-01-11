// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SEditorViewport.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SR_EDITOR_API SSR_EditorViewport : public SEditorViewport
{
public:
	SLATE_BEGIN_ARGS(SSR_EditorViewport)
	{
	}
	SLATE_ATTRIBUTE(class UStaticMesh*, CustomAsset)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	//析构函数！
	~SSR_EditorViewport();

	//创建视口实例
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;
	
	FORCEINLINE TSharedPtr<class FSR_EditorViewportClient> &GetCustomAssetViewportClient() {return EditorViewportClient;}

	/** Component for the preview static mesh. */
	UStaticMeshComponent* PreviewMeshComponent;

	//设置预览模型
	void SetPreviewMesh(UStaticMesh* InStaticMesh) const;


	private:
	class UStaticMesh* CustomAsset = nullptr;

	//预览视口
	TSharedPtr<class FAdvancedPreviewScene> PreviewScene;
	//预览视口Client
	TSharedPtr<class FSR_EditorViewportClient> EditorViewportClient;

	void SpawnDefaultActors();

	
};
