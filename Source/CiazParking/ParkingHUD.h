#pragma once
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UIAnimation.h"
#include "ParkingHUD.generated.h"
class AParkingGameMode;
UCLASS()
class CIAZPARKING_API AParkingHUD : public AHUD {
 GENERATED_BODY()
public:
 virtual void DrawHUD() override;
private:
 float S=1,MX=-1,MY=-1,OriginX=0,OriginY=0;
 float LayerAlpha=1,LayerY=0,ScreenAge=0,FrameDelta=0;
 int LastScreen=-1;
 bool PointerDown=false,PointerPressed=false;
 TMap<int,ParkingUI::Tween> HoverTweens;
 FString LastNotice;
 float NoticeAge=0;
 void Card(float X,float Y,float W,float H,FLinearColor C);
 void DrawGoalArrow(const AParkingGameMode& Game);

 int Pending=-1;
 bool FOVDragging=false;
 bool HeightDragging=false;
 int32 HeightDraft=0;
 void Rect(float X,float Y,float W,float H,FLinearColor C);
 void Text(const FString& T,float X,float Y,float Size,FLinearColor C);
 void Button(const FString& T,float X,float Y,float W,int Action,bool Enabled=true);
#if PLATFORM_ANDROID
 void DrawTouchControls(const AParkingGameMode& Game);
#endif
};
