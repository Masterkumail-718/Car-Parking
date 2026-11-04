#pragma once
#include <algorithm>
#include <cmath>
// SI units. Calibratable passenger-car model; not measured Ciaz tire data.
namespace VehicleDynamics {
inline double Limit(double v,double lo,double hi){return std::max(lo,std::min(v,hi));}
inline double Ackermann(double steer,double side,double wheelbase=2.65,double halfTrack=.73){
 const double angle=Limit(steer,-1,1)*34.*3.141592653589793/180.;
 if(std::abs(angle)<1e-6)return 0;
 const double radius=wheelbase/std::tan(std::abs(angle));
 const bool inner=(angle>0)==(side>0);
 return std::copysign(std::atan(wheelbase/(radius+(inner?-halfTrack:halfTrack))),angle);
}
inline double TireEnvelopeLength(double hitDistance,double longitudinalOffset,double radius=.3065){
 return hitDistance-std::sqrt(std::max(0.,radius*radius-longitudinalOffset*longitudinalOffset));
}
// Beta 1.7.8: the two shoulder probes move the contact point sideways only as
// fast as the tire actually loses central support. Picking the lowest probe
// outright moved the 2.7 kN wheel load by +/-8 cm on a 0.01 degree roll, which
// kicked the chassis and kept it rocking at rest. Lengths in metres.
inline double ShoulderWeight(double centreLength,double shoulderLength){
 return Limit((centreLength-shoulderLength)/.02,0.,1.);
}
// The one-frame "cancel contact velocity" forces (low-speed lateral hold, brake
// stop and locked-wheel skid) treat each wheel as carrying a quarter of the
// car. A contact patch sits well below the centre of mass, so the same force
// also rolls the body and the real effective mass is smaller: at full gain the
// correction overshoots and rings. Half gain stays stable for roll inertias
// from 200 to 1000 kg m^2 at any frame rate and still stops the car in a few
// frames. Gravity compensation is not scaled, so slopes still hold.
constexpr double LowSpeedStopGain=.5;
struct SuspensionState {
 bool grounded=false;double previousLength=.25,rate=0;
 void Release(){grounded=false;rate=0;}
 double Step(double length,double initialRate,double dt,double sprungMass,bool front,double stiffnessScale=1.){
  dt=std::max(.001,dt);
  const double raw=grounded?(previousLength-length)/dt:initialRate;
  rate+=(Limit(raw,-3.,3.)-rate)*(1-std::exp(-dt/.035));
  previousLength=length;grounded=true;
  const double compression=.25-length;
  const double spring=(front?32000.:28000.)*stiffnessScale*compression;
  const double damping=(rate>=0?(front?2200.:1900.):(front?3300.:2900.))*std::sqrt(stiffnessScale)*rate;
  const double bump=140000.*std::pow(std::max(0.,compression-.10),1.25);
  // Preload supports the intended static ride height, rather than losing
  // ground clearance to the old zero-preload spring's static sag.
  return Limit(sprungMass*9.81+spring+damping+bump,0.,12000.);
 }
};
// Legacy helper retained for existing core regression coverage.
inline double Suspension(double compression,double velocity){
 return Limit(38000.*std::max(0.,compression)-velocity*(velocity<0?3200.:4400.)+120000.*std::max(0.,compression-.18),0.,16000.);
}
struct TireInput {
 double dt=1./60.,load=2700,mass=275,longSpeed=0,sideSpeed=0;
 double drive=0,brake=0,gravityLong=0,gravitySide=0;
 double corneringScale=1;
 double rearGripRecovery=1; // 0 = just released, 1 = rolling grip restored
 bool rear=false,handbrake=false;
};
struct TireOutput {double longitudinal=0,lateral=0,grip=0;};
inline TireOutput Tire(const TireInput& i){
 TireOutput out;if(i.load<=0 || i.mass<=0)return out;
 const double dt=std::max(.001,i.dt);
 // Mild load sensitivity: doubling load gives less than twice the tire grip.
 const double mu=Limit(1.05*std::pow(2700./std::max(100.,i.load),.08),.8,1.15);
 out.grip=i.load*mu;
 const double speed=std::abs(i.longSpeed);
 const double travelSpeed=std::hypot(i.longSpeed,i.sideSpeed);
 // A locked tire skids against its complete contact-patch velocity. Unlike
 // an unlocked tire, it cannot independently create large cornering force.
 const double kineticBlend=Limit((travelSpeed-.15)/.45,0.,1.);
 const double skidGrip=out.grip*(1.-.28*kineticBlend);
 const double stopMass=i.mass*LowSpeedStopGain;
 double skidLong=-stopMass*i.longSpeed/dt-i.gravityLong;
 double skidSide=-stopMass*i.sideSpeed/dt-i.gravitySide;
 const double skidDemand=std::hypot(skidLong,skidSide);
 if(skidDemand>skidGrip){skidLong*=skidGrip/skidDemand;skidSide*=skidGrip/skidDemand;}
 if(i.rear&&i.handbrake){
  out.longitudinal=skidLong;out.lateral=skidSide;out.grip=skidGrip;return out;
 }
 const double blend=Limit((speed-.5)/2.5,0.,1.);
 const double slip=std::atan2(i.sideSpeed,std::max(speed,.5));
 const double cornering=-(i.rear?47000.:43000.)*i.corneringScale*slip;
 // At parking speed, cancel lateral contact velocity without an explicit
 // velocity snap. The impulse budget prevents a one-frame sign reversal.
 const double stopSide=-i.sideSpeed*stopMass/dt-i.gravitySide;
 out.lateral=stopSide*(1-blend)+cornering*blend;
 if(i.sideSpeed!=0 && out.lateral*i.sideSpeed<0)
  out.lateral=std::copysign(std::min(std::abs(out.lateral),std::abs(stopSide)),out.lateral);
 double drive=i.drive;
 const double rolling=i.load*.012*std::tanh(i.longSpeed/.12);
 const double stopLong=-i.longSpeed*stopMass/dt-i.gravityLong;
 const double brakeCapacity=Limit(i.brake,0.,1.)*(i.rear?4300.:6200.)+(i.handbrake&&i.rear?7000.:0.);
 const double brakeForce=Limit(stopLong-drive+rolling,-brakeCapacity,brakeCapacity);
 out.longitudinal=drive-rolling+brakeForce;
 // Shared friction ellipse: braking/acceleration use some cornering grip.
 const double lateralGrip=out.grip;
 const double usage=std::hypot(out.longitudinal/out.grip,out.lateral/lateralGrip);
 if(usage>1){out.longitudinal/=usage;out.lateral/=usage;}
 if(i.rear){
  const double recovery=Limit(i.rearGripRecovery,0.,1.);
  out.longitudinal=skidLong*(1-recovery)+out.longitudinal*recovery;
  out.lateral=skidSide*(1-recovery)+out.lateral*recovery;
 }
 return out;
}
}
