#include "../Source/CiazParking/ParkingCore.h"
#include "../Source/CiazParking/VehicleDynamics.h"
#include <cassert>
#include <limits>
#include <random>
#include <iostream>
int main(){
 using namespace Parking;
 assert(SteeringCalibrationValid(0,1,.5));assert(SteeringCalibrationValid(.1,.9,.5));
 assert(!SteeringCalibrationValid(0,1,0));assert(!SteeringCalibrationValid(0,1,1));
 assert(!SteeringCalibrationValid(0,1,.2));assert(!SteeringCalibrationValid(.5,.6,.55));
 assert(!SteeringCalibrationValid(0,1,std::numeric_limits<double>::quiet_NaN()));
 assert(PedalAtRest(0,1,0));assert(PedalAtRest(0,1,1));assert(PedalAtRest(.1,.9,.88));
 assert(!PedalAtRest(0,1,.5));assert(!PedalAtRest(.1,.9,1));assert(!PedalAtRest(0,1,-.1));
 assert(!PedalAtRest(1,0,0));assert(!PedalAtRest(0,1,std::numeric_limits<double>::infinity()));
 std::mt19937 random(177);std::uniform_real_distribution<double> unit(0,1);
 for(int n=0;n<100000;++n){
  VehicleDynamics::TireInput i;i.dt=1./(20+unit(random)*220);i.mass=150+unit(random)*200;i.load=unit(random)*12000;
  i.longSpeed=unit(random)*80-40;i.sideSpeed=unit(random)*30-15;i.drive=unit(random)*10000-5000;i.brake=unit(random);
  i.gravityLong=unit(random)*2000-1000;i.gravitySide=unit(random)*2000-1000;
  i.rear=n%2;i.handbrake=n%3==0;i.rearGripRecovery=unit(random);
  const auto out=VehicleDynamics::Tire(i);
  assert(std::isfinite(out.longitudinal)&&std::isfinite(out.lateral)&&std::isfinite(out.grip));
  assert(std::hypot(out.longitudinal,out.lateral)<=out.grip+1e-7);
 }
 for(bool swift:{false,true})for(Mode mode:{Mode::Automatic,Mode::Sequential,Mode::Clutch}){
  Drive d;d.swift=swift;d.mode=mode;d.gear=1;
  for(int n=0;n<10000;++n){const double f=d.step(1./120.,unit(random)*30,unit(random),unit(random),unit(random));assert(std::isfinite(f)&&std::isfinite(d.rpm)&&d.gear>=-1&&d.gear<=5);}
 }
 std::cout<<"PASS calibration rejection cases, 100,000 bounded tire-force cases and 60,000 drivetrain steps.\n";
}
