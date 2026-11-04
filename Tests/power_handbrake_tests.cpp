#include "../Source/CiazParking/VehicleDynamics.h"
#include "../Source/CiazParking/ParkingCore.h"
#include <cassert>
#include <iostream>
int main(){
 double peak=0,peakRPM=0;
 for(int rpm=850;rpm<=6500;++rpm){double hp=Parking::EngineTorque(rpm)*rpm*2*3.141592653589793/60/745.699871582;if(hp>peak){peak=hp;peakRPM=rpm;}}
 assert(std::abs(peak-110)<.01 && peakRPM==6000);
 for(double dt:{1./30,1./60,1./120})for(double direction:{-1.,1.}){
  VehicleDynamics::TireInput i;i.dt=dt;i.rear=true;i.longSpeed=10*direction;i.sideSpeed=2;i.handbrake=true;
  auto locked=VehicleDynamics::Tire(i);assert(locked.longitudinal*i.longSpeed+locked.lateral*i.sideSpeed<0);
  assert(std::hypot(locked.longitudinal,locked.lateral)<=locked.grip+1e-8);
  i.handbrake=false;auto rolling=VehicleDynamics::Tire(i);assert(std::abs(locked.lateral)<std::abs(rolling.lateral));
  i.handbrake=true;i.sideSpeed=0;assert(VehicleDynamics::Tire(i).lateral==0);
  i.longSpeed=.02*direction;auto stop=VehicleDynamics::Tire(i);assert(std::abs(i.longSpeed+stop.longitudinal/i.mass*dt-(1-VehicleDynamics::LowSpeedStopGain)*i.longSpeed)<1e-8);
  i.longSpeed=0;i.gravityLong=300;assert(std::abs(VehicleDynamics::Tire(i).longitudinal+300)<1e-8);
  i.gravityLong=0;i.load=0;assert(VehicleDynamics::Tire(i).longitudinal==0);
 }
 VehicleDynamics::TireInput front;front.longSpeed=10;front.sideSpeed=1;auto free=VehicleDynamics::Tire(front);
 front.handbrake=true;auto pulled=VehicleDynamics::Tire(front);assert(free.lateral==pulled.lateral&&free.longitudinal==pulled.longitudinal);
 std::cout<<"PASS: 110 hp crank peak, rear locked skid, reduced rear lateral grip, straight-line symmetry, reverse, front isolation, low-speed hold and airborne contacts.\n";
}
