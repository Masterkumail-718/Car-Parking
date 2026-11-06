#include "ParkingHUD.h"
#include "ParkingUITheme.h"
#include "ParkingGameMode.h"
#include "ParkingSave.h"
#include "CiazPawn.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "Engine/Font.h"
#include "EngineFontServices.h"
#include "Fonts/FontMeasure.h"
#include "Fonts/SlateFontInfo.h"
#include "UObject/ConstructorHelpers.h"
#include "CanvasItem.h"
#include "GlobalRenderResources.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameFramework/PlayerController.h"
#include "InputCoreTypes.h"
using namespace ParkingUI;
AParkingHUD::AParkingHUD(){
 // Hold the runtime composite font on the CDO so all faces are cooking dependencies.
 static ConstructorHelpers::FObjectFinder<UFont> Font(TEXT("/Engine/EngineFonts/Roboto.Roboto"));
 MenuFont=Font.Object;
}
void AParkingHUD::UIShape(TArrayView<const FVector2D> Points,FLinearColor Color){
 if(Points.Num()<3||LayerAlpha<=0)return;
 Color.A*=LayerAlpha;
 FLinearColor Clear=Color;Clear.A=0;
 TArray<FVector2D,TInlineAllocator<64>> Inner,Outer;
 for(const FVector2D& P:Points)Inner.Emplace(OriginX+P.X*S,OriginY+(P.Y+LayerY)*S);
 if(UIAntialiasing){
  // Expand the convex clockwise outline by one physical pixel and fade its coverage.
  for(int I=0;I<Inner.Num();++I){
   const FVector2D Before=(Inner[I]-Inner[(I+Inner.Num()-1)%Inner.Num()]).GetSafeNormal();
   const FVector2D After=(Inner[(I+1)%Inner.Num()]-Inner[I]).GetSafeNormal();
   const FVector2D Normal(Before.Y+After.Y,-Before.X-After.X);
   Outer.Add(Inner[I]+Normal/FMath::Max(.5,1.+FVector2D::DotProduct(Before,After)));
  }
 }
 TArray<FCanvasUVTri> Triangles;
 Triangles.Reserve(Inner.Num()*(UIAntialiasing?3:1));
 const auto Add=[&](FVector2D A,FVector2D B,FVector2D C,FLinearColor CA,FLinearColor CB,FLinearColor CC){
  FCanvasUVTri T;
  T.V0_Pos=A;T.V1_Pos=B;T.V2_Pos=C;
  T.V0_UV=T.V1_UV=T.V2_UV=FVector2D::ZeroVector;
  T.V0_Color=CA;T.V1_Color=CB;T.V2_Color=CC;
  Triangles.Add(T);
 };
 for(int I=1;I+1<Inner.Num();++I)Add(Inner[0],Inner[I],Inner[I+1],Color,Color,Color);
 if(UIAntialiasing){
  for(int I=0;I<Inner.Num();++I){
   const int J=(I+1)%Inner.Num();
   Add(Inner[I],Outer[I],Outer[J],Color,Clear,Clear);
   Add(Inner[I],Outer[J],Inner[J],Color,Clear,Color);
  }
 }
 FCanvasTriangleItem Shape(Triangles,GWhiteTexture);
 Shape.BlendMode=SE_BLEND_Translucent;Canvas->DrawItem(Shape);
}
void AParkingHUD::MenuCard(float X,float Y,float W,float H,FLinearColor Color,float Radius){
 if(W<=0||H<=0)return;
 Radius=FMath::Clamp(Radius,0.f,FMath::Min(W,H)*.5f);
 TArray<FVector2D,TInlineAllocator<52>> Outline;
 for(int Corner=0;Corner<4;++Corner){
  const FVector2D Center(X+(Corner==0||Corner==3?Radius:W-Radius),Y+(Corner<2?Radius:H-Radius));
  for(int Segment=0;Segment<=12;++Segment){
   const float Angle=PI+(Corner+Segment/12.f)*PI*.5f;
   const FVector2D P=Center+Radius*FVector2D(FMath::Cos(Angle),FMath::Sin(Angle));
   if(Outline.IsEmpty()||!Outline.Last().Equals(P,.001))Outline.Add(P);
  }
 }
 if(Outline.Last().Equals(Outline[0],.001))Outline.Pop();
 UIShape(Outline,Color);
}
static FSlateFontInfo MenuFontInfo(UFont* Font,float PixelHeight,bool Bold){
 FSlateFontInfo Info(Font,16,Bold?FName(TEXT("Bold")):NAME_None);
 const auto Measure=FEngineFontServices::Get().GetFontMeasure();
 const float BaseHeight=Measure->Measure(TEXT("Ag"),Info).Y;
 Info.Size=FMath::Max(1,FMath::RoundToInt(16.f*PixelHeight/FMath::Max(1.f,BaseHeight)));
 return Info;
}
void AParkingHUD::MenuText(const FString& Label,float X,float Y,float Height,FLinearColor Color,bool Bold,bool Centered){
 UFont* Font=MenuFont?MenuFont.Get():GEngine->GetMediumFont();
 Color.A*=LayerAlpha;
 // Rasterize from the font outlines at the actual output size, never magnify a small atlas.
 // Integer physical positions keep antialiasing crisp as the menu scales or animates.
 FCanvasTextItem Item(FVector2D(FMath::RoundToFloat(OriginX+X*S),FMath::RoundToFloat(OriginY+(Y+LayerY)*S)),
  FText::FromString(Label),MenuFontInfo(Font,Height*S,Bold),Color);
 Item.bCentreX=Item.bCentreY=Centered;
 Canvas->DrawItem(Item);
}
void AParkingHUD::MenuImage(UTexture2D* Texture,float X,float Y,float W,float H){
 if(!Texture)return;
 DrawTexture(Texture,OriginX+X*S,OriginY+(Y+LayerY)*S,W*S,H*S,0,0,1,1,
  FLinearColor(1,1,1,LayerAlpha),BLEND_Translucent);
}
void AParkingHUD::MenuButton(const FString& Label,float X,float Y,float W,float H,int Action,bool IsPrimary,bool Enabled){
 const bool Hover=Enabled&&ScreenAge>=.32f&&MX>=X&&MX<=X+W&&MY>=Y+LayerY&&MY<=Y+LayerY+H;
 auto& Motion=HoverTweens.FindOrAdd(Action);
 Motion.To(Hover?1.f:0.f);Motion.Tick(FrameDelta);
 const FLinearColor Fill=FMath::Lerp(IsPrimary?Primary:Navy,IsPrimary?PrimaryHover:HoverFill,Motion.Value);
 const float Radius=H>=60?10.f:12.f;
 MenuCard(X,Y,W,H,FMath::Lerp(Rim,Accent,Motion.Value),Radius);
 MenuCard(X+1.25f,Y+1.25f,W-2.5f,H-2.5f,Fill,Radius-1.25f);
 const float LabelHeight=H>=60?25.f:18.f;
 UFont* Font=MenuFont?MenuFont.Get():GEngine->GetMediumFont();
 const float TextWidth=FEngineFontServices::Get().GetFontMeasure()->Measure(Label,MenuFontInfo(Font,LabelHeight*S,IsPrimary)).X/S;
 const float Inset=H>=60?26.f:16.f;
 const float FitHeight=LabelHeight*FMath::Min(1.f,(W-2*Inset)/FMath::Max(1.f,TextWidth));
 const FLinearColor LabelColor=Enabled?(Hover&&PointerDown?Muted:White):Disabled;
 if(W<=132.f)MenuText(Label,X+W*.5f,Y+H*.5f,FitHeight,LabelColor,IsPrimary,true);
 else MenuText(Label,X+Inset,Y+(H-FitHeight)*.5f,FitHeight,LabelColor,IsPrimary);
 if(Hover&&PointerPressed)Pending=Action;
}
void AParkingHUD::MenuSlider(float X,float Y,float W,float Fraction){
 const float Fill=W*FMath::Clamp(Fraction,0.f,1.f);
 MenuCard(X,Y-3,W,6,Track,3);
 MenuCard(X,Y-3,Fill,6,Accent,3);
 MenuCard(X+Fill-8,Y-8,16,16,Cyan,8);
}
void AParkingHUD::DrawMenuChrome(const AParkingGameMode& Game,bool CameraPreview){
 if(!MenuAssetsLoaded){
  MenuAssetsLoaded=true;
  MenuBackground=LoadObject<UTexture2D>(nullptr,TEXT("/Game/UI/T_MenuBackground.T_MenuBackground"));
  CiazPreview=LoadObject<UTexture2D>(nullptr,TEXT("/Game/UI/T_CiazPreview.T_CiazPreview"));
  SwiftPreview=LoadObject<UTexture2D>(nullptr,TEXT("/Game/UI/T_SwiftPreview.T_SwiftPreview"));
 }
 // Cover the physical viewport without stretching the background on ultrawide/4:3 screens.
 if(!CameraPreview)DrawRect(Navy,0,0,Canvas->SizeX,Canvas->SizeY);
 if(!CameraPreview&&MenuBackground){
  const float Aspect=float(Canvas->SizeX)/FMath::Max(1,Canvas->SizeY),ImageAspect=16.f/9.f;
  const float U=FMath::Min(1.f,Aspect/ImageAspect),V=FMath::Min(1.f,ImageAspect/Aspect);
  DrawTexture(MenuBackground,0,0,Canvas->SizeX,Canvas->SizeY,(1-U)*.5f,(1-V)*.5f,U,V,FLinearColor::White,BLEND_Opaque);
 }
 DrawRect(FLinearColor(.005,.012,.025,CameraPreview?.42f:Game.Screen==1?.24f:.60f),0,0,Canvas->SizeX,Canvas->SizeY);
 // Quiet header scrim keeps small text readable over the garage's overhead lamps.
 DrawRect(FLinearColor(0,0,0,.35f),0,0,Canvas->SizeX,OriginY+112*S);
 MenuText(TEXT("CIAZ"),60,32,40,White,true);
 const float TitleW=FEngineFontServices::Get().GetFontMeasure()->Measure(TEXT("CIAZ"),MenuFontInfo(MenuFont?MenuFont.Get():GEngine->GetMediumFont(),40*S,true)).X/S;
 MenuText(TEXT("PARKING"),60+TitleW+12,32,40,Accent,true);
 MenuText(Game.Save->VehicleIndex==1?TEXT("2022 SUZUKI SWIFT"):TEXT("2017 SUZUKI CIAZ"),60,82,16,Muted);
 MenuText(TEXT("PRECISION DRIVING"),994,49,15,Muted);
 Rect(60,105,1160,1,Rim);
 MenuText(TEXT("BETA 1.7.27"),1124,681,13,Muted);
}
void AParkingHUD::DrawMainMenu(const AParkingGameMode& Game){
 MenuButton(TEXT("Start / Continue"),62,158,342,71,1,true);
 MenuButton(TEXT("Level Select"),62,245,342,68,2);
 MenuButton(TEXT("Settings"),62,327,342,68,3);
 MenuButton(TEXT("Controls"),62,409,342,68,4);
 MenuButton(TEXT("Quit"),62,491,342,68,5);
 HUDPanel(438,138,782,496,15);
 MenuText(TEXT("Your vehicle"),474,154,19,Muted);
 MenuText(Game.Save->VehicleIndex==1?TEXT("Suzuki Swift"):TEXT("Suzuki Ciaz"),474,184,32,White,true);
 // Compact outlined vehicle switch; action remains deferred until after HUD drawing.
 const bool ChangeHover=ScreenAge>=.32f&&MX>=1078&&MX<=1192&&MY>=172+LayerY&&MY<=210+LayerY;
 MenuCard(1078,172,114,38,Accent,11);
 MenuCard(1079,173,112,36,ChangeHover?HoverFill:Navy,10);
 MenuText(TEXT("Change"),1100,182,19,Accent);
 if(ChangeHover&&PointerPressed)Pending=30;
 Rect(470,235,722,1,FLinearColor(.38,.45,.50,.45));
 UTexture2D* Preview=Game.Save->VehicleIndex==1?SwiftPreview.Get():CiazPreview.Get();
 if(Preview){
  const float W=680,H=FMath::Min(236.f,W*Preview->GetSizeY()/FMath::Max(1,Preview->GetSizeX()));
  const float DrawW=H*Preview->GetSizeX()/FMath::Max(1,Preview->GetSizeY());
  MenuImage(Preview,830-DrawW*.5f,244+(236-H)*.5f,DrawW,H);
 }else MenuText(TEXT("Vehicle preview unavailable"),660,355,18,Muted);
 Rect(470,478,722,1,FLinearColor(.38,.45,.50,.45));
 constexpr float SliderX=478,SliderWidth=706,SliderY=543;
 constexpr int32 MaxHeight=ACiazPawn::MaxRideHeightOffsetCm;
 if(ScreenAge>=.32f&&MX>=SliderX-12&&MX<=SliderX+SliderWidth+12&&MY>=SliderY-16+LayerY&&MY<=SliderY+16+LayerY&&PointerPressed){
  HeightDraft=FMath::RoundToInt(MaxHeight*FMath::Clamp((MX-SliderX)/SliderWidth,0.f,1.f));HeightDragging=true;
 }
 if(HeightDragging){
  if(PointerDown){if(MX!=-1.f)HeightDraft=FMath::RoundToInt(MaxHeight*FMath::Clamp((MX-SliderX)/SliderWidth,0.f,1.f));}
  else{Pending=AParkingGameMode::HeightActionBase+HeightDraft;HeightDragging=false;}
 }
 const float Height=HeightDragging?float(HeightDraft):Game.Save->RideHeightOffsetCm;
 MenuText(TEXT("Ride height"),474,499,20,White);
 MenuText(FString::Printf(TEXT("+%.1f cm"),Height),1100,499,20,White);
 MenuSlider(SliderX,SliderY,SliderWidth,Height/MaxHeight);
 MenuText(TEXT("0 cm"),474,563,15,Muted);MenuText(TEXT("+8 cm"),1140,563,15,Muted);
 MenuText(TEXT("Transmission can be changed in Settings"),474,599,17,Muted);
}
void AParkingHUD::Rect(float X,float Y,float W,float H,FLinearColor C){
 C.A*=LayerAlpha;DrawRect(C,OriginX+X*S,OriginY+(Y+LayerY)*S,W*S,H*S);
}
void AParkingHUD::Text(const FString& Label,float X,float Y,float Size,FLinearColor Color){
 MenuText(Label,X,Y,16.f*Size,Color,Size>=1.6f);
}
void AParkingHUD::Button(const FString& Label,float X,float Y,float W,int Action,bool Enabled){
 const bool IsPrimary=Action==6||Action==7||Action==9||Action==530||Action==531;
 MenuButton(Label,X,Y,W,40,Action,IsPrimary,Enabled);
}
#if PLATFORM_ANDROID
void AParkingHUD::DrawTouchControls(const AParkingGameMode& Game){
 using namespace ParkingTouch;
 const auto& Car=*Game.Car;
 const bool WheelMode=Game.Save->AndroidSteeringWheel;
 const FLinearColor Edge(FColor(104,139,174,220)), Glass(FColor(19,33,51,175));
 const auto Surface=[&](const Area& Bounds,float Radius,bool Active){
  MenuCard(Bounds.X,Bounds.Y,Bounds.W,Bounds.H,(Active?Cyan:Edge).CopyWithNewOpacity(.55f),Radius);
  // Keep the outline translucent too, so the scene remains visible through the controls.
  const FLinearColor Fill=Active?FLinearColor(FColor(34,76,106,225)):Glass;
  MenuCard(Bounds.X+1.5,Bounds.Y+1.5,Bounds.W-3,Bounds.H-3,Fill,Radius-1.5f);
 };
 const auto Line=[this](FVector2D A,FVector2D B,FLinearColor Color,float Thickness){
  Color.A*=LayerAlpha;
  DrawLine(OriginX+A.X*S,OriginY+(A.Y+LayerY)*S,OriginX+B.X*S,OriginY+(B.Y+LayerY)*S,Color,Thickness*S);
 };
 const auto Arc=[&](FVector2D Centre,float Radius,float Start,float Sweep,FLinearColor Color,float Thickness){
  constexpr int Steps=48;
  for(int I=0;I<Steps;++I){
   const auto Point=[&](int Index){
    const float A=Start+Sweep*Index/Steps;
    return Centre+FVector2D(FMath::Cos(A),FMath::Sin(A))*Radius;
   };
   Line(Point(I),Point(I+1),Color,Thickness);
  }
 };

 HUDPanel(GearSelector.X,GearSelector.Y,GearSelector.W,GearSelector.H,GearSelector.H*.5);
 for(const auto& B:Buttons){
  if(B.Role==Control::Clutch&&Car.Drive.mode!=Parking::Mode::Clutch)continue;
  if(WheelMode&&(B.Role==Control::Left||B.Role==Control::Right))continue;
  const Area& R=B.Bounds;
  const float X=R.X+R.W*.5,Y=R.Y+R.H*.5;
  const bool Pressed=Game.TouchInput.Down(B.Role);
  const bool IsGear=B.Role==Control::Drive||B.Role==Control::Neutral||B.Role==Control::Reverse;
  if(IsGear){
   const bool Selected=(B.Role==Control::Drive&&Car.Drive.gear>0)||
    (B.Role==Control::Neutral&&Car.Drive.gear==0)||(B.Role==Control::Reverse&&Car.Drive.gear<0);
   if(Selected||Pressed)MenuCard(R.X+2,R.Y,R.W-4,R.H,Selected?Green:Cyan,R.H*.5);
   MenuText(ANSI_TO_TCHAR(B.Label),X,Y,27,Selected||Pressed?Navy:White,true,true);
   continue;
  }
  if(B.Role==Control::Pause||B.Role==Control::Camera){
   HUDPanel(R.X,R.Y,R.W,R.H,16);
   if(B.Role==Control::Pause){
    MenuCard(X-9,Y-12,6,24,White,2);
    MenuCard(X+3,Y-12,6,24,White,2);
   }else{
    MenuCard(X-6,Y-14,12,6,White,2);
    MenuCard(X-15,Y-10,30,23,White,4);
    MenuCard(X-12,Y-7,24,17,Navy,2);
    Arc({X,Y+1},5,0,2*PI,White,2);
   }
   continue;
  }
  Surface(R,B.Role==Control::Handbrake?40.f:28.f,Pressed);
  if(B.Role==Control::Handbrake){
   const FLinearColor Color=Car.Handbrake?Warning:White;
   Arc({X,Y},17,0,2*PI,Color,2.5f);
   Arc({X,Y},21,-.85f,1.7f,Color,2);
   Arc({X,Y},21,PI-.85f,1.7f,Color,2);
   MenuText(TEXT("P"),X,Y,27,Color,true,true);
  }else{
   MenuText(ANSI_TO_TCHAR(B.Label),X,Y,26,Pressed?Cyan:White,true,true);
  }
 }
 if(!WheelMode)return;
 const FVector2D Centre(WheelCentre.X,WheelCentre.Y);
 // Draw a single translucent disk with a clean rim instead of stacking two filled disks.
 MenuCard(Centre.X-WheelRadius,Centre.Y-WheelRadius,2*WheelRadius,2*WheelRadius,Glass,WheelRadius);
 Arc(Centre,WheelRadius,0,2*PI,Edge,1.5f);
 const FLinearColor WheelColor=Game.TouchInput.Down(Control::Wheel)?Cyan:FLinearColor(FColor(172,187,208,205));
 const float Angle=Car.Steering.angle*WheelTravel;
 constexpr float RimRadius=95;
 Arc(Centre,RimRadius,0,2*PI,WheelColor,6);
 for(const float Offset:{-.18f,PI+.18f,PI*.5f}){
  const float A=Angle+Offset;
  const FVector2D Direction(FMath::Cos(A),FMath::Sin(A)),Side(-Direction.Y,Direction.X);
  const FVector2D Spoke[]={Centre+Direction*26-Side*15,Centre+Direction*RimRadius-Side*8,
   Centre+Direction*RimRadius+Side*8,Centre+Direction*26+Side*15};
  UIShape(Spoke,WheelColor);
 }
 MenuCard(Centre.X-36,Centre.Y-36,72,72,WheelColor,36);
 MenuCard(Centre.X-33,Centre.Y-33,66,66,Navy,33);
 MenuText(TEXT("S"),Centre.X,Centre.Y,31,White,true,true);
}
#endif
void AParkingHUD::DrawHUD(){
 Super::DrawHUD();if(!Canvas||!PlayerOwner)return;
 auto* G=Cast<AParkingGameMode>(GetWorld()->GetAuthGameMode());if(!G||!G->Car||!G->Save)return;
 S=FMath::Min(Canvas->SizeX/1280.f,Canvas->SizeY/720.f);if(S<=0)return;
 OriginX=(Canvas->SizeX-1280.f*S)*.5f;OriginY=(Canvas->SizeY-720.f*S)*.5f;
 FrameDelta=FMath::Clamp(GetWorld()->GetDeltaSeconds(),0.f,.1f);
 if(LastScreen!=G->Screen){LastScreen=G->Screen;ScreenAge=0;HoverTweens.Empty();FOVDragging=false;HeightDragging=false;}
 ScreenAge+=FrameDelta;
 const float Reveal=ParkingUI::Ease(ScreenAge/.32f);
 LayerAlpha=Reveal;LayerY=12.f*(1.f-Reveal);
#if PLATFORM_ANDROID
 const auto Pointer=G->TouchInput.MenuPosition();MX=Pointer.X;MY=Pointer.Y;
 PointerDown=G->TouchInput.Down(ParkingTouch::Control::Menu);
 PointerPressed=G->TouchInput.Pressed(ParkingTouch::Control::Menu);
#else
 float X,Y;if(PlayerOwner->GetMousePosition(X,Y)){MX=(X-OriginX)/S;MY=(Y-OriginY)/S;}else MX=MY=-1;
 PointerDown=PlayerOwner->IsInputKeyDown(EKeys::LeftMouseButton);
 PointerPressed=PlayerOwner->WasInputKeyJustPressed(EKeys::LeftMouseButton);
#endif
 if(G->Screen!=8)FOVDragging=false;
 Pending=-1;
 UIAntialiasing=G->IsUIAntialiasingEnabled();
 if(G->Screen==0)DrawDrivingHUD(*G);
 if(G->Screen!=0){
  LayerAlpha=1;LayerY=0;
  DrawMenuChrome(*G,G->Screen==10);
  LayerAlpha=Reveal;LayerY=12.f*(1.f-Reveal);
  if(G->Screen==2||G->Screen==4||G->Screen==5||G->Screen==6){
   HUDPanel(48,144,550,460,18);
   HUDPanel(650,144,570,460,18);
  }
  if(G->Screen==3)HUDPanel(48,125,1172,516,18);
  if(G->Screen==7)HUDPanel(48,122,1172,548,18);
  if(G->Screen==8)HUDPanel(48,119,1172,562,18);
  if(G->Screen==9){
   HUDPanel(48,115,382,528,18);
   HUDPanel(438,115,782,528,18);
  }
  switch(G->Screen){
  case 1:DrawMainMenu(*G);break;
  case 2:
   Text(TEXT("TAKE A BREATHER"),740,224,1.6f,White);
   Text(TEXT("Your current attempt is waiting."),740,275,1.15f,Muted);
   Text(TEXT("Resume when you are ready."),740,310,1.15f,Muted);
   Text(TEXT("PAUSED"),68,160,2.5f,White);
   Button(TEXT("RESUME"),68,230,350,6);Button(TEXT("RETRY LEVEL"),68,280,350,7);
   Button(TEXT("SETTINGS"),68,330,350,3);Button(TEXT("CONTROLS"),68,380,350,4);
   Button(TEXT("MAIN MENU"),68,430,350,8);break;
  case 3:
   Text(TEXT("SELECT A LEVEL"),68,140,1.8f,White);
   for(int i=0;i<G->Levels.Num();i++){
    int Col=i%2,Row=i/2;
    Button(FString::Printf(TEXT("%02d  %s%s"),i+1,*G->Levels[i].Name,i>=G->Save->Unlocked?TEXT("  [LOCKED]"):TEXT("")),
     68+Col*570,190+Row*65,530,100+i,i<G->Save->Unlocked);
   }Button(TEXT("MAIN MENU"),68,190+((G->Levels.Num()+1)/2)*65,260,8);break;
  case 4:
   Text(TEXT("SETTINGS"),68,155,2.2f,White);
   Button(TEXT("GRAPHICS"),68,240,450,12);
   Button(PLATFORM_ANDROID?TEXT("TOUCH CONTROLS"):TEXT("CONTROLS / WHEEL"),68,300,450,13);
   Button(FString::Printf(TEXT("MASTER VOLUME: %.0f%%"),G->Save->MasterVolume*100),68,360,450,26);
   Button(TEXT("INTERIOR CAMERA"),68,420,450,800);
   Button(TEXT("BACK"),68,470,300,10);
   Text(TEXT("Make it feel right."),680,246,2.f,White);
   Text(TEXT("Display and visual quality in Graphics."),680,304,1.1f,Muted);
   Text(PLATFORM_ANDROID?TEXT("Steering buttons or a touch wheel in Controls."):TEXT("Wheel, pedals and key bindings in Controls."),680,345,1.1f,Muted);
   break;
  case 10:{
   const auto* Save=G->Save.Get();
   HUDPanel(48,119,350,48,14);
   Text(TEXT("INTERIOR CAMERA"),68,130,1.8f,White);
   const TCHAR* Labels[]={TEXT("FORWARD / BACK"),TEXT("RIGHT / LEFT"),TEXT("UP / DOWN"),TEXT("LOOK UP / DOWN"),TEXT("LOOK RIGHT / LEFT"),TEXT("FIELD OF VIEW")};
   const double Values[]={Save->InteriorCameraOffset.X,Save->InteriorCameraOffset.Y,Save->InteriorCameraOffset.Z,
    Save->InteriorCameraRotation.Pitch,Save->InteriorCameraRotation.Yaw,Save->InteriorFOV};
   const TCHAR* Minus[]={TEXT("BACK"),TEXT("LEFT"),TEXT("DOWN"),TEXT("DOWN"),TEXT("LEFT"),TEXT("NARROWER")};
   const TCHAR* Plus[]={TEXT("FORWARD"),TEXT("RIGHT"),TEXT("UP"),TEXT("UP"),TEXT("RIGHT"),TEXT("WIDER")};
   for(int32 Row=0;Row<6;++Row){
    const float RowY=180.f+65.f*Row;
    HUDPanel(48,RowY-4,330,48,12);
    HUDPanel(732,RowY-4,488,48,12);
    Text(Labels[Row],68,RowY+10,1.1f,White);
    Text(FString::Printf(TEXT("%+.0f %s"),Values[Row],Row<3?TEXT("cm"):TEXT("deg")),752,RowY+10,1.1f,Cyan);
    Button(Minus[Row],900,RowY,110,810+Row*2);
    Button(Plus[Row],1030,RowY,110,811+Row*2);
   }
   HUDPanel(48,558,1172,113,16);
   Text(TEXT("Click a direction to adjust and save. Movement is relative to the vehicle; mouse look stays available."),68,570,.9f,Muted);
   Text(TEXT("Values are offsets from the default view, except field of view. Resume driving to use mouse look."),68,592,.9f,Muted);
   Button(TEXT("BACK TO SETTINGS"),68,620,300,823);
   Button(TEXT("RESET CAMERA"),900,620,240,822);
  }break;
  case 8:{
   auto* Save=G->Save.Get();
   const bool Editable=!G->GraphicsConfirm;
   Text(TEXT("GRAPHICS"),68,130,1.8f,White);
   const TCHAR* Presets[]={TEXT("LOW"),TEXT("MEDIUM"),TEXT("HIGH"),TEXT("EPIC")};
   for(int i=0;i<4;++i)Button(Presets[i],640+i*142,124,132,540+i,Editable);
   for(int i=0;i<AParkingGameMode::GraphicsSettingCount;++i){
    const int Col=i/8,Row=i%8;
    Button(G->GraphicsLabel(i),68+Col*575,174+Row*44,545,500+i,Editable);
   }
   Text(TEXT("Click an option to cycle. Borderless uses your desktop resolution."),68,536,.95f,Muted);
   Text(FString::Printf(TEXT("INTERIOR FOV: %.0f deg"),Save->InteriorFOV),68,559,1.f,White);
   const bool SliderHover=!G->GraphicsConfirm && ScreenAge>=.32f && MX>=68 && MX<=408 && MY>=580+LayerY && MY<=605+LayerY;
   if(SliderHover && PointerPressed)FOVDragging=true;
   float DisplayFOV=Save->InteriorFOV;
   if(FOVDragging){
    if(PointerDown){
     DisplayFOV=ACiazPawn::MinInteriorFOV+(ACiazPawn::MaxInteriorFOV-ACiazPawn::MinInteriorFOV)*FMath::Clamp((MX-68.f)/340.f,0.f,1.f);
     Pending=AParkingGameMode::FOVActionBase+FMath::RoundToInt(DisplayFOV-ACiazPawn::MinInteriorFOV);
    }else{FOVDragging=false;Pending=480;}
   }
   const float FOVFraction=(DisplayFOV-ACiazPawn::MinInteriorFOV)/(ACiazPawn::MaxInteriorFOV-ACiazPawn::MinInteriorFOV);
   MenuSlider(68,592,340,FOVFraction);

   Text(TEXT("Interior FOV: 70-150 degrees. Saves immediately."),450,589,.85f,Muted);
   if(G->GraphicsConfirm){
    HUDPanel(656,550,548,120,16);
    const int Seconds=FMath::Max(0,FMath::CeilToInt(float(G->GraphicsDeadline-FPlatformTime::Seconds())));
    Text(FString::Printf(TEXT("Keep these settings? Reverting in %d s"),Seconds),680,570,1.15f,Cyan);
    Button(TEXT("KEEP CHANGES"),680,620,250,531);
    Button(TEXT("REVERT"),950,620,250,532);
   }else{
    Button(TEXT("BACK"),68,630,240,11);
    Button(TEXT("DISCARD CHANGES"),680,630,250,533);
    Button(TEXT("APPLY"),950,630,250,530,G->GraphicsDraft!=Save->Graphics);
   }
  }break;
  case 9:{
   auto* Save=G->Save.Get();
#if PLATFORM_ANDROID
   Text(TEXT("TOUCH CONTROLS"),68,125,1.7f,White);
   Button(Save->AndroidSteeringWheel?TEXT("STEERING BUTTONS"):TEXT("STEERING BUTTONS  [SELECTED]"),68,185,340,AParkingGameMode::TouchButtonsAction);
   Button(Save->AndroidSteeringWheel?TEXT("TOUCH WHEEL  [SELECTED]"):TEXT("TOUCH WHEEL"),68,245,340,AParkingGameMode::TouchWheelAction);
   Button(Save->Transmission==static_cast<int>(Parking::Mode::Clutch)?TEXT("MANUAL CLUTCH"):TEXT("AUTOMATIC"),68,305,340,21);
   Button(TEXT("BACK TO SETTINGS"),68,580,340,11);
   Text(TEXT("Steer on the left. Hold the pedals on the right."),470,190,1.25f,Cyan);
   Text(TEXT("Select D, N or R with the gear buttons."),470,245,1.1f,Muted);
   Text(TEXT("Tap the handbrake to engage or release it."),470,284,1.1f,Muted);
   Text(TEXT("Drag anywhere off the controls to look around."),470,323,1.1f,Muted);
   Text(TEXT("In manual, hold the clutch to select D or R."),470,362,1.1f,Muted);
#else
   Text(TEXT("CONTROLS / WHEEL"),68,125,1.7f,White);
   Button(FString(TEXT("INPUT: "))+ (Save->WheelEnabled?TEXT("T248"):TEXT("KEYBOARD")),68,165,340,20);
   const TCHAR* ModeNames[]={TEXT("AUTOMATIC"),TEXT("SEQUENTIAL"),TEXT("MANUAL CLUTCH")};
   Button(ModeNames[Save->Transmission],68,215,340,21);
   Button(TEXT("KEYBOARD BINDINGS"),68,265,340,14);
   Button(Save->HandbrakeHold?TEXT("HANDBRAKE: HOLD"):TEXT("HANDBRAKE: TOGGLE"),68,315,340,29);
   Text(Save->HandbrakeHold?TEXT("Hold the assigned key; release to disengage."):TEXT("Press once to engage; again to release."),68,530,.85f,Muted);
   Button(Save->Feedback?TEXT("FORCE FEEDBACK: ON"):TEXT("FORCE FEEDBACK: OFF"),68,365,340,24);
   Button(Save->FeedbackInvert?TEXT("FFB DIRECTION: INVERTED"):TEXT("FFB DIRECTION: NORMAL"),68,415,340,25);
   Button(G->Calibrating?TEXT("FINISH CALIBRATION"):TEXT("START CALIBRATION"),68,465,340,23);
   Button(TEXT("BACK TO SETTINGS"),68,580,340,11);
   Text(G->Wheel.IsConnected()?G->Wheel.Name:TEXT("T248 not connected"),450,126,1.1f,Cyan);
   const TCHAR* Labels[]={TEXT("Steering"),TEXT("Accelerator"),TEXT("Brake"),TEXT("Clutch")};
   const TCHAR* AxisLabels[]={TEXT("X"),TEXT("Y"),TEXT("Z"),TEXT("Rx"),TEXT("Ry"),TEXT("Rz"),TEXT("Slider 1"),TEXT("Slider 2")};
   for(int i=0;i<4;i++){
    const int Axis=Save->Axes[i];
    Button(FString::Printf(TEXT("%s: %s (Axis %d)"),Labels[i],AxisLabels[Axis],Axis),450,165+i*48,270,200+i);
    Button(Save->Invert[i]?TEXT("INVERTED"):TEXT("NORMAL"),735,165+i*48,160,210+i);
   }
   Button(FString::Printf(TEXT("SHIFT UP: BUTTON %d"),Save->ShiftUp),450,365,270,27);
   Button(FString::Printf(TEXT("SHIFT DOWN: BUTTON %d"),Save->ShiftDown),735,365,270,28);
   Text(TEXT("Live readings for assigned controls"),450,425,1.05f,Muted);
   for(int i=0;i<4;i++){
    const float MeterX=450+i*184;
    Text(Labels[i],MeterX,452,1,White);
    MenuCard(MeterX,478,160,9,Track,4.5f);
    MenuCard(MeterX,478,160*FMath::Clamp(G->Wheel.Axes[Save->Axes[i]],0.f,1.f),9,Accent,4.5f);
   }
   Text(Save->Calibrated?TEXT("Calibration saved"):TEXT("Calibration required before wheel driving"),450,510,1.1f,Cyan);
   Text(TEXT("Only assigned axes need travel. Unused axes are ignored."),450,548,1,Muted);
   Text(TEXT("Before Finish: centre the wheel and release every pedal."),450,573,1,Muted);
   Text(G->Wheel.HasForceFeedback()?TEXT("Force-feedback interface detected"):TEXT("Force-feedback interface not available"),450,605,1,Muted);
#endif
  }break;
  case 5:
   Text(TEXT("SPACE FOUND"),740,224,1.8f,Cyan);
   Text(G->Levels.IsValidIndex(G->Level+1)?TEXT("A careful finish. On to the next course."):TEXT("All courses complete."),740,280,1.1f,Muted);
   Text(TEXT("PARKED."),68,170,4.f,Cyan);
   Text(FString::Printf(TEXT("%s  /  %d collisions"),*G->Levels[G->Level].Name,G->Rules.collisions),68,250,1.5,White);
   Button(G->Levels.IsValidIndex(G->Level+1)?TEXT("NEXT LEVEL"):TEXT("REPLAY FINAL LEVEL"),68,325,350,9);
   Button(TEXT("LEVEL SELECT"),68,375,350,2);Button(TEXT("MAIN MENU"),68,425,350,8);break;
  case 6:
   Text(TEXT("ANOTHER APPROACH"),740,224,1.7f,White);
   Text(TEXT("Use the mirrors. Watch the sensors."),740,280,1.1f,Muted);
   Text(TEXT("THREE IMPACTS."),68,170,3.2f,Warning);
   Text(TEXT("Reset, slow down, and try another approach."),68,245,1.4f,Muted);
   Button(TEXT("RETRY"),68,325,350,7);Button(TEXT("LEVEL SELECT"),68,375,350,2);Button(TEXT("MAIN MENU"),68,425,350,8);break;
  case 7:{
   Text(TEXT("CONTROLS  /  CLICK A ROW TO REBIND"),68,135,1.6f,White);
   const TCHAR* Labels[]={TEXT("Accelerator"),TEXT("Brake only"),TEXT("Steer left"),TEXT("Steer right"),TEXT("Centre steering"),
    TEXT("Parking brake"),TEXT("Drive / Gear 1"),TEXT("Neutral"),TEXT("Reverse"),TEXT("Shift down"),TEXT("Shift up"),
    TEXT("Clutch"),TEXT("Restart engine"),TEXT("Transmission"),TEXT("Camera"),TEXT("Look back"),TEXT("Headlights"),
    TEXT("Gear 2"),TEXT("Gear 3"),TEXT("Gear 4"),TEXT("Gear 5")};
   const FKey Keys[]={EKeys::W,EKeys::S,EKeys::A,EKeys::D,EKeys::X,EKeys::SpaceBar,EKeys::One,EKeys::N,EKeys::R,EKeys::Q,EKeys::E,EKeys::LeftShift,EKeys::I,EKeys::T,EKeys::C,EKeys::V,EKeys::L,EKeys::Two,EKeys::Three,EKeys::Four,EKeys::Five};
   for(int i=0;i<21;i++){
    int Col=i/7,Row=i%7;
    Button(FString::Printf(TEXT("%s: %s"),Labels[i],*G->BoundKey(Keys[i]).GetDisplayName().ToString()),68+Col*385,185+Row*49,365,300+i);
   }
   Text(TEXT("KEYBOARD STEERING SENSITIVITY"),68,551,1.1f,Cyan);
   for(int32 Level=1;Level<=5;++Level){
    const bool Selected=G->Save->KeyboardSteeringSensitivity==Level;
    MenuButton(FString::FromInt(Level),385+(Level-1)*76,539,64,40,
     AParkingGameMode::SteeringSensitivityActionBase+Level,Selected);
   }
   Text(TEXT("1 Slow  /  5 Fast"),775,552,1.05f,Muted);
   Text(TEXT("MOUSE LOOK SENSITIVITY"),68,597,1.1f,Cyan);
   for(int32 Level=1;Level<=5;++Level){
    const bool Selected=G->Save->MouseSensitivity==Level;
    MenuButton(FString::FromInt(Level),385+(Level-1)*76,585,64,40,
     AParkingGameMode::MouseSensitivityActionBase+Level,Selected);
   }
   Text(TEXT("1 Slow  /  3 Default  /  5 Fast"),775,598,1.05f,Muted);
   Text(TEXT("Steering holds at rest and centres while moving. Mouse look adjusts both cameras."),68,625,.85f,Muted);
   Text(TEXT("ESC Pause  /  F5 Retry  /  F4 Settings  /  F1 Key bindings."),390,652,1.05f,Muted);
   Button(TEXT("BACK TO CONTROLS"),68,638,300,13);
  }break;
  }
 }
#if PLATFORM_ANDROID
 else DrawTouchControls(*G);
#endif
 LayerAlpha=1;LayerY=0;
 // The level hint belongs to driving; keep the intro clear while still showing errors/notices.
 const bool IntroHint=G->Screen==1&&G->Levels.IsValidIndex(G->Level)&&G->Notice==G->Levels[G->Level].Hint;
 if(G->NoticeTime>0&&!IntroHint){
  if(LastNotice!=G->Notice){LastNotice=G->Notice;NoticeAge=0;}
  NoticeAge+=FrameDelta;
  const float Toast=ParkingUI::Ease(NoticeAge/.25f)*ParkingUI::Ease(G->NoticeTime/.25f);
  LayerAlpha=Toast;LayerY=8*(1-Toast);
  // Size the pill to the message and keep it between the goal and sensor widgets.
  const float LabelHeight=18;
  UFont* Font=MenuFont?MenuFont.Get():GEngine->GetMediumFont();
  const auto Measure=FEngineFontServices::Get().GetFontMeasure();
  const float TextWidth=Measure->Measure(G->Notice,MenuFontInfo(Font,LabelHeight*S,true)).X/S;
  const float Width=FMath::Clamp(TextWidth+36.f,136.f,800.f);
  const float FitHeight=LabelHeight*FMath::Min(1.f,(Width-36.f)/FMath::Max(1.f,TextWidth));
  HUDPanel(640-Width*.5f,114,Width,36,18);
  const FLinearColor LabelColor=G->Notice.StartsWith(TEXT("Collision "))?Warning:White;
  MenuText(G->Notice,640,132,FitHeight,LabelColor,true,true);
 }else{LastNotice.Empty();NoticeAge=0;}
 LayerAlpha=1;LayerY=0;
 // Never resize the viewport or mutate the level from inside HUD rendering.
 if(Pending>=0){
  const int Action=Pending,ExpectedScreen=G->Screen;
  GetWorld()->GetTimerManager().SetTimerForNextTick(
   FTimerDelegate::CreateWeakLambda(G,[G,Action,ExpectedScreen](){if(G->Screen==ExpectedScreen)G->HandleAction(Action);}));
  Pending=-1;
 }
}
