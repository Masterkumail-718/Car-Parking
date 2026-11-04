#include "ParkingHUD.h"
#include "ParkingGameMode.h"
#include "ParkingSave.h"
#include "CiazPawn.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameFramework/PlayerController.h"
#include "InputCoreTypes.h"
static const FLinearColor Ink(.018,.027,.039,.94),Panel(.045,.061,.078,.98),Muted(.52,.61,.66,1),Mint(.35,.88,.75,1);
void AParkingHUD::Rect(float X,float Y,float W,float H,FLinearColor C){
 C.A*=LayerAlpha;DrawRect(C,OriginX+X*S,OriginY+(Y+LayerY)*S,W*S,H*S);
}
void AParkingHUD::Text(const FString& T,float X,float Y,float Size,FLinearColor C){
 C.A*=LayerAlpha;DrawText(T,C,OriginX+X*S,OriginY+(Y+LayerY)*S,GEngine->GetSmallFont(),Size*S,false);
}
void AParkingHUD::Card(float X,float Y,float W,float H,FLinearColor C){
 // Small stepped corners remain crisp at the minimum 720p target.
 Rect(X+4,Y,W-8,H,C);Rect(X,Y+4,4,H-8,C);Rect(X+W-4,Y+4,4,H-8,C);
}
void AParkingHUD::Button(const FString& T,float X,float Y,float W,int Action,bool Enabled){
 const bool Hover=Enabled&&ScreenAge>=.32f&&MX>=X&&MX<=X+W&&MY>=Y+LayerY&&MY<=Y+LayerY+40;
 auto& Motion=HoverTweens.FindOrAdd(Action);Motion.To(Hover?1.f:0.f);Motion.Tick(FrameDelta);
 const float H=Motion.Value;
 const bool Pressed=Hover&&PlayerOwner->IsInputKeyDown(EKeys::LeftMouseButton);
 const FLinearColor Fill=FMath::Lerp(Panel,FLinearColor(.085,.19,.19,1),H);
 Card(X,Y,W,40,Fill);
 Rect(X+10,Y+39,W-20,1,FLinearColor(.19,.30,.34,.35f+H*.5f));
 Rect(X,Y+12,2,16,Enabled?FLinearColor(Mint.R,Mint.G,Mint.B,.2f+.8f*H):Muted);
 float TextWidth=0,TextHeight=0;GetTextSize(T,TextWidth,TextHeight,GEngine->GetSmallFont(),1.f);
 const float FontScale=FMath::Min(1.05f,(W-40.f)/FMath::Max(1.f,TextWidth));
 Text(T,X+16+4*H,Y+(40.f-TextHeight*FontScale)*.5f,FontScale,Enabled?FLinearColor(.91,.95,.96,Pressed?.72f:1.f):FLinearColor(.35,.41,.45,1));
 if(Hover&&PlayerOwner->WasInputKeyJustPressed(EKeys::LeftMouseButton))Pending=Action;
}
void AParkingHUD::DrawHUD(){
 Super::DrawHUD();if(!Canvas||!PlayerOwner)return;
 auto* G=Cast<AParkingGameMode>(GetWorld()->GetAuthGameMode());if(!G||!G->Car||!G->Save)return;
 S=FMath::Min(Canvas->SizeX/1280.f,Canvas->SizeY/720.f);if(S<=0)return;
 OriginX=(Canvas->SizeX-1280.f*S)*.5f;OriginY=(Canvas->SizeY-720.f*S)*.5f;
 FrameDelta=FMath::Clamp(GetWorld()->GetDeltaSeconds(),0.f,.1f);
 if(LastScreen!=G->Screen){LastScreen=G->Screen;ScreenAge=0;HoverTweens.Empty();FOVDragging=false;}
 ScreenAge+=FrameDelta;
 const float Reveal=ParkingUI::Ease(ScreenAge/.32f);
 LayerAlpha=Reveal;LayerY=12.f*(1.f-Reveal);
 float X,Y;if(PlayerOwner->GetMousePosition(X,Y)){MX=(X-OriginX)/S;MY=(Y-OriginY)/S;}else MX=MY=-1;
 if(G->Screen!=8)FOVDragging=false;
 Pending=-1;auto* C=G->Car.Get();
 const TCHAR* ModeNames[]={TEXT("AUTOMATIC"),TEXT("SEQUENTIAL"),TEXT("MANUAL CLUTCH")};
 FString Gear=C->Drive.gear<0?TEXT("R"):(C->Drive.gear==0?TEXT("N"):(C->Drive.mode==Parking::Mode::Automatic?TEXT("D"):FString::FromInt(C->Drive.gear)));
 // Driving instruments use the same short S-curve reveal as the menus.
 if(G->Screen==0){
 Card(24,22,520,76,Ink);
 Text(FString::Printf(TEXT("%02d  /  %s"),G->Level+1,*G->Levels[G->Level].Name),42,35,1.5f,FLinearColor::White);
 Text(TEXT("Fit the outline. Face the arrow."),42,66,.95f,Muted);
 Card(1010,22,246,76,Ink);
 Text(FString::Printf(TEXT("COLLISIONS   %d / 3"),G->Rules.collisions),1030,43,1.45f,G->Rules.collisions?FLinearColor(1,.45,.25):FLinearColor::White);
 Card(24,565,290,130,Ink);
 Text(Gear,44,576,3.1f,Mint);
 Text(FString::Printf(TEXT("%02.0f km/h"),FMath::Abs(C->Speed)*3.6f),110,582,2.1f,FLinearColor::White);
 Text(ModeNames[int(C->Drive.mode)],44,630,1.05f,Muted);
 Text(FString::Printf(TEXT("%04.0f RPM   %s"),C->Drive.rpm,C->Handbrake?TEXT("HANDBRAKE"):TEXT("")),44,658,1.f,C->Handbrake?FLinearColor(1,.65,.2):Muted);
 Rect(430,650,420,45,Ink);Rect(460,672,360,3,FLinearColor(.3,.4,.43));
 Rect(640+float(C->Steering.angle)*175-3,665,6,16,Mint);
 Text(TEXT("L                      STEERING                      R"),460,654,.8f,Muted);
 // Sensors sit top-left, directly under the level card (card ends at y=98).
 Card(24,110,246,205,Ink);Text(TEXT("PARKING SENSORS"),39,122,1.15f,FLinearColor::White);
 for(int i=0;i<6;i++){
  float D=C->Sensors[i];int Row=i/3,Col=i%3;
  FLinearColor Color=D<35?FLinearColor(1,.2,.1):(D<90?FLinearColor(1,.65,.08):FLinearColor(.15,.55,.35));
  Rect(38+Col*73,155+Row*94,64,25,D<250?Color:FLinearColor(.12,.17,.19));
  Text(D<250?FString::Printf(TEXT("%.0f cm"),D):TEXT("--"),44+Col*73,159+Row*94,.9f,FLinearColor::White);
 }
 Text(TEXT("FRONT"),104,186,.85f,Muted);Text(TEXT("REAR"),111,221,.85f,Muted);
 if(G->Rules.held>0){Rect(430,610,420,25,Ink);Rect(430,610,420*FMath::Clamp(float(G->Rules.held/2),0.f,1.f),25,Mint);Text(TEXT("HOLD STILL"),580,613,1,Ink);}
 if(!C->Drive.running&&G->Screen==0){Rect(380,120,520,50,Ink);Text(TEXT("ENGINE STALLED  /  CLUTCH + I TO RESTART"),400,135,1.25f,FLinearColor(1,.55,.2));}
 }
 if(G->Screen!=0){
  LayerAlpha=1;LayerY=0;
  DrawRect(FLinearColor(.012,.020,.030,.94),0,0,Canvas->SizeX,Canvas->SizeY);
  Rect(0,0,6,720,Mint);
  Rect(64,111,1152,1,FLinearColor(.13,.21,.25));
  Text(TEXT("PRECISION DRIVING"),963,57,1.f,Muted);
  Text(TEXT("BETA 1.7.8"),1092,681,.85f,Muted);
  LayerAlpha=Reveal;LayerY=18.f*(1.f-Reveal);
  if(G->Screen==1 || G->Screen==2 || G->Screen==5 || G->Screen==6){
   Card(710,165,505,405,Ink);
   Rect(740,194,40,3,Mint);
  }
  if(G->Screen==9){Card(48,152,380,478,Ink);Card(432,152,784,478,Ink);}

  Text(TEXT("CIAZ PARKING"),64,40,2.6f,FLinearColor::White);
  Text(G->Save->VehicleIndex==1?TEXT("2022 SUZUKI SWIFT"):TEXT("2017 SUZUKI CIAZ"),66,83,1.f,Mint);
  switch(G->Screen){
  case 1:
   Text(TEXT("Take your time."),66,150,2.7f,FLinearColor::White);
   Text(TEXT("Find the space."),66,193,2.7f,FLinearColor::White);
   Text(TEXT("Three impacts end the attempt."),68,253,1.2f,Muted);
   Button(TEXT("START / CONTINUE"),68,312,350,1);
   Button(TEXT("LEVEL SELECT"),68,362,350,2);
   Button(TEXT("SETTINGS"),68,412,350,3);
   Button(TEXT("CONTROLS"),68,462,350,4);
   Button(TEXT("QUIT"),68,512,350,5);
   Text(TEXT("THE PARKING COLLECTION"),740,222,1.5f,FLinearColor::White);
   Text(TEXT("10 courses. One precise finish."),740,268,1.2f,Muted);
   Text(TEXT("Keyboard or T248 wheel + pedals"),740,309,1.1f,Muted);
   Button(G->Save->VehicleIndex==1?TEXT("VEHICLE: SWIFT  /  CHANGE"):TEXT("VEHICLE: CIAZ  /  CHANGE"),740,365,420,30);
   Text(TEXT("Choose your transmission in Settings"),740,522,1,Muted);break;
  case 2:
   Text(TEXT("TAKE A BREATHER"),740,224,1.6f,FLinearColor::White);
   Text(TEXT("Your current attempt is waiting."),740,275,1.15f,Muted);
   Text(TEXT("Resume when you are ready."),740,310,1.15f,Muted);
   Text(TEXT("PAUSED"),68,160,2.5f,FLinearColor::White);
   Button(TEXT("RESUME"),68,230,350,6);Button(TEXT("RETRY LEVEL"),68,280,350,7);
   Button(TEXT("SETTINGS"),68,330,350,3);Button(TEXT("CONTROLS"),68,380,350,4);
   Button(TEXT("MAIN MENU"),68,430,350,8);break;
  case 3:
   Text(TEXT("SELECT A LEVEL"),68,140,1.8f,FLinearColor::White);
   for(int i=0;i<G->Levels.Num();i++){
    int Col=i%2,Row=i/2;
    Button(FString::Printf(TEXT("%02d  %s%s"),i+1,*G->Levels[i].Name,i>=G->Save->Unlocked?TEXT("  [LOCKED]"):TEXT("")),
     68+Col*570,190+Row*65,530,100+i,i<G->Save->Unlocked);
   }Button(TEXT("MAIN MENU"),68,560,260,8);break;
  case 4:
   Text(TEXT("SETTINGS"),68,155,2.2f,FLinearColor::White);
   Button(TEXT("GRAPHICS"),68,240,450,12);
   Button(TEXT("CONTROLS / WHEEL"),68,300,450,13);
   Button(FString::Printf(TEXT("MASTER VOLUME: %.0f%%"),G->Save->MasterVolume*100),68,360,450,26);
   Button(TEXT("BACK"),68,470,300,10);
   Text(TEXT("Make it feel right."),680,246,2.f,FLinearColor::White);
   Text(TEXT("Display and visual quality in Graphics."),680,304,1.1f,Muted);
   Text(TEXT("Wheel, pedals and key bindings in Controls."),680,345,1.1f,Muted);
   break;
  case 8:{
   auto* Save=G->Save.Get();
   const bool Editable=!G->GraphicsConfirm;
   Text(TEXT("GRAPHICS"),68,130,1.8f,FLinearColor::White);
   const TCHAR* Presets[]={TEXT("LOW"),TEXT("MEDIUM"),TEXT("HIGH"),TEXT("EPIC")};
   for(int i=0;i<4;++i)Button(Presets[i],640+i*142,124,132,540+i,Editable);
   for(int i=0;i<14;++i){
    const int Col=i/7,Row=i%7;
    Button(G->GraphicsLabel(i),68+Col*575,185+Row*49,545,500+i,Editable);
   }
   Text(TEXT("Click an option to cycle. Borderless uses your desktop resolution."),68,536,.95f,Muted);
   Text(FString::Printf(TEXT("INTERIOR FOV: %.0f deg"),Save->InteriorFOV),68,559,1.f,FLinearColor::White);
   const bool SliderHover=!G->GraphicsConfirm && ScreenAge>=.32f && MX>=68 && MX<=408 && MY>=580+LayerY && MY<=605+LayerY;
   if(SliderHover && PlayerOwner->WasInputKeyJustPressed(EKeys::LeftMouseButton))FOVDragging=true;
   float DisplayFOV=Save->InteriorFOV;
   if(FOVDragging){
    if(PlayerOwner->IsInputKeyDown(EKeys::LeftMouseButton)){
     DisplayFOV=60.f+50.f*FMath::Clamp((MX-68.f)/340.f,0.f,1.f);
     Pending=400+FMath::RoundToInt(DisplayFOV-60.f);
    }else{FOVDragging=false;Pending=480;}
   }
   Rect(68,590,340,5,Muted);
   Rect(68,590,340*(DisplayFOV-60.f)/50.f,5,Mint);
   Rect(68+340*(DisplayFOV-60.f)/50.f-5,584,10,17,Mint);

   Text(TEXT("Interior FOV saves immediately."),450,589,.85f,Muted);
   if(G->GraphicsConfirm){
    const int Seconds=FMath::Max(0,FMath::CeilToInt(float(G->GraphicsDeadline-FPlatformTime::Seconds())));
    Text(FString::Printf(TEXT("Keep these settings? Reverting in %d s"),Seconds),680,570,1.15f,Mint);
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
   Text(TEXT("CONTROLS / WHEEL"),68,125,1.7f,FLinearColor::White);
   Button(FString(TEXT("INPUT: "))+ (Save->WheelEnabled?TEXT("T248"):TEXT("KEYBOARD")),68,165,340,20);
   Button(ModeNames[Save->Transmission],68,215,340,21);
   Button(TEXT("KEYBOARD BINDINGS"),68,265,340,14);
   Button(Save->HandbrakeHold?TEXT("HANDBRAKE: HOLD"):TEXT("HANDBRAKE: TOGGLE"),68,315,340,29);
   Text(Save->HandbrakeHold?TEXT("Hold the assigned key; release to disengage."):TEXT("Press once to engage; again to release."),68,530,.85f,Muted);
   Button(Save->Feedback?TEXT("FORCE FEEDBACK: ON"):TEXT("FORCE FEEDBACK: OFF"),68,365,340,24);
   Button(Save->FeedbackInvert?TEXT("FFB DIRECTION: INVERTED"):TEXT("FFB DIRECTION: NORMAL"),68,415,340,25);
   Button(G->Calibrating?TEXT("FINISH CALIBRATION"):TEXT("START CALIBRATION"),68,465,340,23);
   Button(TEXT("BACK TO SETTINGS"),68,580,340,11);
   Text(G->Wheel.IsConnected()?G->Wheel.Name:TEXT("T248 not connected"),450,126,1.1f,Mint);
   const TCHAR* Labels[]={TEXT("Steering"),TEXT("Throttle"),TEXT("Brake"),TEXT("Clutch")};
   for(int i=0;i<4;i++){
    Button(FString::Printf(TEXT("%s  AXIS %d"),Labels[i],Save->Axes[i]),450,165+i*48,270,200+i);
    Button(Save->Invert[i]?TEXT("INVERTED"):TEXT("NORMAL"),735,165+i*48,160,210+i);
   }
   Button(FString::Printf(TEXT("SHIFT UP: BUTTON %d"),Save->ShiftUp),450,365,270,27);
   Button(FString::Printf(TEXT("SHIFT DOWN: BUTTON %d"),Save->ShiftDown),735,365,270,28);
   Text(TEXT("Live axes 0-7: move one control to identify its axis"),450,425,1.05f,Muted);
   for(int i=0;i<8;i++){
    Text(FString::FromInt(i),450+i*92,452,1,FLinearColor::White);
    Rect(450+i*92,478,72,9,Panel);Rect(450+i*92,478,72*G->Wheel.Axes[i],9,Mint);
   }
   Text(Save->Calibrated?TEXT("Calibration saved"):TEXT("Calibration required before wheel driving"),450,510,1.1f,Mint);
   Text(TEXT("During calibration: turn to both locks and fully press each pedal."),450,548,1,Muted);
   Text(TEXT("Before Finish: centre the wheel and release every pedal."),450,573,1,Muted);
   Text(G->Wheel.HasForceFeedback()?TEXT("Force-feedback interface detected"):TEXT("Force-feedback interface not available"),450,605,1,Muted);
  }break;
  case 5:
   Text(TEXT("SPACE FOUND"),740,224,1.8f,Mint);
   Text(TEXT("A careful finish. On to the next course."),740,280,1.1f,Muted);
   Text(TEXT("PARKED."),68,170,4.f,Mint);
   Text(FString::Printf(TEXT("%s  /  %d collisions"),*G->Levels[G->Level].Name,G->Rules.collisions),68,250,1.5,FLinearColor::White);
   Button(G->Level<9?TEXT("NEXT LEVEL"):TEXT("REPLAY FINAL LEVEL"),68,325,350,9);
   Button(TEXT("LEVEL SELECT"),68,375,350,2);Button(TEXT("MAIN MENU"),68,425,350,8);break;
  case 6:
   Text(TEXT("ANOTHER APPROACH"),740,224,1.7f,FLinearColor::White);
   Text(TEXT("Use the mirrors. Watch the sensors."),740,280,1.1f,Muted);
   Text(TEXT("THREE IMPACTS."),68,170,3.2f,FLinearColor(1,.45,.25));
   Text(TEXT("Reset, slow down, and try another approach."),68,245,1.4f,Muted);
   Button(TEXT("RETRY"),68,325,350,7);Button(TEXT("LEVEL SELECT"),68,375,350,2);Button(TEXT("MAIN MENU"),68,425,350,8);break;
  case 7:{
   Text(TEXT("CONTROLS  /  CLICK A ROW TO REBIND"),68,135,1.6f,FLinearColor::White);
   const TCHAR* Labels[]={TEXT("Accelerator"),TEXT("Brake only"),TEXT("Steer left"),TEXT("Steer right"),TEXT("Centre steering"),
    TEXT("Parking brake"),TEXT("Drive / Gear 1"),TEXT("Neutral"),TEXT("Reverse"),TEXT("Shift down"),TEXT("Shift up"),
    TEXT("Clutch"),TEXT("Restart engine"),TEXT("Transmission"),TEXT("Camera"),TEXT("Look back"),TEXT("Headlights"),
    TEXT("Gear 2"),TEXT("Gear 3"),TEXT("Gear 4"),TEXT("Gear 5")};
   const FKey Keys[]={EKeys::W,EKeys::S,EKeys::A,EKeys::D,EKeys::X,EKeys::SpaceBar,EKeys::One,EKeys::N,EKeys::R,EKeys::Q,EKeys::E,EKeys::LeftShift,EKeys::I,EKeys::T,EKeys::C,EKeys::V,EKeys::L,EKeys::Two,EKeys::Three,EKeys::Four,EKeys::Five};
   for(int i=0;i<21;i++){
    int Col=i/7,Row=i%7;
    Button(FString::Printf(TEXT("%s: %s"),Labels[i],*G->BoundKey(Keys[i]).GetDisplayName().ToString()),68+Col*385,185+Row*49,365,300+i);
   }
   Text(TEXT("Steering holds when stopped; centres while moving. Mouse: look around."),68,545,1.1f,Mint);
   Text(TEXT("ESC Pause  /  F5 Retry  /  F4 Settings  /  F1 Key bindings. Arrow keys also drive."),68,572,1.05f,Muted);
   Text(TEXT("T248: calibrate in Settings. C: camera. V: look back. Cockpit look: +/-135 deg."),68,598,1.05f,Muted);
   Button(TEXT("BACK TO CONTROLS"),68,638,300,13);
  }break;
  }
 }else Text(TEXT("ESC  Pause     C  Camera     F1  Controls"),571,28,.85f,Muted);
 LayerAlpha=1;LayerY=0;
 if(G->NoticeTime>0){
  if(LastNotice!=G->Notice){LastNotice=G->Notice;NoticeAge=0;}
  NoticeAge+=FrameDelta;
  const float Toast=ParkingUI::Ease(NoticeAge/.25f)*ParkingUI::Ease(G->NoticeTime/.25f);
  LayerAlpha=Toast;LayerY=8*(1-Toast);
  // Starts right of the sensor card so notices never cover it.
  Card(290,114,850,38,Ink);Rect(290,122,3,22,Mint);
  Text(G->Notice,305,125,1.05,FLinearColor::White);
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
