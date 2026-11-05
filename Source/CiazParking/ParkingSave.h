#pragma once
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ParkingSave.generated.h"
UCLASS()
class CIAZPARKING_API UParkingSave : public USaveGame {
 GENERATED_BODY()
public:
 UPROPERTY() int32 Unlocked=1;
 UPROPERTY() TMap<FString,FString> KeyBindings;
 UPROPERTY() int32 Transmission=0;
 UPROPERTY() int32 Quality=0;
 UPROPERTY() TArray<int32> Graphics;
 UPROPERTY() bool HandbrakeHold=false;
 UPROPERTY() int32 VehicleIndex=0; // Existing saves retain toggle control.
 UPROPERTY() bool WheelEnabled=false;
 UPROPERTY() bool Calibrated=false;
 UPROPERTY() TArray<int32> Axes={0,5,1,6};
 UPROPERTY() TArray<float> Minimum={0,0,0,0};
 UPROPERTY() TArray<float> Maximum={1,1,1,1};
 UPROPERTY() TArray<float> Rest={.5,1,1,1};
 UPROPERTY() TArray<bool> Invert={false,true,true,true};
 UPROPERTY() int32 ShiftUp=1;
 UPROPERTY() int32 ShiftDown=0;
 UPROPERTY() bool Feedback=false;
 UPROPERTY() float FeedbackStrength=.35f;
 UPROPERTY() bool FeedbackInvert=false;
 UPROPERTY() float MasterVolume=.7f;
 UPROPERTY() float InteriorFOV=85.f;
 UPROPERTY() FVector InteriorCameraOffset=FVector::ZeroVector;
 UPROPERTY() FRotator InteriorCameraRotation=FRotator::ZeroRotator;
 UPROPERTY() float RideHeightOffsetCm=-1.f; // Older saves use the pawn's configured height.
 UPROPERTY() int32 KeyboardSteeringSensitivity=3;
 UPROPERTY() int32 MouseSensitivity=3; // Level 3 preserves the original camera speed.
 UPROPERTY() bool AndroidSteeringWheel=false;
};
