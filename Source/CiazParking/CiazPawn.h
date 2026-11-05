#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ParkingCore.h"
#include "VehicleDynamics.h"
#include "CiazPawn.generated.h"
class UProceduralMeshComponent;
class UMaterialInstanceDynamic;
class USpringArmComponent;
class UCameraComponent;
class UAudioComponent;
class USpotLightComponent;
class USceneCaptureComponent2D;
class UTextureRenderTarget2D;
UCLASS(Config=Game)
class CIAZPARKING_API ACiazPawn : public APawn {
 GENERATED_BODY()
public:
 ACiazPawn();
 int32 VehicleIndex=0;
 float VehicleLength=449,VehicleWidth=190,VehicleMass=1100,WheelRadius=30.65f,FrontWeight=.55f;
 float SuspensionScale=1.f,GaugeSweep[2]={-270.f,-270.f};
 FVector CockpitPosition=FVector(24,36,40),SteerAxis=FVector(.891754,-.023709,-.451899),SteerCentreOffset=FVector(-.973936,-.004798,-.063572);
 FString VehicleFolder() const;
 void ConfigureVehicle();
 void BuildSwiftCollision();
 // Positive offset raises the complete chassis relative to wheel centres.
 static constexpr int32 MaxRideHeightOffsetCm=8;
 UPROPERTY(Config,EditAnywhere,Category="Suspension") float RideHeightOffsetCm=0;
 virtual void BeginPlay() override;
 virtual void Tick(float Delta) override;
 UPROPERTY(VisibleAnywhere) TObjectPtr<UProceduralMeshComponent> Body;
 UPROPERTY() TArray<TObjectPtr<UProceduralMeshComponent>> Visuals;
 UPROPERTY() TArray<TObjectPtr<UMaterialInstanceDynamic>> Materials;
 UPROPERTY() TObjectPtr<USpringArmComponent> Boom;
 UPROPERTY() TObjectPtr<UCameraComponent> Camera;
 UPROPERTY() TArray<TObjectPtr<UProceduralMeshComponent>> GaugeNeedles;
 UPROPERTY() TObjectPtr<UAudioComponent> EngineAudio;
 UPROPERTY() TObjectPtr<UAudioComponent> BeepAudio;
 UPROPERTY() TObjectPtr<UAudioComponent> LoadAudio;
 UPROPERTY() TArray<TObjectPtr<USpotLightComponent>> Headlights;
 UPROPERTY() TArray<TObjectPtr<UMaterialInstanceDynamic>> InstrumentMaterials;
 Parking::Drive Drive;
 Parking::Steering Steering;
 float Throttle=0,Brake=0,Clutch=0;
 bool Handbrake=true,HeadlightsOn=false,Cockpit=false;
 bool Frozen=true,AssetLoaded=false,CollisionReady=false;
 float Speed=0,Slip=0,DriveForce=0;
 float Sensors[6]={300,300,300,300,300,300};
 FVector WheelOffsets[4];
 float WheelTravel[4]={},Spin[4]={};
 void SetFrozen(bool Value);
 void ResetAt(FVector Position,float Yaw);
 void ToggleCamera();
 void MouseLook(float X,float Y,bool LookBack,float Delta);
 void SetInteriorFOV(float Value);
 void SetInteriorCamera(FVector Offset,FRotator Rotation);
 static constexpr float MinInteriorFOV=70.f;
 static constexpr float MaxInteriorFOV=150.f;
 void ApplyCamera();
 void UpdateSensors();
 void ToggleLights();
 void LoadVehicle();
 UFUNCTION() void OnHit(UPrimitiveComponent* HitComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,
  FVector NormalImpulse,const FHitResult& Hit);
private:
 UPROPERTY() TObjectPtr<class UInstancedStaticMeshComponent> SkidMarks;
 TOptional<FVector> PreviousSkidPoint[4];
 int32 NextSkidMark=0;
 void AddSkidMark(int32 Wheel,const FVector& Point);
 UPROPERTY() TArray<TObjectPtr<USceneCaptureComponent2D>> MirrorCaptures;
 UPROPERTY() TArray<TObjectPtr<UTextureRenderTarget2D>> MirrorTargets;
 void AddMirror(UProceduralMeshComponent* Mesh,int32 Index,FVector Pivot);
 void UpdateMirrors(float Delta);
 float MirrorClock=0;
 int32 NextMirror=0,MirrorQuality=-1;
 FVector PausedLinear=FVector::ZeroVector,PausedAngular=FVector::ZeroVector;
 float WheelSteer[4]={};
 float RearGripRecovery=1;
 VehicleDynamics::SuspensionState SuspensionCorners[4];
 float SensorClock=0,BeepClock=0;
 float InteriorFOV=85.f,OrbitIdle=0;
 FVector InteriorCameraOffset=FVector::ZeroVector;
 FRotator InteriorCameraRotation=FRotator::ZeroRotator;
 float ChaseYaw=0,ChasePitch=-24,CockpitYaw=0,CockpitPitch=-5;
 FVector SteeringPivot=FVector::ZeroVector;
 void Physics(float Delta);
 void UpdateWheelVisuals();
 void BuildBodyCollision();
 void UpdateGauges(float Delta);
 FVector GaugeAxes[2]={FVector::ForwardVector,FVector::ForwardVector};
 float GaugeZero[2]={0,0},GaugeValues[2]={0,0};
};
