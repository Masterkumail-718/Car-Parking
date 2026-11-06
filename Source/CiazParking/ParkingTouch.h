#pragma once
#include <algorithm>
#include <array>
#include <cmath>

namespace ParkingTouch {
constexpr int FingerCount=10;
constexpr double Width=1280,Height=720;
constexpr double Pi=3.141592653589793,WheelTravel=Pi*.75;
struct Point { double X=0,Y=0; };
struct Area {
 double X,Y,W,H;
 bool Contains(Point P) const {return P.X>=X&&P.X<X+W&&P.Y>=Y&&P.Y<Y+H;}
};
enum class Control {None,Menu,Brake,Accelerator,Clutch,Left,Right,Wheel,Drive,Neutral,Reverse,Handbrake,Pause,Camera,Look};
struct Button {Control Role;Area Bounds;const char* Label;};
constexpr Area GearSelector{1037,404,192,51};
constexpr std::array<Button,11> Buttons={{
 {Control::Brake,{976,494,133,164},"BRAKE"},
 {Control::Accelerator,{1121,494,128,164},"ACCEL"},
 {Control::Clutch,{735,494,133,164},"CLUTCH"},
 {Control::Left,{32,494,113,164},"LEFT"},
 {Control::Right,{157,494,113,164},"RIGHT"},
 {Control::Drive,{1043,409,60,41},"D"},
 {Control::Neutral,{1103,409,60,41},"N"},
 {Control::Reverse,{1163,409,60,41},"R"},
 {Control::Handbrake,{880,540,80,80},"P"},
 {Control::Pause,{1198,32,57,54},"PAUSE"},
 {Control::Camera,{1124,32,60,54},"CAMERA"}
}};
constexpr Point WheelCentre{152,540};
constexpr double WheelRadius=122;

inline Point ToLayout(Point P,double ViewWidth,double ViewHeight){
 const double Scale=std::min(ViewWidth/Width,ViewHeight/Height);
 if(Scale<=0)return {-1,-1};
 return {(P.X-(ViewWidth-Width*Scale)*.5)/Scale,(P.Y-(ViewHeight-Height*Scale)*.5)/Scale};
}
inline double WheelDistance(Point P){return std::hypot(P.X-WheelCentre.X,P.Y-WheelCentre.Y);}
inline Control Hit(Point P,bool WheelMode,bool ManualClutch=false){
 if(WheelMode&&WheelDistance(P)<=WheelRadius)return Control::Wheel;
 for(const auto& B:Buttons){
  if(B.Role==Control::Clutch&&!ManualClutch)continue;
  if(WheelMode&&(B.Role==Control::Left||B.Role==Control::Right))continue;
  if(B.Role==Control::Handbrake&&std::hypot(P.X-B.Bounds.X-40,P.Y-B.Bounds.Y-40)>40)continue;
  if(B.Bounds.Contains(P))return B.Role;
 }
 return Control::None;
}
struct Sample {Point Position;bool Down=false;};
class State {
 struct Finger {Sample Last;Control Role=Control::None;bool Pressed=false;};
 std::array<Finger,FingerCount> Fingers{};
 double WheelAngle=0;
 Point LookMotion;
public:
 void Cancel(){
  for(auto& F:Fingers){F.Role=Control::None;F.Pressed=false;}
  WheelAngle=0;
  LookMotion={};
 }
 void Update(const std::array<Sample,FingerCount>& Samples,bool Driving,bool WheelMode,bool ManualClutch=false){
  LookMotion={};
  // Release first so a newly pressed finger can claim a control in the same frame.
  for(int I=0;I<FingerCount;++I){
   auto& F=Fingers[I];
   F.Pressed=false;
   if(!Samples[I].Down){
    if(F.Role==Control::Wheel)WheelAngle=0;
    F={};
   }
  }
  for(int I=0;I<FingerCount;++I){
   const auto& S=Samples[I];auto& F=Fingers[I];
   if(!S.Down)continue;
   if(!F.Last.Down){
    Control Role=Driving?Hit(S.Position,WheelMode,ManualClutch):Control::Menu;
    if(Driving&&Role==Control::None&&!GearSelector.Contains(S.Position))Role=Control::Look;
    if(Role!=Control::None&&!Down(Role)){F.Role=Role;F.Pressed=true;}
   }else if(F.Role==Control::Look){
    LookMotion={S.Position.X-F.Last.Position.X,S.Position.Y-F.Last.Position.Y};
   }else if(F.Role==Control::Wheel&&WheelDistance(F.Last.Position)>20&&WheelDistance(S.Position)>20){
    const auto Angle=[](Point P){return std::atan2(P.X-WheelCentre.X,WheelCentre.Y-P.Y);};
    const double Delta=std::remainder(Angle(S.Position)-Angle(F.Last.Position),2*Pi);
    WheelAngle=std::clamp(WheelAngle+Delta,-WheelTravel,WheelTravel);
   }
   F.Last=S;
  }
 }
 bool Down(Control Role) const {
  return std::any_of(Fingers.begin(),Fingers.end(),[Role](const Finger& F){return F.Role==Role&&F.Last.Down;});
 }
 bool Pressed(Control Role) const {
  return std::any_of(Fingers.begin(),Fingers.end(),[Role](const Finger& F){return F.Role==Role&&F.Pressed;});
 }
 Point MenuPosition() const {
  for(const auto& F:Fingers)if(F.Role==Control::Menu)return F.Last.Position;
  return {-1,-1};
 }
 double Steering() const {return WheelAngle/WheelTravel;}
 Point LookDelta() const {return LookMotion;}
};
}
