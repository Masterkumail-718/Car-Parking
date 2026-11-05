#include "../Source/CiazParking/ParkingCore.h"
#include <cassert>
#include <cmath>
#include <limits>
#include <iostream>
int main(){
 using Parking::WheelCenteringForce;
 assert(WheelCenteringForce(.8,0,.35,false)==0);
 assert(WheelCenteringForce(0,5,.35,false)==0);
 assert(WheelCenteringForce(.8,5,0,false)==0);
 const double slow=WheelCenteringForce(.8,1,.35,false);
 const double fast=WheelCenteringForce(.8,5,.35,false);
 assert(slow>0 && fast>slow); // requested reversal of the old negative demand
 assert(slow> .8*(1-.05)*.08*.35); // stronger low-speed response
 assert(WheelCenteringForce(-.8,5,.35,false)==-fast);
 assert(WheelCenteringForce(.8,-5,.35,false)==fast);
 assert(WheelCenteringForce(.8,5,.35,true)==-fast);
 for(double speed:{-100.,-5.,-.05,0.,.05,1.,5.,100.})
  for(double angle:{-2.,-1.,-.01,0.,.01,1.,2.}){
   const double force=WheelCenteringForce(angle,speed,1,false);
   assert(std::abs(force)<=.35);
   assert(force*angle>=0);
  }
 assert(WheelCenteringForce(1,5,-1,false)==0);
 const double nan=std::numeric_limits<double>::quiet_NaN();
 assert(WheelCenteringForce(nan,5,.35,false)==0);
 assert(WheelCenteringForce(1,nan,.35,false)==0);
 assert(WheelCenteringForce(1,5,nan,false)==0);
 std::cout<<"Feedback tests passed\n";
}
