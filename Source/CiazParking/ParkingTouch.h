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
enum class Control {None,Menu,Brake,Accelerator,Left,Right,Wheel,Drive,Neutral,Reverse,Handbrake,Pause,Camera};
struct Button {Control Role;Area Bounds;const char* Label;};
constexpr std::array<Button,10> Buttons={{
 {Control::Brake,{24,548,126,144},"BRAKE"},
 {Control::Accelerator,{166,548,126,144},"ACCEL"},
 {Control::Left,{964,548,132,144},"LEFT"},
 {Control::Right,{1112,548,132,144},"RIGHT"},
 {Control::Drive,{398,548,72,56},"D"},
 {Control::Neutral,{482,548,72,56},"N"},
 {Control::Reverse,{566,548,72,56},"R"},
 {Control::Handbrake,{398,620,240,64},"HANDBRAKE"},
 {Control::Pause,{875,24,112,52},"PAUSE"},
 {Control::Camera,{746,24,112,52},"CAMERA"}
}};
constexpr Point WheelCentre{1104,592};
constexpr double WheelRadius=99;

inline Point ToLayout(Point P,double ViewWidth,double ViewHeight){
 const double Scale=std::min(ViewWidth/Width,ViewHeight/Height);
 if(Scale<=0)return {-1,-1};
 return {(P.X-(ViewWidth-Width*Scale)*.5)/Scale,(P.Y-(ViewHeight-Height*Scale)*.5)/Scale};
}
inline double WheelDistance(Point P){return std::hypot(P.X-WheelCentre.X,P.Y-WheelCentre.Y);}
inline Control Hit(Point P,bool WheelMode){
 if(WheelMode&&WheelDistance(P)<=WheelRadius+8)return Control::Wheel;
 for(const auto& B:Buttons){
  if(WheelMode&&(B.Role==Control::Left||B.Role==Control::Right))continue;
  if(B.Bounds.Contains(P))return B.Role;
 }
 return Control::None;
}
struct Sample {Point Position;bool Down=false;};
class State {
 struct Finger {Sample Last;Control Role=Control::None;bool Pressed=false;};
 std::array<Finger,FingerCount> Fingers{};
 double WheelAngle=0;
public:
 void Cancel(){
  for(auto& F:Fingers){F.Role=Control::None;F.Pressed=false;}
  WheelAngle=0;
 }
 void Update(const std::array<Sample,FingerCount>& Samples,bool Driving,bool WheelMode){
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
    const Control Role=Driving?Hit(S.Position,WheelMode):Control::Menu;
    if(Role!=Control::None&&!Down(Role)){F.Role=Role;F.Pressed=true;}
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
};
}
