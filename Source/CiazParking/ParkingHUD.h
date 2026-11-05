#pragma once
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UIAnimation.h"
#include "ParkingHUD.generated.h"
class AParkingGameMode;
class UTexture2D;
class UFont;
UCLASS()
class CIAZPARKING_API AParkingHUD : public AHUD {
 GENERATED_BODY()
public:
 AParkingHUD();
 virtual void DrawHUD() override;
private:
 float S=1,MX=-1,MY=-1,OriginX=0,OriginY=0;
 float LayerAlpha=1,LayerY=0,ScreenAge=0,FrameDelta=0;
 int LastScreen=-1;
 bool PointerDown=false,PointerPressed=false;
 TMap<int,ParkingUI::Tween> HoverTweens;
 FString LastNotice;
 float NoticeAge=0;
 void DrawGoalArrow(const AParkingGameMode& Game);
 void DrawDrivingHUD(const AParkingGameMode& Game);
 void HUDSprite(float U,float V,float UW,float VH,float X,float Y,float W,float H,float Rotation=0);
 void HUDPanel(float X,float Y,float W,float H,float Radius);
 void UIShape(TArrayView<const FVector2D> Points,FLinearColor Color);
 bool UIAntialiasing=true;
 UPROPERTY() TObjectPtr<UTexture2D> DrivingArt;
 bool DrivingArtLoaded=false;
 void DrawMainMenu(const AParkingGameMode& Game);
 void DrawMenuChrome(const AParkingGameMode& Game,bool CameraPreview);
 void MenuButton(const FString& Label,float X,float Y,float W,float H,int Action,bool Primary=false,bool Enabled=true);
 void MenuSlider(float X,float Y,float W,float Fraction);
 void MenuText(const FString& Label,float X,float Y,float Height,FLinearColor Color,bool Bold=false,bool Centered=false);
 void MenuImage(UTexture2D* Texture,float X,float Y,float W,float H);
 void MenuCard(float X,float Y,float W,float H,FLinearColor Color,float Radius=10.f);
 UPROPERTY() TObjectPtr<UFont> MenuFont;
 bool MenuAssetsLoaded=false;
 UPROPERTY() TObjectPtr<UTexture2D> MenuBackground;
 UPROPERTY() TObjectPtr<UTexture2D> CiazPreview;
 UPROPERTY() TObjectPtr<UTexture2D> SwiftPreview;

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
