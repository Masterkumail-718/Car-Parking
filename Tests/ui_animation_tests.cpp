#include "../Source/CiazParking/UIAnimation.h"
#include <cassert>
#include <cmath>
#include <iostream>
int main(){
 using namespace ParkingUI;
 assert(Ease(-1)==0 && Ease(0)==0 && Ease(1)==1 && Ease(2)==1);
 assert(std::abs(Ease(.5f)-.5f)<1e-6f);
 float previous=0;
 for(int i=0;i<=1000;++i){float v=Ease(i/1000.f);assert(v>=previous-1e-6f && v>=0 && v<=1.000001f);previous=v;}
 assert(Ease(.001f)/.001f<.001f);
 Tween a,b;a.To(1);b.To(1);a.Tick(.09f);for(int i=0;i<9;++i)b.Tick(.01f);
 assert(std::abs(a.Value-b.Value)<1e-5f);
 float current=a.Value;a.To(0);assert(a.Value==current);a.Tick(.18f);assert(a.Value==0);
 b.Tick(1);assert(b.Value==1);b.To(1);assert(b.Value==1);
 std::cout<<"PASS: S-curve endpoints, monotonicity, frame timing and continuous retargeting.\n";
}
