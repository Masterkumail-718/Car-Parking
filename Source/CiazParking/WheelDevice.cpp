#include "WheelDevice.h"
#if PLATFORM_WINDOWS
#include "HAL/PlatformTime.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include <windows.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "Windows/HideWindowsPlatformTypes.h"
struct FWheelDevice::FImpl {
 IDirectInput8W* Input=nullptr;
 IDirectInputDevice8W* Device=nullptr;
 IDirectInputEffect* Effect=nullptr;
 GUID Instance={}; bool Found=false; FString Label;
 bool RestoreAutoCenter=false;DWORD OriginalAutoCenter=DIPROPAUTOCENTER_ON;
 static BOOL CALLBACK Enum(const DIDEVICEINSTANCEW* D,VOID* Context){
  auto* P=static_cast<FImpl*>(Context);
  // Thrustmaster USB vendor ID. No firmware-version assumptions.
  if(LOWORD(D->guidProduct.Data1)!=0x044f)return DIENUM_CONTINUE;
  P->Instance=D->guidInstance;P->Found=true;P->Label=FString(D->tszProductName);
  return DIENUM_STOP;
 }
 static BOOL CALLBACK Axis(const DIDEVICEOBJECTINSTANCEW* O,VOID* Context){
  if(O->dwType&DIDFT_AXIS){
   auto* D=static_cast<IDirectInputDevice8W*>(Context);
   DIPROPRANGE R={};R.diph.dwSize=sizeof(R);R.diph.dwHeaderSize=sizeof(R.diph);
   R.diph.dwHow=DIPH_BYID;R.diph.dwObj=O->dwType;R.lMin=0;R.lMax=65535;
   D->SetProperty(DIPROP_RANGE,&R.diph);
  }return DIENUM_CONTINUE;
 }
};
#else
struct FWheelDevice::FImpl {};
#endif
FWheelDevice::FWheelDevice():Impl(MakeUnique<FImpl>()) {}
FWheelDevice::~FWheelDevice(){Disconnect();}
void FWheelDevice::Disconnect(){
 SetForce(0);
#if PLATFORM_WINDOWS
 if(Impl->Effect){Impl->Effect->Stop();Impl->Effect->Release();Impl->Effect=nullptr;}
 if(Impl->Device&&Impl->RestoreAutoCenter){
  DIPROPDWORD Auto={};Auto.diph.dwSize=sizeof(Auto);Auto.diph.dwHeaderSize=sizeof(Auto.diph);Auto.diph.dwHow=DIPH_DEVICE;Auto.dwData=Impl->OriginalAutoCenter;
  Impl->Device->SetProperty(DIPROP_AUTOCENTER,&Auto.diph);Impl->RestoreAutoCenter=false;
 }
 if(Impl->Device){Impl->Device->Unacquire();Impl->Device->Release();Impl->Device=nullptr;}
 if(Impl->Input){Impl->Input->Release();Impl->Input=nullptr;}
 Impl->Found=false;
#endif
 bConnected=bHasFF=false;
 FMemory::Memzero(Buttons,sizeof(Buttons));FMemory::Memzero(Axes,sizeof(Axes));Name.Empty();
}
bool FWheelDevice::Connect(){
#if PLATFORM_WINDOWS
 Disconnect();
 auto Fail=[this](){Disconnect();return false;};
 if(FAILED(DirectInput8Create(GetModuleHandleW(nullptr),DIRECTINPUT_VERSION,IID_IDirectInput8W,
  reinterpret_cast<void**>(&Impl->Input),nullptr)))return Fail();
 Impl->Input->EnumDevices(DI8DEVCLASS_GAMECTRL,&FImpl::Enum,Impl.Get(),DIEDFL_ATTACHEDONLY);
 if(!Impl->Found)return Fail();
 if(FAILED(Impl->Input->CreateDevice(Impl->Instance,&Impl->Device,nullptr)))return Fail();
 if(FAILED(Impl->Device->SetDataFormat(&c_dfDIJoystick2)))return Fail();
 HWND Window=GetActiveWindow();
 if(!Window)return Fail();
 bool Exclusive=SUCCEEDED(Impl->Device->SetCooperativeLevel(Window,DISCL_EXCLUSIVE|DISCL_FOREGROUND));
 if(!Exclusive&&FAILED(Impl->Device->SetCooperativeLevel(Window,DISCL_NONEXCLUSIVE|DISCL_FOREGROUND)))return Fail();
 Impl->Device->EnumObjects(&FImpl::Axis,Impl->Device,DIDFT_AXIS);
 if(FAILED(Impl->Device->Acquire()))return Fail();
 if(Exclusive){
  DIPROPDWORD Auto={};Auto.diph.dwSize=sizeof(Auto);Auto.diph.dwHeaderSize=sizeof(Auto.diph);
  Auto.diph.dwHow=DIPH_DEVICE;
  if(SUCCEEDED(Impl->Device->GetProperty(DIPROP_AUTOCENTER,&Auto.diph))){
   Impl->OriginalAutoCenter=Auto.dwData;Auto.dwData=DIPROPAUTOCENTER_OFF;
   Impl->RestoreAutoCenter=SUCCEEDED(Impl->Device->SetProperty(DIPROP_AUTOCENTER,&Auto.diph));
  }
  // A one-axis Cartesian force needs a nonzero direction vector.
  DWORD Axis=DIJOFS_X;LONG Direction=DI_FFNOMINALMAX;DICONSTANTFORCE Force={0};
  DIEFFECT E={};E.dwSize=sizeof(E);E.dwFlags=DIEFF_CARTESIAN|DIEFF_OBJECTOFFSETS;
  E.dwDuration=INFINITE;E.dwGain=DI_FFNOMINALMAX;E.dwTriggerButton=DIEB_NOTRIGGER;
  E.cAxes=1;E.rgdwAxes=&Axis;E.rglDirection=&Direction;
  E.cbTypeSpecificParams=sizeof(Force);E.lpvTypeSpecificParams=&Force;
  bHasFF=SUCCEEDED(Impl->Device->CreateEffect(GUID_ConstantForce,&E,&Impl->Effect,nullptr));
  if(!bHasFF&&Impl->RestoreAutoCenter){Auto.dwData=Impl->OriginalAutoCenter;Impl->Device->SetProperty(DIPROP_AUTOCENTER,&Auto.diph);Impl->RestoreAutoCenter=false;}
 }
 Name=Impl->Label;bConnected=true;return true;
#else
 return false;
#endif
}
bool FWheelDevice::Poll(){
#if PLATFORM_WINDOWS
 if(!bConnected){
  const double Now=FPlatformTime::Seconds();
  if(Now-LastTry<2)return false;
  LastTry=Now;if(!Connect())return false;
 }
 if(FAILED(Impl->Device->Poll())){
  SetForce(0);Impl->Device->Acquire();
  if(FAILED(Impl->Device->Poll())){Disconnect();return false;}
 }
 DIJOYSTATE2 S={};
 if(FAILED(Impl->Device->GetDeviceState(sizeof(S),&S))){Disconnect();return false;}
 LONG Values[]={S.lX,S.lY,S.lZ,S.lRx,S.lRy,S.lRz,S.rglSlider[0],S.rglSlider[1]};
 for(int i=0;i<8;i++)Axes[i]=FMath::Clamp(Values[i]/65535.f,0.f,1.f);
 for(int i=0;i<128;i++)Buttons[i]=(S.rgbButtons[i]&0x80)!=0;
 return true;
#else
 return false;
#endif
}
void FWheelDevice::SetForce(float Force){
#if PLATFORM_WINDOWS
 if(!Impl->Effect)return;
 if(!FMath::IsFinite(Force))Force=0;
 DWORD PID=0;GetWindowThreadProcessId(GetForegroundWindow(),&PID);
 if(PID!=GetCurrentProcessId())Force=0;
 if(FMath::Abs(Force)<.001f){Impl->Effect->Stop();return;}
 DICONSTANTFORCE C={static_cast<LONG>(FMath::Clamp(Force,-.35f,.35f)*DI_FFNOMINALMAX)};
 DIEFFECT E={};E.dwSize=sizeof(E);E.cbTypeSpecificParams=sizeof(C);E.lpvTypeSpecificParams=&C;
 Impl->Effect->SetParameters(&E,DIEP_TYPESPECIFICPARAMS|DIEP_START);
#endif
}
