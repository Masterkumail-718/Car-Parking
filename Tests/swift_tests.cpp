#include "../Source/CiazParking/ParkingCore.h"
#include "../Source/CiazParking/VehicleDynamics.h"
#include <cassert>
#include <iostream>
int main(){
 double peak=0;
 for(int rpm=850;rpm<=6500;++rpm)peak=std::max(peak,Parking::SwiftTorque(rpm)*rpm*2*3.141592653589793/60.);
 assert(std::abs(peak-61000)<1);assert(std::abs(Parking::SwiftTorque(4200)-113)<1e-9);
 Parking::Drive swift;swift.swift=true;swift.tireRadius=.30495;swift.reset();assert(swift.swift);assert(swift.select(1,0,0));
 for(int i=0;i<120;++i)assert(std::abs(swift.step(1./120.,0,0,0,0))<1e-9);
 assert(!swift.select(-1,2,0));swift.setMode(Parking::Mode::Sequential);assert(swift.swift);
 assert(swift.select(1,0,0));double force=0;for(int i=0;i<120;++i)force=swift.step(1./120.,0,1,0,0);assert(force>3000&&force<6500);
 const double left=VehicleDynamics::Ackermann(.5,-1,2.44857,.746165),right=VehicleDynamics::Ackermann(.5,1,2.44857,.746165);
 assert(right>left&&left>0);assert(std::abs(VehicleDynamics::Ackermann(-.5,-1,2.44857,.746165)+right)<1e-12);
 VehicleDynamics::SuspensionState corner;assert(std::abs(corner.Step(.25,0,1./60.,930*.61/2,true,.76)-930*.61/2*9.81)<1e-9);
 assert(Parking::fits({0,0},0,{0,0},0,4.0,2.0,3.84,1.85));assert(!Parking::fits({0,0},0,{0,0},0,4.0,2.0,4.49,1.90));
 std::cout<<"PASS Swift torque/power, retained profile, no creep, direction guard, gearing, Ackermann, preload and parking footprint.\n";
}
