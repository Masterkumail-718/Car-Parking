#include "../Source/CiazParking/ParkingTouch.h"
#include <cassert>
#include <iostream>

int main(){
 using namespace ParkingTouch;
 std::array<Sample,FingerCount> Fingers{};
 State Input;
 Fingers[0]={{220,620},true};
 Fingers[1]={{1000,620},true};
 Input.Update(Fingers,true,false);
 assert(Input.Down(Control::Accelerator)&&Input.Down(Control::Left));
 assert(Input.Pressed(Control::Accelerator));
 Fingers[0].Position={70,620};
 Input.Update(Fingers,true,false);
 assert(Input.Down(Control::Accelerator)&&!Input.Down(Control::Brake));
 assert(!Input.Pressed(Control::Accelerator));
 Fingers[2]={{70,620},true};
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
 Fingers[1]={{220,620},true};
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

 const auto P=ToLayout({480,200},1920,720);
 assert(P.X==160&&P.Y==200);
 std::cout<<"PASS: touch ownership, concurrent controls, cancellation, wheel wrap and viewport mapping\n";
}
