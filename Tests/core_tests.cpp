#include "../Source/CiazParking/ParkingCore.h"
#include <cassert>
#include <iostream>
using namespace Parking;
int main(){
 // Stationary hold, speed-dependent return, reverse, active input and frame-rate independence.
 Steering stopped,slow,fast,reverse,fine,coarse,held;
 stopped.angle=slow.angle=fast.angle=reverse.angle=fine.angle=coarse.angle=held.angle=.8;
 stopped.keyboard(5,false,false,false,0);assert(stopped.angle==.8);
 slow.keyboard(1,false,false,false,1);fast.keyboard(1,false,false,false,8);
 assert(fast.angle>0 && fast.angle<slow.angle && slow.angle<.8);
 reverse.keyboard(1,false,false,false,-8);assert(std::abs(reverse.angle-fast.angle)<1e-12);
 for(int i=0;i<120;i++)fine.keyboard(1./120,false,false,false,5);
 for(int i=0;i<30;i++)coarse.keyboard(1./30,false,false,false,5);
 assert(std::abs(fine.angle-coarse.angle)<1e-12);
 held.keyboard(.1,false,true,false,8);assert(held.angle>.8);

 Drive d; assert(d.select(1,0,0));
 for(int i=0;i<1000;i++)d.step(.01,0,0,1,0);
 assert(d.gear>0); // brake cannot select reverse
 assert(!d.select(-1,2,0));assert(d.select(0,0,0));assert(d.select(-1,0,0));
 for(int i=0;i<30;i++){d.step(.01,0,1,0,0);} assert(d.step(.01,0,1,0,0)<0);
 d.setMode(Mode::Clutch);assert(!d.select(1,0,0));assert(d.select(1,0,1));
 for(int i=0;i<200;i++)d.step(.01,0,0,0,0);
 assert(!d.running);assert(!d.restart(0,0));assert(d.restart(0,1));
 d.setMode(Mode::Sequential);assert(d.shift(1,0,0));assert(d.gear==1);
 Steering s;s.keyboard(1,false,true,false);double a=s.angle;
 s.keyboard(10,false,false,false);assert(s.angle==a);
 s.keyboard(1,true,false,false);assert(std::abs(s.angle)<1e-8);
 s.keyboard(1,true,false,false);s.keyboard(2,false,false,true);assert(s.angle==0);
 Rules r;assert(r.contact(1,0,.5));assert(!r.contact(1,.1,.5));assert(!r.contact(1,.2,.5));
 assert(r.contact(1,.6,.5));assert(r.contact(2,.7,.5));assert(r.failed&&r.collisions==3);
 r.park(3,true,0,false);assert(!r.complete);
 r.reset();r.park(1,true,0,false);r.park(.1,true,.1,false);assert(r.held==0);
 r.park(2.1,true,0,false);assert(r.complete);
 assert(fits({0,0},0,{0,0},0,5.5,2.7));
 assert(!fits({1,0},0,{0,0},0,5.5,2.7));
 assert(!fits({0,0},3.14159,{0,0},0,5.5,2.7));
 assert(fits({5,7},1.2,{5,7},1.2,5.5,2.7));
 assert(!fits({0,0},.3,{0,0},0,5.5,2.7));
 // No idle propulsion in either direction or any transmission mode.
 for(auto mode:{Mode::Automatic,Mode::Sequential,Mode::Clutch})for(int gear:{-1,1}){
  Drive idle;idle.mode=mode;idle.gear=gear;
  assert(idle.step(.01,0,0,0,0)==0);
  Drive power;power.mode=mode;power.gear=gear;
  assert(power.step(.01,0,.5,0,0)*gear>0);
 }
 Steering combined,stationary,freeReturn;
 combined.angle=stationary.angle=freeReturn.angle=-.8;
 combined.keyboard(.1,false,true,false,8);
 stationary.keyboard(.1,false,true,false,0);
 freeReturn.keyboard(.1,false,false,false,8);
 assert(combined.angle>stationary.angle && combined.angle>freeReturn.angle);
 fine.angle=coarse.angle=-.3;
 coarse.keyboard(1,false,true,false,8);
 for(int n=0;n<100;++n)fine.keyboard(.01,false,true,false,8);
 assert(std::abs(fine.angle-coarse.angle)<1e-9);
 Drive coasting;coasting.gear=1;assert(coasting.step(.01,2,0,0,0)<0);
 coasting.gear=-1;assert(coasting.step(.01,-2,0,0,0)>0);
 // Toggle persists through a held key and its release; Hold does not latch.
 bool brake=false;
 brake=HandbrakeInput(brake,false,true,true);assert(brake);
 brake=HandbrakeInput(brake,false,false,true);assert(brake);
 brake=HandbrakeInput(brake,false,false,false);assert(brake);
 brake=HandbrakeInput(brake,false,true,true);assert(!brake);
 brake=HandbrakeInput(brake,true,true,true);assert(brake);
 brake=HandbrakeInput(brake,true,false,true);assert(brake);
 brake=HandbrakeInput(brake,true,false,false);assert(!brake);
 assert(!HandbrakeInput(true,true,false,false)); // Reset/resume clears a released hold.
 std::cout<<"PASS: automatic direction, shift guards, clutch stall/restart, steering hold, collision episodes, parking bounds and completion.\n";
}
