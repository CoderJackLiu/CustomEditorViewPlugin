#pragma once
#include "EditorViewportClient.h"
#include "UnrealEd/Public/SEditorViewport.h"
#include "Engine/Public/PreviewScene.h"
#include "InputCoreTypes.h"


/*
 * 
 */


class FViewport;
class FAdvancedPreviewScene;
class UProceduralMeshComponent;
class FSR_EditorViewportClient:public FEditorViewportClient, public TSharedFromThis<FSR_EditorViewportClient>
{
public:

	/*构造函数*/
	FSR_EditorViewportClient(FPreviewScene& InPreviewScene, UStaticMesh* InCustomAsset, const TWeakPtr<class SEditorViewport> &InEditorViewportWidget = nullptr);

	/*检测用户输入按键*/
	virtual bool InputKey(FViewport* TheViewport, int32 ControllerId, FKey Key, EInputEvent Event, float AmountDepressed = 1.f, bool bGamepad=false) override;
	
	/*绘制视口*/
	virtual void Draw(const FSceneView* View,FPrimitiveDrawInterface* PDI) override;
	
	/*绘制视口中的UI*/
	virtual void DrawCanvas( FViewport& InViewport, FSceneView& View, FCanvas& Canvas ) override;

	/*检测鼠标事件*/
	virtual void UpdateMouseDelta() override;
	
	/*绘制angle*/
	static void DrawAngles(FCanvas* Canvas, int32 XPos, int32 YPos, EAxisList::Type ManipAxis, FWidget::EWidgetMode MoveMode, const FRotator& Rotation, const FVector& Translation);

	/*用户点击视口中的物体触发*/
	virtual void ProcessClick(class FSceneView& View, class HHitProxy* HitProxy, FKey Key, EInputEvent Event, uint32 HitX, uint32 HitY) override;

	/*tick事件，绘制视口每帧执行*/
	virtual void Tick(float DeltaSeconds) override;

	/*改变显示状态：即隔离显示*/
	void ChangeShowState(bool bShowFistSection);

	/*设置显示的模型的Section*/
	void SetPreviewMesh(UStaticMesh* InStaticMesh, UStaticMeshComponent* InStaticMeshComponent);

private:

	/*DEPRECATED:procedualMesh组件*/
	TArray<UProceduralMeshComponent*> ProceduralMesh;
	
	/*是否显示槽点*/
	bool bShowSockets=true;
	
	/** true when the user is manipulating a socket widget. */
	bool bManipulating;

	/** Component for the static mesh. */
	UStaticMeshComponent* StaticMeshComponent;

	/** The static mesh being used in the editor. */
	UStaticMesh* StaticMesh;

	/*camera 移动触发的函数，目前没有必要的逻辑需要修改*/
	virtual void BeginCameraMovement(bool bHasMovement) override {}
	virtual void EndCameraMovement() override {}
	
	/** Stored pointer to the preview scene in which the static mesh is shown */
	FAdvancedPreviewScene* AdvancedPreviewScene;
	
};
