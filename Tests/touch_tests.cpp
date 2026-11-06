#include "../Source/CiazParking/ParkingTouch.h"
#include <cassert>
#include <iostream>

int main(){
 using namespace ParkingTouch;
 std::array<Sample,FingerCount> Fingers{};
 State Input;
 assert(Hit({1154,59},true)==Control::Camera);
 assert(Hit({1226,59},true)==Control::Pause);
 assert(Hit({1072,429},true)==Control::Drive);
 assert(Hit({1132,429},true)==Control::Neutral);
 assert(Hit({1192,429},true)==Control::Reverse);
 assert(Hit({920,580},true)==Control::Handbrake);
 assert(Hit({880,540},true)==Control::None);
 assert(Hit(WheelCentre,true)==Control::Wheel);
 assert(Hit({90,575},false)==Control::Left);
 assert(Hit({212,575},false)==Control::Right);
 assert(Hit(ToLayout({1154+160,59},1600,720),true)==Control::Camera);
 Fingers[0]={{1180,575},true};
 Fingers[1]={{90,575},true};
 Input.Update(Fingers,true,false);
 assert(Input.Down(Control::Accelerator)&&Input.Down(Control::Left));
 assert(Input.Pressed(Control::Accelerator));
 Fingers[0].Position={1040,575};
 Input.Update(Fingers,true,false);
 assert(Input.Down(Control::Accelerator)&&!Input.Down(Control::Brake));
 assert(!Input.Pressed(Control::Accelerator));
 Fingers[2]={{1040,575},true};
 Input.Update(Fingers,true,false);
 assert(Input.Down(Control::Accelerator)&&Input.Down(Control::Brake));
 assert(!Input.Pressed(Control::Reverse));

 Input.Cancel();
 Input.Update(Fingers,false,false);
 assert(!Input.Down(Control::Menu)&&!Input.Down(Control::Accelerator));
 Fingers={};
 Input.Update(Fingers,false,false);
 Fingers[1]={{90,350},true};
 Input.Update(Fingers,false,false);
 assert(Input.Pressed(Control::Menu)&&Input.MenuPosition().X==90);
 Input.Cancel();
 Input.Update(Fingers,true,false);
 assert(!Input.Down(Control::Menu)&&!Input.Down(Control::Left));

 Fingers={};
 Input.Update(Fingers,true,true);
 const auto Rim=[](double Angle){
  return Point{WheelCentre.X+WheelRadius*std::sin(Angle),WheelCentre.Y-WheelRadius*std::cos(Angle)};
 };
 Fingers[0]={Rim(Pi-.1),true};
 Fingers[1]={{1180,575},true};
 Input.Update(Fingers,true,true);
 assert(Input.Down(Control::Wheel)&&Input.Down(Control::Accelerator)&&Input.Steering()==0);
 Fingers[0].Position=Rim(-Pi+.1);
 Input.Update(Fingers,true,true);
 assert(std::abs(Input.Steering()-.2/WheelTravel)<1e-9);
 Fingers[0].Position=WheelCentre;
 Input.Update(Fingers,true,true);
 Fingers[0].Position=Rim(0);
 Input.Update(Fingers,true,true);
 assert(std::abs(Input.Steering()-.2/WheelTravel)<1e-9);
 Fingers[0].Position=Rim(Pi-.1);
 Input.Update(Fingers,true,true);
 assert(Input.Steering()==1);
 Fingers[0]={};
 Input.Update(Fingers,true,true);
 assert(Input.Steering()==0&&Input.Down(Control::Accelerator));

 // A camera finger keeps ownership when it crosses a pedal, and vice versa.
 Fingers={};
 Input.Update(Fingers,true,true,true);
 assert(Hit({800,575},true)==Control::None);
 assert(Hit({800,575},true,true)==Control::Clutch);
 Fingers[0]={{800,575},true};
 Fingers[1]={{500,300},true};
 Fingers[2]={{1180,575},true};
 Fingers[3]={{600,300},true};
 Fingers[4]={Rim(0),true};
 Fingers[5]={{1038,430},true}; // Gear selector rim cannot claim camera input.
 Input.Update(Fingers,true,true,true);
 assert(Input.Down(Control::Clutch)&&Input.Down(Control::Look));
 assert(Input.Down(Control::Accelerator)&&Input.Down(Control::Wheel));
 assert(Input.LookDelta().X==0&&Input.LookDelta().Y==0);
 Fingers[0].Position={500,300};
 Fingers[1].Position={1040,575};
 Fingers[3].Position={650,400};
 Fingers[4].Position=Rim(.2);
 Input.Update(Fingers,true,true,true);
 assert(Input.Down(Control::Clutch)&&!Input.Down(Control::Brake));
 assert(Input.LookDelta().X==540&&Input.LookDelta().Y==275);
 assert(Input.Steering()>0);
 Fingers[1]={};
 Fingers[5].Position={1040,580};
 Input.Update(Fingers,true,true,true);
 assert(!Input.Down(Control::Look)&&Input.LookDelta().X==0);
 Fingers[1]={{500,300},true};
 Input.Update(Fingers,true,true,true);
 assert(Input.Pressed(Control::Look)&&Input.LookDelta().X==0);
 Input.Cancel();
 Fingers[1].Position={600,300};
 Input.Update(Fingers,false,true,true);
 assert(!Input.Down(Control::Look)&&!Input.Down(Control::Clutch));
 assert(Input.LookDelta().X==0);

 const auto P=ToLayout({480,200},1920,720);
 assert(P.X==160&&P.Y==200);
 std::cout<<"PASS: touch ownership, concurrent controls, cancellation, wheel wrap and viewport mapping\n";
}
