#include "SR_EditorViewportClient.h"

#include "AssetEditorModeManager.h"
#include "CanvasItem.h"
#include "CanvasTypes.h"
#include "MouseDeltaTracker.h"
#include "Engine/Canvas.h"
#include "Engine/StaticMeshSocket.h"
#include "Framework/Application/SlateApplication.h"
#include "Engine/Public/SceneView.h"
#include "UnrealEd/Public/UnrealWidget.h"
#include "UnrealEd/Public/EditorModeManager.h"
#include "EditorViewportClient.h"
#include "Editor.h"
#include "ProceduralMeshComponent.h"

#include "InputCoreTypes.h"

#include "Engine/Selection.h"
#include "SEditorViewport.h"

#include "PreviewScene.h"
#include "EngineUtils.h"
#include "AudioDevice.h"
#include "Math/Axis.h"
#include "Engine/EngineBaseTypes.h"
#include "Editor/UnrealEdTypes.h"
#include "UnrealClient.h"
#include "SceneManagement.h"
#include "EditorComponents.h"
#include "Engine/EngineTypes.h"
#include "HitProxies.h"
#include "AdvancedPreviewScene/Public/AdvancedPreviewScene.h"
#include "Components/PostProcessComponent.h"
#include "Engine/StaticMesh.h"


/**
* A hit proxy class for sockets.
*/
struct IR_HSMESocketProxy : public HHitProxy
{
	DECLARE_HIT_PROXY( );

	int32		SocketIndex;

	IR_HSMESocketProxy(int32 InSocketIndex) :
        HHitProxy( HPP_UI ), 
        SocketIndex( InSocketIndex ) {}
};
IMPLEMENT_HIT_PROXY(IR_HSMESocketProxy, HHitProxy);


FSR_EditorViewportClient::FSR_EditorViewportClient(FPreviewScene& InPreviewScene, UStaticMesh* InCustomAsset,
	const TWeakPtr<SEditorViewport>& InEditorViewportWidget): FEditorViewportClient(nullptr, &InPreviewScene, InEditorViewportWidget)
,StaticMesh(InCustomAsset)
{
	AdvancedPreviewScene = static_cast<FAdvancedPreviewScene*>(PreviewScene);

	DrawHelper.bDrawGrid = true;
	DrawHelper.bDrawPivot = true;
	SetRealtime(true);
	FEditorViewportClient::SetViewMode(VMI_Lit);
	SetViewLocation(FVector(500, 300, 500));
	SetViewRotation(FRotator(-40,-150,0));
	// CreateMeshLOD();
	
}



bool FSR_EditorViewportClient::InputKey(FViewport* TheViewport, int32 ControllerId, FKey Key, EInputEvent Event,
    float AmountDepressed, bool bGamepad)
{
	bool bHandled = FEditorViewportClient::InputKey(TheViewport, ControllerId, Key, Event, AmountDepressed, false);

	// Handle viewport screenshot.
	bHandled |= InputTakeScreenshot( TheViewport, Key, Event );

	bHandled |= AdvancedPreviewScene->HandleInputKey(TheViewport, ControllerId, Key, Event, AmountDepressed, bGamepad);

	return bHandled;
	
}

void FSR_EditorViewportClient::Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI)
{
	FEditorViewportClient::Draw(View, PDI);

	if (StaticMesh)
	{
		if (bShowSockets)
		{
			const FColor SocketColor = FColor(255, 128, 128);
    
			for (int32 i = 0; i < StaticMesh->Sockets.Num(); i++)
			{
				UStaticMeshSocket* Socket = StaticMesh->Sockets[i];
				if (Socket)
				{
					// FMatrix SocketTM;
					// Socket->GetSocketMatrix(SocketTM, StaticMeshComponent);
                    
					FMatrix SocketTM = FScaleRotationTranslationMatrix(StaticMesh->Sockets[i]->RelativeScale, StaticMesh->Sockets[i]->RelativeRotation, StaticMesh->Sockets[i]->RelativeLocation) * StaticMeshComponent->GetComponentTransform().
                        ToMatrixWithScale();
    
					PDI->SetHitProxy( new IR_HSMESocketProxy(i) );
					DrawWireDiamond(PDI, SocketTM, 5.f, SocketColor, SDPG_Foreground);
					PDI->SetHitProxy(nullptr);
				}
			}
		}
	}
}

void FSR_EditorViewportClient::DrawCanvas(FViewport& InViewport, FSceneView& View, FCanvas& Canvas)
{
	//绘制槽点名称！
        FEditorViewportClient::DrawCanvas(InViewport, View, Canvas);
        if (!StaticMesh)
        {
            return;
        }
        const int32 HalfX = Viewport->GetSizeXY().X / 2;
        const int32 HalfY = Viewport->GetSizeXY().Y / 2;
    
        if (bShowSockets)
        {
            for (int32 i = 0; i < StaticMesh->Sockets.Num(); i++)
            {
                UStaticMeshSocket* Socket = StaticMesh->Sockets[i];
                if (Socket != nullptr)
                {
                    FMatrix SocketTM;
                    // Socket->GetSocketTransform(SocketTM, StaticMeshComponent);
                    // const FVector SocketPos	= SocketTM.GetOrigin();
                    const FVector SocketPos = Socket->RelativeLocation;
                    const FPlane Proj = View.Project(SocketPos);
                    if (Proj.W > 0.f)
                    {
                        const int32 XPos = HalfX + (HalfX * Proj.X);
                        const int32 YPos = HalfY + (HalfY * (Proj.Y * -1));
    
                        FCanvasTextItem TextItem(FVector2D(XPos, YPos), FText::FromString(Socket->SocketName.ToString()),
                                                 GEngine->GetSmallFont(), FLinearColor(FColor(255, 196, 196)));
                        Canvas.DrawItem(TextItem);
    
                        const UStaticMeshSocket* SelectedSocket = StaticMesh->Sockets[i];
                        if (bManipulating && SelectedSocket == Socket)
                        {
                            //Figure out the text height
                            FTextSizingParameters Parameters(GEngine->GetSmallFont(), 1.0f, 1.0f);
                            UCanvas::CanvasStringSize(Parameters, *Socket->SocketName.ToString());
                            int32 YL = FMath::TruncToInt(Parameters.DrawYL);
    
                            DrawAngles(&Canvas, XPos, YPos + YL,Widget->GetCurrentAxis(),GetWidgetMode(),Socket->RelativeRotation,Socket->RelativeLocation);
                        }
                    }
                }
            }
        }
}

void FSR_EditorViewportClient::UpdateMouseDelta()
{
	FEditorViewportClient::UpdateMouseDelta();
}

void FSR_EditorViewportClient::DrawAngles(FCanvas* Canvas, int32 XPos, int32 YPos, EAxisList::Type ManipAxis,
	FWidget::EWidgetMode MoveMode, const FRotator& Rotation, const FVector& Translation)
{
	FString OutputString(TEXT(""));
	if (MoveMode == FWidget::WM_Rotate && Rotation.IsZero() == false)
	{
		//同时只有一个值在变化
		const FVector EulerAngles = Rotation.Euler();
		if (ManipAxis == EAxisList::X)
		{
			OutputString += FString::Printf(TEXT("Roll: %0.2f"), EulerAngles.X);
		}
		else if (ManipAxis == EAxisList::Y)
		{
			OutputString += FString::Printf(TEXT("Pitch: %0.2f"), EulerAngles.Y);
		}
		else if (ManipAxis == EAxisList::Z)
		{
			OutputString += FString::Printf(TEXT("Yaw: %0.2f"), EulerAngles.Z);
		}
	}
	else if (MoveMode == FWidget::WM_Translate && Translation.IsZero() == false)
	{
		//Only one value moves at a time
		if (ManipAxis == EAxisList::X)
		{
			OutputString += FString::Printf(TEXT(" %0.2f"), Translation.X);
		}
		else if (ManipAxis == EAxisList::Y)
		{
			OutputString += FString::Printf(TEXT(" %0.2f"), Translation.Y);
		}
		else if (ManipAxis == EAxisList::Z)
		{
			OutputString += FString::Printf(TEXT(" %0.2f"), Translation.Z);
		}
	}

	if (OutputString.Len() > 0)
	{
		FCanvasTextItem TextItem(FVector2D(XPos, YPos), FText::FromString(OutputString), GEngine->GetSmallFont(),FLinearColor::White);
		Canvas->DrawItem(TextItem);
	}
}


void FSR_EditorViewportClient::ProcessClick(FSceneView& View, HHitProxy* HitProxy, FKey Key, EInputEvent Event, uint32 HitX, uint32 HitY)
{
	if (!StaticMesh)
	{
		return;
	}

	const bool bCtrlDown = Viewport->KeyState(EKeys::LeftControl) || Viewport->KeyState(EKeys::RightControl);

	bool ClearSelectedSockets=true;
	bool ClearSelectedPrims = true;
	bool ClearSelectedEdges = true;

	if( HitProxy )
	{
		if(HitProxy->IsA( IR_HSMESocketProxy::StaticGetType() ) )
		{
			IR_HSMESocketProxy* SocketProxy = static_cast<IR_HSMESocketProxy*>(HitProxy);

			UStaticMeshSocket* Socket = nullptr;

			if(SocketProxy->SocketIndex < StaticMesh->Sockets.Num())
			{
				Socket = StaticMesh->Sockets[SocketProxy->SocketIndex];
			}

			// if(Socket)
			// {
			// 	StaticMeshEditorPtr.Pin()->SetSelectedSocket(Socket);
			// }

			ClearSelectedSockets = false;
		}
	}
}
void FSR_EditorViewportClient::Tick(float DeltaSeconds)
{
	FEditorViewportClient::Tick(DeltaSeconds);
	//更新鼠标
	FViewportCameraTransform& ViewTransform = GetViewTransform();
	const bool bIsAnimating = ViewTransform.UpdateTransition();
	
	if (bIsAnimating && GetViewportType() == LVT_Perspective)
	{
		PerspectiveCameraMoved();
	}
	
	if ( bIsTracking )
	{
		FEditorViewportStats::BeginFrame();
	}
	
	if( !bIsAnimating )
	{
		bIsCameraMovingOnTick = bIsCameraMoving;
	
		// Update any real-time camera movement
		// UpdateCameraMovement( DeltaSeconds );
	
		UpdateMouseDelta();
		
		UpdateGestureDelta();
		//
		EndCameraMovement();
	}

	//显示模型？！！！
	// FComponentReregisterContext ReregisterContext( StaticMeshComponent );
	// StaticMeshComponent->SetStaticMesh(CustomAsset);
	// StaticMeshComponent->MarkRenderStateDirty();
   
	PreviewScene->GetWorld()->Tick(LEVELTICK_All, DeltaSeconds);
}

void FSR_EditorViewportClient::ChangeShowState(bool bShowFistSection)
{
	if (ProceduralMesh.Num() > 0 && bShowFistSection)
	{
		ProceduralMesh[0]->SetMeshSectionVisible(0, bShowFistSection);
	}
}

void FSR_EditorViewportClient::SetPreviewMesh(UStaticMesh* InStaticMesh, UStaticMeshComponent* InStaticMeshComponent)
{
	StaticMesh = InStaticMesh;
	StaticMeshComponent = InStaticMeshComponent;

	if(StaticMeshComponent != nullptr)
	{
		StaticMeshComponent->MarkRenderStateDirty();
	}
}























