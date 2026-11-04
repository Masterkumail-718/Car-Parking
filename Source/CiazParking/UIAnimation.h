#pragma once
#include <algorithm>
namespace ParkingUI {
// Quintic S curve: zero velocity and acceleration at both endpoints.
inline float Ease(float t){t=std::max(0.f,std::min(1.f,t));return t*t*t*(t*(t*6.f-15.f)+10.f);}
struct Tween {
 float Value=0,Start=0,Target=0,Elapsed=0,Duration=.18f;
 void To(float next){if(next!=Target){Start=Value;Target=next;Elapsed=0;}}
 void Tick(float dt){Elapsed=std::min(Duration,Elapsed+std::max(0.f,dt));Value=Start+(Target-Start)*Ease(Elapsed/Duration);}
};
}
