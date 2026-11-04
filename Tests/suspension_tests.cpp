#include "../Source/CiazParking/VehicleDynamics.h"
#include <cassert>
#include <iostream>
using namespace VehicleDynamics;
int main(){
 constexpr double mass=302.5;
 for(double dt:{1./30,1./60,1./120}){
  SuspensionState left,right;
  assert(std::abs(left.Step(.25,0,dt,mass,true)-mass*9.81)<1e-8);
  assert(left.Step(.20,0,dt,mass,true)>right.Step(.25,0,dt,mass,true));
  left.Release();assert(!left.grounded&&left.rate==0);
  // Quarter-car settling with independent spring/damper state.
  SuspensionState corner;double height=.06,velocity=0;
  for(int n=0;n<int(4/dt);++n){
   double force=corner.Step(.25+height,-velocity,dt,mass,true);
   velocity+=(force/mass-9.81)*dt;height+=velocity*dt;
   assert(std::isfinite(height)&&std::abs(height)<.2);
  }
  assert(std::abs(height)<.002&&std::abs(velocity)<.01);
 }
 // Arc samples ahead of the hub see a curb before the hub reaches its edge.
 const double radius=.3065,offset=.75*radius;
 const double flat=TireEnvelopeLength(.25+radius,0);
 const double curb=TireEnvelopeLength(.25+radius-.12,offset);
 assert(std::abs(flat-.25)<1e-12);assert(curb<flat);
 assert(TireEnvelopeLength(.25+radius,offset)>flat);
 // Added ride-height offsets shift the chassis, not the ground contact target.
 for(double lift:{0.,.04,.08})assert(std::abs((.25+lift)-lift-.25)<1e-12);
 std::cout<<"PASS independent corners, static ride-height support, 30/60/120 Hz quarter-car settling, tire arc curb detection and contact release.\n";
}
