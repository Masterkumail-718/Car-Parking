#include "ParkingHUD.h"
#include "ParkingUITheme.h"
#include "ParkingGameMode.h"
#include "ParkingSave.h"
#include "CiazPawn.h"
#include "Engine/Texture2D.h"
#include "Engine/Font.h"
#include "GameFramework/PlayerController.h"

using namespace ParkingUI;

void AParkingHUD::HUDPanel(float X,float Y,float W,float H,float Radius){
 MenuCard(X,Y,W,H,Rim,Radius);
 MenuCard(X+1.5f,Y+1.5f,W-3,H-3,Navy,Radius-1.5f);
}

void AParkingHUD::HUDSprite(float U,float V,float UW,float VH,float X,float Y,float W,float H,float Rotation){
 if(!DrivingArt)return;
 // Source rectangles use the pixel coordinates of the supplied transparent reference.
 constexpr float AtlasW=1671,AtlasH=941;
 DrawTexture(DrivingArt,OriginX+X*S,OriginY+(Y+LayerY)*S,W*S,H*S,
  U/AtlasW,V/AtlasH,UW/AtlasW,VH/AtlasH,FLinearColor(1,1,1,LayerAlpha),BLEND_Translucent,
  1.f,false,Rotation,FVector2D(.5,.5));
}

void AParkingHUD::DrawGoalArrow(const AParkingGameMode& Game){
 if(!Game.Levels.IsValidIndex(Game.Level))return;
 const auto& Level=Game.Levels[Game.Level];
 FVector ToGoal=Level.Target-Game.Car->GetActorLocation();ToGoal.Z=0;
 if(ToGoal.SizeSquared2D()<1.f)ToGoal=FRotator(0,Level.TargetYaw,0).Vector();
 FVector ViewLocation;FRotator ViewRotation;
 PlayerOwner->GetPlayerViewPoint(ViewLocation,ViewRotation);
 const float Angle=FMath::RadiansToDegrees(FMath::Atan2(ToGoal.Y,ToGoal.X))-ViewRotation.Yaw;
 if(DrivingArt){
  // The reference sprite already points 78 degrees counter-clockwise from straight up.
  HUDSprite(782,12,125,75,602,PLATFORM_ANDROID?31.f:17.f,76,45.6f,Angle+78.f);
 }else{
  // Retain navigation if the optional artwork is absent from a source-only checkout.
  const float Rad=FMath::DegreesToRadians(Angle),Sin=FMath::Sin(Rad),Cos=FMath::Cos(Rad);
  const FVector2D ArrowOutline[]={{0,-28},{18,-7},{7,-7},{7,24},{-7,24},{-7,-7},{-18,-7}};
  const auto Rotate=[&](FVector2D P){return FVector2D(640+P.X*Cos-P.Y*Sin,(PLATFORM_ANDROID?54:40)+P.X*Sin+P.Y*Cos);};
  const FVector2D Tip[]={Rotate(ArrowOutline[0]),Rotate(ArrowOutline[1]),Rotate(ArrowOutline[6])};
  const FVector2D Stem[]={Rotate(ArrowOutline[5]),Rotate(ArrowOutline[2]),Rotate(ArrowOutline[3]),Rotate(ArrowOutline[4])};
  UIShape(Tip,Cyan);UIShape(Stem,Cyan);
 }
 if(!PLATFORM_ANDROID){
  HUDPanel(592,75,96,29,14.5f);
  MenuText(TEXT("GOAL"),619,80,20,White,true);
 }
}

void AParkingHUD::DrawDrivingHUD(const AParkingGameMode& Game){
 if(!DrivingArtLoaded){
  DrivingArtLoaded=true;
  DrivingArt=LoadObject<UTexture2D>(nullptr,TEXT("/Game/UI/T_DrivingHUD.T_DrivingHUD"));
 }
 const auto& Car=*Game.Car;
 const float SavedAlpha=LayerAlpha,SavedY=LayerY;
 LayerAlpha=1;LayerY=0;DrawGoalArrow(Game);LayerAlpha=SavedAlpha;LayerY=SavedY;

 if(PLATFORM_ANDROID){
  HUDPanel(32,32,256,54,27);
  HUDSprite(44,37,36,47,46,43,24,32);
 }else{
  HUDPanel(19,19,264,55,27.5f);
  HUDSprite(44,37,36,47,34,30,27.5f,36);
 }
 if(Game.Levels.IsValidIndex(Game.Level)){
  FString Name=Game.Levels[Game.Level].Name;
  if(Name==TEXT("Full house"))Name=TEXT("Full House");
  const FString Label=FString::Printf(TEXT("%02d / %s"),Game.Level+1,*Name);
  float Width=0,Height=0;GetTextSize(Label,Width,Height,MenuFont.Get());
  const float LabelHeight=FMath::Min(23.f,192.f*Height/FMath::Max(Width,1.f));
  if(PLATFORM_ANDROID)MenuText(Label,84,59-LabelHeight*.5f,LabelHeight,White,true);
  else MenuText(Label,77,27+(23-LabelHeight)*.5f,LabelHeight,White,true);
 }
 if(!PLATFORM_ANDROID)MenuText(TEXT("Fit the outline. Face the arrow."),77,50,16,White);

 if(PLATFORM_ANDROID){
  HUDPanel(930,32,173,54,27);
  MenuText(TEXT("Collisions"),947,47,23,White,true);
  MenuText(FString::FromInt(Game.Rules.collisions),1047,59,36,White,true,true);
  MenuText(TEXT("/ 3"),1075,59,27,Red,true,true);
 }else{
  HUDPanel(1070,19,195,54,27);
  HUDSprite(1416,42,40,37,1084,32,30.5f,28);
  MenuText(TEXT("Collisions"),1118,36,20,White,true);
  MenuText(FString::FromInt(Game.Rules.collisions),1204,28,36,White,true);
  MenuText(TEXT("/3"),1227,37,27,Red,true);
 }

 constexpr float SensorDX=PLATFORM_ANDROID?24.f:0.f,SensorDY=PLATFORM_ANDROID?-9.f:0.f;
 HUDPanel(1111+SensorDX,120+SensorDY,128,157,PLATFORM_ANDROID?23.f:15.f);
 // The car crop excludes the reference's example sensor colours. All bands below use live distances.
 const auto CarSprite=[this](float U,float V,float W,float H){
  constexpr float ScaleX=61.f/80,ScaleY=98.f/128;
  HUDSprite(U,V,W,H,1144+SensorDX+(U-1495)*ScaleX,149+SensorDY+(V-195)*ScaleY,W*ScaleX,H*ScaleY);
 };
 CarSprite(1513,198,43,5);
 CarSprite(1495,203,80,120);
 const auto Band=[this](float Angle,float Span,float Inner,float Outer,FLinearColor Color){
  const auto Point=[](float Degrees,float Radius){
   const float A=FMath::DegreesToRadians(Degrees);
   return FVector2D(1175+SensorDX+FMath::Cos(A)*Radius,198+SensorDY+FMath::Sin(A)*Radius);
  };
  const float A=Angle-Span*.5f,B=Angle+Span*.5f;
  const FVector2D Points[]={Point(A,Inner),Point(A,Outer),Point(B,Outer),Point(B,Inner)};
  UIShape(Points,Color);
 };
 // The car has three front and three rear sensors. Side marks stay neutral.
 for(int I=0;I<4;++I){
  Band(-24.f+16.f*I,13,39,54,Track);
  Band(156.f+16.f*I,13,39,54,Track);
 }
 for(int I=0;I<6;++I){
  const float Distance=Car.Sensors[I];
  const FLinearColor Color=Distance>=250?Track:Distance<35?Red:
   Distance<90?FLinearColor(FColor(255,183,45)):FLinearColor(FColor(34,237,54));
  const float Angle=I<3?-110.f+20.f*I:110.f-20.f*(I-3);
  Band(Angle,17,50,57,Color);
  Band(Angle,17,59,66,Color);
 }

 const FString Speed=FString::Printf(TEXT("%.0f"),FMath::Abs(Car.Speed)*3.6f);
 const FString Gear=Car.Drive.gear<0?TEXT("R"):Car.Drive.gear==0?TEXT("N"):
  Car.Drive.mode==Parking::Mode::Automatic?TEXT("D"):FString::FromInt(Car.Drive.gear);
 const FLinearColor GearColor=Car.Drive.gear<0?Red:Green;
#if PLATFORM_ANDROID
 HUDPanel(32,330,246,57,28.5f);
 if(Car.Handbrake){
  if(DrivingArt)HUDSprite(50,811,89,70,53,341,38,30);
  else MenuText(TEXT("(P)"),72,358.5f,25,Red,true,true);
 }
 Rect(109,340,1,37,Rim);
 Rect(213,340,1,37,Rim);
 MenuText(Speed,136,358.5f,Speed.Len()>2?28.f:37.f,White,true,true);
 MenuText(TEXT("km/h"),161,351,19,White,true);
 MenuText(Gear,243,358.5f,37,GearColor,true,true);
#else
 constexpr float SpeedY=604.f;
 HUDPanel(19,SpeedY,264,85,42.5f);
 if(Car.Handbrake){
  if(DrivingArt)HUDSprite(50,811,89,70,39,SpeedY+16,68,53.5f);
  else MenuText(TEXT("(P)"),43,SpeedY+21,40,Red,true);
 }
 MenuText(Speed,151-11.f*Speed.Len(),SpeedY+5,50,White,true);
 MenuText(TEXT("km/h"),132,SpeedY+53,20,White,true);
 constexpr float GearX=214,GearSize=45;
 const float GearY=SpeedY+20;
 MenuCard(GearX,GearY,GearSize,GearSize,GearColor,5);
 MenuCard(GearX+1.5f,GearY+1.5f,GearSize-3,GearSize-3,Navy,3.5f);
 MenuText(Gear,GearX+GearSize*.5f,GearY+GearSize*.5f,41,GearColor,true,true);

 constexpr float SteeringY=655.f;
 HUDPanel(430,SteeringY,428,46,23);
 HUDSprite(582,865,44,45,446,SteeringY+5,34,35);
 MenuText(TEXT("Steering"),489,SteeringY+13,18,White,true);
 MenuText(TEXT("L"),563,SteeringY+13,18,White,true);
 MenuText(TEXT("R"),831,SteeringY+13,18,White,true);
 constexpr float TrackX=580,TrackWidth=241;
 const float Progress=FMath::Clamp((float(Car.Steering.angle)+1.f)*.5f,0.f,1.f);
 MenuCard(TrackX,SteeringY+19,TrackWidth,8,Track,4);
 MenuCard(TrackX,SteeringY+19,TrackWidth*Progress,8,FLinearColor(FColor(13,174,234)),4);
 MenuCard(TrackX+TrackWidth*Progress-8.5f,SteeringY+14.5f,17,17,Cyan,8.5f);
#endif

 if(Game.Rules.held>0){
  constexpr float HoldY=PLATFORM_ANDROID?645.f:621.f;
  HUDPanel(497,HoldY,286,25,12.5f);
  MenuCard(499,HoldY+2,282*FMath::Clamp(float(Game.Rules.held/2),0.f,1.f),21,
   FLinearColor(FColor(0,91,124)),10.5f);
  MenuText(TEXT("HOLD STILL"),599,HoldY+4,17,White,true);
 }
 if(!Car.Drive.running){
  HUDPanel(380,158,520,38,19);
  if(PLATFORM_ANDROID)MenuText(TEXT("ENGINE STALLED / TAP N TO RESTART"),640,177,20,Red,true,true);
  else MenuText(TEXT("ENGINE STALLED / CLUTCH + I TO RESTART"),412,167,20,Red,true);
 }
}
