#include "../Source/CiazParking/VehicleDynamics.h"
#include <cassert>
#include <iostream>
using namespace VehicleDynamics;
int main(){
 assert(Ackermann(0,1)==0);
 assert(Ackermann(.8,1)>Ackermann(.8,-1));
 assert(std::abs(Ackermann(.8,1)+Ackermann(-.8,-1))<1e-12);
 assert(Suspension(.1,-.1)>Suspension(.1,.1));
 assert(Suspension(-.1,0)==0);assert(Suspension(1,-100)<=16000);
 for(double dt:{1./30,1./60,1./120}){
  TireInput i;i.dt=dt;
  auto rest=Tire(i);assert(rest.longitudinal==0&&rest.lateral==0);
  i.load=0;i.drive=1000;assert(Tire(i).longitudinal==0);i.load=2700;
  i.drive=0;i.longSpeed=.03;i.brake=1;
  auto stop=Tire(i);assert(std::abs(i.longSpeed+stop.longitudinal/i.mass*dt-(1-VehicleDynamics::LowSpeedStopGain)*i.longSpeed)<1e-10);
  i.longSpeed=-.03;stop=Tire(i);assert(std::abs(i.longSpeed+stop.longitudinal/i.mass*dt-(1-VehicleDynamics::LowSpeedStopGain)*i.longSpeed)<1e-10);
  i.longSpeed=0;i.gravityLong=300;stop=Tire(i);assert(std::abs(stop.longitudinal+300)<1e-10);
  i.gravityLong=0;i.brake=0;i.sideSpeed=.03;auto side=Tire(i);
  assert(std::abs(i.sideSpeed+side.lateral/i.mass*dt-(1-VehicleDynamics::LowSpeedStopGain)*i.sideSpeed)<1e-10);
  i.sideSpeed=10;i.longSpeed=15;i.drive=10000;
  auto saturated=Tire(i);assert(std::hypot(saturated.longitudinal,saturated.lateral)<=saturated.grip+1e-8);
  assert(saturated.lateral*i.sideSpeed<=0);
 }
 // Brake a four-contact 1100 kg car: no overshoot across rendering rates.
 for(double dt:{1./30,1./60,1./120}){
  double speed=5;
  for(int n=0;n<int(2/dt);++n){TireInput i;i.dt=dt;i.longSpeed=speed;i.brake=1;
   speed+=Tire(i).longitudinal/275*dt;assert(speed>=-1e-9);}
  assert(std::abs(speed)<.001);
 }
 std::cout<<"PASS: Ackermann symmetry, suspension damping, tire force limits, air contact, no idle creep, slope hold and braking at 30/60/120 Hz.\n";
}
