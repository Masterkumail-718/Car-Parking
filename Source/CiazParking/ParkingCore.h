#pragma once
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <unordered_map>

// Engine-independent rules. Distances in metres, time in seconds, force in N.
namespace Parking {
inline double clamp(double v,double lo,double hi){return std::max(lo,std::min(v,hi));}
inline double approach(double a,double b,double step){return a<b?std::min(b,a+step):std::max(b,a-step);}
inline bool SteeringCalibrationValid(double minimum,double maximum,double rest){
 const double range=maximum-minimum;
 return std::isfinite(minimum)&&std::isfinite(maximum)&&std::isfinite(rest)&&range>=.3&&rest>=minimum+range*.35&&rest<=minimum+range*.65;
}
inline bool PedalAtRest(double minimum,double maximum,double rest){
 const double range=maximum-minimum;
 return std::isfinite(minimum)&&std::isfinite(maximum)&&std::isfinite(rest)&&range>=.3&&rest>=minimum&&rest<=maximum&&(rest<=minimum+range*.1||rest>=maximum-range*.1);
}
enum class Mode : int { Automatic, Sequential, Clutch };
inline bool HandbrakeInput(bool current,bool hold,bool pressed,bool down){
 return hold?down:(pressed?!current:current);
}
// Design target: 110 mechanical horsepower at the crank, not wheel horsepower.
inline double EngineTorque(double rpm){
 constexpr double peakWatts=110.*745.699871582;
 const double revs[]={850,1500,2500,3500,4200,5000,6000,6500};
 const double torque[]={80,105,130,143,145,142,peakWatts/(6000.*2.*3.141592653589793/60.),105};
 rpm=clamp(rpm,850,6500);
 for(int i=1;i<8;++i)if(rpm<=revs[i]){
  const double t=(rpm-revs[i-1])/(revs[i]-revs[i-1]);
  return torque[i-1]+(torque[i]-torque[i-1])*t;
 }
 return torque[7];
}
inline double SwiftTorque(double rpm){
 const double revs[]={850,1500,2500,3500,4200,5000,6000,6500};
 const double torque[]={62,80,99,110,113,108,61000./(6000.*2.*3.141592653589793/60.),80};
 rpm=clamp(rpm,850,6500);
 for(int i=1;i<8;++i)if(rpm<=revs[i])return torque[i-1]+(torque[i]-torque[i-1])*(rpm-revs[i-1])/(revs[i]-revs[i-1]);
 return torque[7];
}
struct Drive {
 bool swift=false;
 double tireRadius=.308;

 Mode mode=Mode::Automatic;
 int gear=0;
 bool running=true;
 double rpm=850, stallTime=0, shiftTimer=0;
 void reset(){gear=0;running=true;rpm=850;stallTime=shiftTimer=0;}
 bool select(int next,double speed,double clutch){
  next=std::max(-1,std::min(5,next));
  if((next<0 && speed>.2)||(next>0 && speed<-.2))return false;
  if(next*gear<0 && std::abs(speed)>.2)return false;
  if(mode==Mode::Clutch && next!=0 && clutch<.8)return false;
  if(next!=gear)shiftTimer=.18;
  gear=next;return true;
 }
 bool shift(int delta,double speed,double clutch){
  if(mode==Mode::Automatic)return false;
  return select(gear+(delta>0?1:-1),speed,clutch);
 }
 void setMode(Mode m){mode=m;reset();}
 bool restart(double speed,double clutch){
  if(gear!=0 && clutch<.8)return false;
  if(std::abs(speed)>1)return false;
  running=true;rpm=850;stallTime=0;return true;
 }
 double step(double dt,double speed,double throttle,double /*brake*/,double clutch){
  dt=clamp(dt,0,.05);throttle=clamp(throttle,0,1);clutch=clamp(clutch,0,1);
  shiftTimer=std::max(0.,shiftTimer-dt);
  // The automatic selector is never changed by brake input.
  const double wheelRPM=std::abs(speed)/(2*3.141592653589793*tireRadius)*60.;
  const double ciazRatios[]={3.545,3.545,1.904,1.310,.969,.815};
  const double swiftRatios[]={3.272,3.545,1.904,1.240,.914,.717};
  const double* ratios=swift?swiftRatios:ciazRatios;
  const double finalDrive=swift?4.388:4.105;
  if(mode==Mode::Automatic && gear>0){
   const double coupled=wheelRPM*ratios[gear]*finalDrive;
   if(shiftTimer==0 && coupled>2800+throttle*3400 && gear<5){++gear;shiftTimer=.25;}
   else if(shiftTimer==0 && coupled<1000+throttle*900 && gear>1){--gear;shiftTimer=.25;}
  }
  if(!running){rpm=approach(rpm,0,dt*2500);return 0;}
  const double ratio=gear<0?ratios[0]:(gear>0?ratios[gear]:0);
  double coupling=mode==Mode::Clutch?clamp((.88-clutch)/.62,0,1):1.;
  if(shiftTimer>0 && mode!=Mode::Clutch)coupling=0;
  double wanted=850+throttle*5200;
  if(gear!=0){
   const double locked=wheelRPM*ratio*finalDrive;
   if(mode==Mode::Clutch) wanted=wanted*(1-coupling)+locked*coupling;
   else wanted=std::max(850.+throttle*1000,locked);
  }
  rpm=approach(rpm,wanted,dt*5000);
  rpm=clamp(rpm,0,6500);
  if(mode==Mode::Clutch && gear!=0 && coupling>.85 && rpm<480)stallTime+=dt;
  else stallTime=0;
  if(stallTime>.45){running=false;return 0;}
  if(gear==0)return 0;
  const double torque=swift?SwiftTorque(rpm):EngineTorque(rpm);
  double demand=throttle; // Idle RPM does not request wheel torque.
  if(rpm>=6400)demand=0;
  double force=torque*demand*ratio*finalDrive*.86/tireRadius*coupling;
  // Engine braking follows travel direction only while coupled.
  force*=gear<0?-1:1;
  force-=(1-throttle)*140*coupling*std::tanh(speed/.5);
  return force;
 }
};
struct Steering {
 double angle=0; // normalised -1..1; positive means right
 void keyboard(double dt,bool left,bool right,bool center,double speed=0){
  if(center)angle=approach(angle,0,dt*1.2);
  else {
   const double input=(right?1.:0.)-(left?1.:0.);
   const double rate=clamp((std::abs(speed)-.05)*.22,0.,1.6);
   if(input==0)angle*=std::exp(-rate*dt);
   else if(angle*input<0 && rate>0){
    // Integrate input + return together until crossing centre; beyond it,
    // only the key turns the wheel. This is independent of frame rate.
    const double velocity=input*.65;
    const double crossing=std::log(1-rate*angle/velocity)/rate;
    if(dt>=crossing)angle=velocity*(dt-crossing);
    else angle=angle*std::exp(-rate*dt)+velocity/rate*(1-std::exp(-rate*dt));
   }else angle+=input*.65*dt;
   angle=clamp(angle,-1,1);
   if(input==0 && rate>0 && std::abs(angle)<.0001)angle=0;
  }
 }
};
struct Vec2 {double x=0,y=0;};
inline Vec2 rotate(Vec2 a,double yaw){return {a.x*std::cos(yaw)-a.y*std::sin(yaw),a.x*std::sin(yaw)+a.y*std::cos(yaw)};}
inline bool fits(Vec2 pos,double yaw,Vec2 target,double targetYaw,double bayLength,double bayWidth,
 double carLength=4.49,double carWidth=1.90,double tolerance=.13962634){
 const double heading=std::remainder(yaw-targetYaw,2*3.141592653589793);
 if(std::abs(heading)>tolerance)return false;
 for(double x:{-carLength/2,carLength/2})for(double y:{-carWidth/2,carWidth/2}){
  Vec2 c=rotate({x,y},yaw); c=rotate({pos.x+c.x-target.x,pos.y+c.y-target.y},-targetYaw);
  if(std::abs(c.x)>bayLength/2 || std::abs(c.y)>bayWidth/2)return false;
 }return true;
}
struct Rules {
 int collisions=0; bool failed=false,complete=false;
 double held=0;
 std::unordered_map<uint64_t,double> lastContact;
 void reset(){*this=Rules{};}
 bool contact(uint64_t id,double time,double impactSpeed){
  if(failed||complete)return false;
  auto it=lastContact.find(id);
  const bool newEpisode=it==lastContact.end() || time-it->second>.30;
  lastContact[id]=time;
  if(!newEpisode || impactSpeed<.12)return false;
  ++collisions;if(collisions>=3){failed=true;held=0;}
  return true;
 }
 bool touching(double time)const{
  for(const auto& p:lastContact)if(time-p.second<.30)return true;
  return false;
 }
 void park(double dt,bool inside,double speed,bool contactActive){
  if(failed||complete)return;
  if(inside && std::abs(speed)<.04 && !contactActive)held+=std::max(0.,dt);else held=0;
  if(held>=2)complete=true;
 }
};
}
