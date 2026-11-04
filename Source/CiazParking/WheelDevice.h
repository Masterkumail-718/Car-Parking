#pragma once
#include "CoreMinimal.h"
class FWheelDevice {
public:
 FWheelDevice(); ~FWheelDevice();
 bool Poll();
 void SetForce(float Force);
 void Disconnect();
 bool IsConnected() const {return bConnected;}
 bool HasForceFeedback() const {return bHasFF;}
 FString Name;
 float Axes[8]={}; bool Buttons[128]={};
private:
 struct FImpl; TUniquePtr<FImpl> Impl;
 bool bConnected=false,bHasFF=false;
 double LastTry=-100;
 bool Connect();
};
