// Beta 1.7.8: a parked car must stay still. Portable rigid-body harness that
// mirrors ACiazPawn::Physics (nine probes per wheel, per-corner suspension,
// axle transfer, tire forces, Chaos-like substeps with a constant force) on a
// flat plane, using the project's real VehicleDynamics.h and ParkingCore.h.
// It is NOT Unreal: chassis inertia is estimated, so the sweep covers a wide
// range. A negative control confirms the harness still reproduces the 1.7.7
// rocking, otherwise a passing run would prove nothing.
#include "VehicleDynamics.h"
#include "ParkingCore.h"
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
namespace {
constexpr double Pi=3.14159265358979323846;
struct V{double x=0,y=0,z=0;};
V operator+(V a,V b){return{a.x+b.x,a.y+b.y,a.z+b.z};}
V operator-(V a,V b){return{a.x-b.x,a.y-b.y,a.z-b.z};}
V operator*(V a,double s){return{a.x*s,a.y*s,a.z*s};}
double dot(V a,V b){return a.x*b.x+a.y*b.y+a.z*b.z;}
V cross(V a,V b){return{a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x};}
double len(V a){return std::sqrt(dot(a,a));}
V norm(V a){const double l=len(a);return l>1e-12?a*(1/l):V{};}
struct Q{double w=1,x=0,y=0,z=0;};
Q qmul(Q a,Q b){return{a.w*b.w-a.x*b.x-a.y*b.y-a.z*b.z,a.w*b.x+a.x*b.w+a.y*b.z-a.z*b.y,a.w*b.y-a.x*b.z+a.y*b.w+a.z*b.x,a.w*b.z+a.x*b.y-a.y*b.x+a.z*b.w};}
V rot(Q q,V v){const V u{q.x,q.y,q.z};const V t=cross(u,v)*2;return v+t*q.w+cross(u,t);}
Q qnorm(Q q){const double l=std::sqrt(q.w*q.w+q.x*q.x+q.y*q.y+q.z*q.z);return{q.w/l,q.x/l,q.y/l,q.z/l};}
Q qconj(Q q){return{q.w,-q.x,-q.y,-q.z};}

struct Car{
 double mass=1100,front=.55,radius=.3065,scale=1,corner=1;bool swift=false;
 V com{.20,0,-.20},inertia{500,2000,2200};
 V wheel[4]={{1.3856,-.7288,-.5134},{1.3856,.7286,-.5134},{-1.2624,-.7288,-.5134},{-1.2624,.7286,-.5134}};
 bool handbrake=true;double brake=0;int gear=0;
};
Car Swift(){Car c;c.mass=930;c.front=.61;c.radius=.30495;c.swift=true;c.corner=.84;c.scale=.76;c.com={.168,0,-.28};c.inertia={420,1500,1700};
 c.wheel[0]={1.1229,-.7462,-.495};c.wheel[1]={1.1229,.7462,-.495};c.wheel[2]={-1.3257,-.7462,-.495};c.wheel[3]={-1.3257,.7462,-.495};return c;}
struct Out{double maxAngle=0,maxSpeed=0,drift=0,hold=0;};
struct Mode{bool blend=true,legacyStop=false;};

Out Rest(const Car& c,Mode mode,double fps,bool jitter,unsigned seed,double seconds=10){
 srand(seed);
 V pos{0,0,.8165+.03};Q q;V v,w,start;
 VehicleDynamics::SuspensionState S[4];
 Parking::Drive drive;drive.swift=c.swift;drive.tireRadius=c.radius;drive.gear=c.gear;
 double t=0,recovery=0,held=0;int samples=0;Out out;const double g=-9.80665;
 while(t<seconds){
  double dt=1./fps;if(jitter)dt*=.6+.8*(rand()/double(RAND_MAX));
  recovery=c.handbrake?0.:std::min(1.,recovery+dt/.22);
  const V up=rot(q,{0,0,1}),fwd=rot(q,{1,0,0});
  V com=pos+rot(q,c.com);
  double driveForce=0;for(double rem=dt;rem>0;){const double step=std::min(rem,1./120);driveForce+=drive.step(step,dot(v,fwd),0,c.brake,0)*step/dt;rem-=step;}
  struct Contact{bool grounded=false;V point,normal,forward,right,velocity;double compression=0,load=0;}k[4];
  for(int i=0;i<4;++i){
   const V wr=norm(cross(up,fwd));const V mount=pos+rot(q,c.wheel[i]+V{0,0,.25});
   double best=.37,bestOffset=0,centre=1e9,shoulder[2]={1e9,1e9};V bestPoint,centrePoint,shoulderPoint[2];int bestProbe=-1;bool supported=false;
   const double offsets[]={-.95,-.75,-.45,0,.45,.75,.95,0,0};
   for(int p=0;p<9;++p){
    const double o=offsets[p]*c.radius,side=p==7?-.08:(p==8?.08:0);
    const V s=mount+fwd*o+wr*side;const double d=s.z/up.z;
    if(!(d>=0&&d<=.37+c.radius)||up.z<.45)continue;
    const double L=VehicleDynamics::TireEnvelopeLength(d,o,c.radius);const V pt=s-up*d;
    if(p==3){centre=L;centrePoint=pt;}else if(p>=7){shoulder[p-7]=L;shoulderPoint[p-7]=pt;}
    if(L<best){best=L;bestPoint=pt;bestOffset=o;bestProbe=p;supported=true;}
   }
   if(!supported){S[i].Release();continue;}
   if(mode.blend&&(bestProbe==3||bestProbe>=7)&&centre<1e8){
    V blended=centrePoint;
    for(int s=0;s<2;++s)if(shoulder[s]<1e8)blended=blended+(shoulderPoint[s]-centrePoint)*VehicleDynamics::ShoulderWeight(centre,shoulder[s]);
    bestPoint=blended;
   }
   const double L=std::max(.05,std::min(best,.37));
   k[i].grounded=true;k[i].point=bestPoint;
   k[i].normal=std::fabs(bestOffset)<.0001?V{0,0,1}:norm(up*std::sqrt(std::max(0.,c.radius*c.radius-bestOffset*bestOffset))-fwd*bestOffset);
   k[i].compression=.25-L;k[i].velocity=v+cross(w,bestPoint-com);
   k[i].load=S[i].Step(L,-dot(k[i].velocity,up),dt,c.mass*(i<2?c.front:1-c.front)*.5,i<2,c.scale);
   k[i].forward=norm(fwd-k[i].normal*dot(fwd,k[i].normal));k[i].right=norm(cross(k[i].normal,k[i].forward));
  }
  for(int a=0;a<2;++a){auto&l=k[a*2];auto&r=k[a*2+1];
   if(l.grounded&&r.grounded){double tr=(l.compression-r.compression)*(a==0?6500.:4500.)*c.scale;tr=std::max(-l.load,std::min(tr,r.load));l.load+=tr;r.load-=tr;}}
  V force,torque;
  for(int i=0;i<4;++i){if(!k[i].grounded)continue;
   const double normalLoad=k[i].load/std::max(.3,dot(k[i].normal,up));
   VehicleDynamics::TireInput in;in.dt=dt;in.load=normalLoad;
   const double share=c.mass*(i<2?c.front:1-c.front)*.5;
   in.mass=mode.legacyStop?share/VehicleDynamics::LowSpeedStopGain:share; // legacy = full one-frame stop
   in.longSpeed=dot(k[i].velocity,k[i].forward);in.sideSpeed=dot(k[i].velocity,k[i].right);
   in.drive=i<2?driveForce*.5:0;in.brake=c.brake;in.rear=i>=2;in.handbrake=c.handbrake;in.rearGripRecovery=recovery;in.corneringScale=c.corner;
   const V G{0,0,g};in.gravityLong=dot(G,k[i].forward)*share;in.gravitySide=dot(G,k[i].right)*share;
   const auto tire=VehicleDynamics::Tire(in);
   const V f=k[i].normal*normalLoad+k[i].forward*tire.longitudinal+k[i].right*tire.lateral;
   force=force+f;torque=torque+cross(k[i].point-com,f);
  }
  force=force-v*len(v)*.5*1.225*.3*2.2;
  const int sub=std::max(1,std::min(12,int(std::ceil(dt/.008333333))));const double h=dt/sub;
  for(int s=0;s<sub;++s){
   v=v+(force*(1/c.mass)+V{0,0,g})*h;
   V wl=rot(qconj(q),w);const V tl=rot(qconj(q),torque);
   const V iw{c.inertia.x*wl.x,c.inertia.y*wl.y,c.inertia.z*wl.z};const V gyro=cross(wl,iw);
   wl=wl+V{(tl.x-gyro.x)/c.inertia.x,(tl.y-gyro.y)/c.inertia.y,(tl.z-gyro.z)/c.inertia.z}*h;w=rot(q,wl);
   v=v*(1/(1+.06*h));w=w*(1/(1+.45*h));
   com=com+v*h;const Q dq{0,w.x*h*.5,w.y*h*.5,w.z*h*.5};const Q d=qmul(dq,q);q=qnorm(Q{q.w+d.w,q.x+d.x,q.y+d.y,q.z+d.z});
   pos=com-rot(q,c.com);
  }
  t+=dt;
  if(t>3){
   if(!samples++)start=pos;
   const double angle=len(w)*180/Pi;
   out.maxAngle=std::max(out.maxAngle,angle);out.maxSpeed=std::max(out.maxSpeed,len(v));
   held=(len(v)<.04&&angle<1.5)?held+dt:0;out.hold=std::max(out.hold,held); // same limits as AParkingGameMode
  }
 }
 out.drift=len(V{pos.x-start.x,pos.y-start.y,0});return out;
}
}
int main(){
 // Shoulder blend is continuous and bounded.
 assert(VehicleDynamics::ShoulderWeight(.10,.10)==0&&VehicleDynamics::ShoulderWeight(.10,.12)==0);
 assert(VehicleDynamics::ShoulderWeight(.10,.08)==1&&VehicleDynamics::ShoulderWeight(.10,.01)==1);
 double previous=0;for(double d=0;d<=.03;d+=.0005){const double wt=VehicleDynamics::ShoulderWeight(.10,.10-d);assert(wt>=previous&&wt-previous<=.0251);previous=wt;}
 assert(VehicleDynamics::ShoulderWeight(.10,.0999)<.01); // a 0.1 mm difference moves the load < 0.1 cm
 // A parked car stays parked for every combination, both cars, a wide inertia range.
 int runs=0;double worstAngle=0,worstSpeed=0,worstDrift=0;
 for(int car=0;car<2;++car)for(double ix:{200.,300.,500.,1000.})
  for(double fps:{30.,45.,60.,90.,120.,144.,240.})for(int jitter=0;jitter<2;++jitter)
   for(int handbrake=0;handbrake<2;++handbrake)for(int brake=0;brake<2;++brake)for(int gear=0;gear<2;++gear){
    Car c=car?Swift():Car();c.inertia.x=ix*(car?.85:1);c.handbrake=handbrake;c.brake=brake;c.gear=gear;
    const Out r=Rest(c,Mode{},fps,jitter,5+jitter);++runs;
    worstAngle=std::max(worstAngle,r.maxAngle);worstSpeed=std::max(worstSpeed,r.maxSpeed);worstDrift=std::max(worstDrift,r.drift);
    assert(r.hold>=2);assert(r.maxAngle<.1);assert(r.maxSpeed<.01);assert(r.drift<.02);
   }
 // Negative control: the 1.7.7 behaviour (snap contact point, full-gain stop) must still rock.
 Car old;Mode legacy;legacy.blend=false;legacy.legacyStop=true;
 const Out before=Rest(old,legacy,60,true,5);
 assert(before.maxAngle>1.5&&before.hold<2);
 // Each fix alone is insufficient in the harness: contact blend fixes the nominal car, the gain fixes low inertia.
 Car light;light.inertia.x=250;Mode blendOnly;blendOnly.legacyStop=true;
 assert(Rest(light,blendOnly,60,true,5).hold<2);
 Mode gainOnly;gainOnly.blend=false;
 assert(Rest(old,gainOnly,60,true,5).maxAngle>.5);
 std::printf("PASS rest stability: %d parked-car runs (both cars, 30-240 fps, jitter, handbrake/brake/gear, Ixx 200-1000): worst %.4f deg/s, %.5f m/s, %.4f m drift; 1.7.7 control rocks at %.1f deg/s.\n",runs,worstAngle,worstSpeed,worstDrift,before.maxAngle);
}
