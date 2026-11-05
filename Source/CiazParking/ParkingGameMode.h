#pragma once
#include "CoreMinimal.h"
#include "InputCoreTypes.h"
#include "GameFramework/GameModeBase.h"
#include "ParkingCore.h"
#include "WheelDevice.h"
#if PLATFORM_ANDROID
#include "ParkingTouch.h"
#endif
#include "ParkingGameMode.generated.h"
class ACiazPawn;
class APlayerController;
class UParkingSave;
class UStaticMeshComponent;
class UStaticMesh;
class UMaterialInstanceDynamic;
struct FParkingLevel {
 FString Name,Hint;
 FVector Spawn=FVector(-1100,0,100),Target=FVector(900,0,0);
 float SpawnYaw=0,TargetYaw=0,Length=550,Width=280;
 FVector2D GroundSize=FVector2D(6000,4400);
 struct FObstacle{FString Asset;FVector P;float Yaw=0;FVector2D Footprint=FVector2D::ZeroVector;};
 TArray<FObstacle> Obstacles;
};
UCLASS()
class CIAZPARKING_API AParkingGameMode : public AGameModeBase {
 GENERATED_BODY()
public:
 AParkingGameMode();
 virtual void BeginPlay() override;
 virtual void Tick(float Delta) override;
 virtual void EndPlay(const EEndPlayReason::Type Reason) override;
 UPROPERTY() TObjectPtr<ACiazPawn> Car;
 UPROPERTY() TObjectPtr<UParkingSave> Save;
 UPROPERTY() TArray<TObjectPtr<AActor>> LevelActors;
 UPROPERTY() TObjectPtr<UMaterialInstanceDynamic> TargetMaterial;
 UPROPERTY() TMap<FString,TObjectPtr<UStaticMesh>> ObstacleMeshes;
 bool ObstacleAssetsReady=false;
 TArray<FParkingLevel> Levels;
 Parking::Rules Rules;
 FWheelDevice Wheel;
 int Level=0;
 // Screen: 0 driving, 1 main, 2 pause, 3 levels, 4 settings, 5 complete, 6 failed, 7 key bindings, 8 graphics, 9 wheel controls, 10 interior camera.
 int Screen=1,ReturnScreen=1;
 static constexpr int HeightActionBase=600;
 static constexpr int SteeringSensitivityActionBase=620;
 static constexpr int MouseSensitivityActionBase=640;
 static constexpr int FOVActionBase=700;
#if PLATFORM_ANDROID
 static constexpr int TouchButtonsAction=630;
 static constexpr int TouchWheelAction=631;
 ParkingTouch::State TouchInput;
#endif
 FString Notice;
 float NoticeTime=0,Time=0;
 bool Calibrating=false,WasWheelConnected=false;
 bool OldButtons[128]={};
 int CaptureAction=-1;
 FString CaptureKey;
 FKey BoundKey(FKey Default) const;
 float CalMin[8]={},CalMax[8]={};
 void SelectVehicle(int32 Index);
 void StartLevel(int Index);
 void SetScreen(int NewScreen);
 void HandleAction(int Action);
 void SaveProgress();
 void ConfigureQuality();
 TArray<int32> GraphicsDraft,GraphicsPrevious;
 double GraphicsDeadline=0;
 bool GraphicsConfirm=false;
 void RevertGraphics();
 void GraphicsPreset(int32 PresetLevel);
 FString GraphicsLabel(int32 Index) const;

 void Collision(AActor* Other,float ImpactSpeed);
 void Toast(const FString& Text);
 void BuildLevel();
 void CreateLevels();
 void LoadObstacles();
 void SpawnObstacle(const FParkingLevel::FObstacle& Obstacle);
 UStaticMeshComponent* Box(FVector Position,FVector Size,FLinearColor Color,bool Collision=true,float Yaw=0);
private:
#if PLATFORM_ANDROID
 void ReadTouchInput(APlayerController& Controller,float Delta);
 void SuspendTouch();
#endif
 void ReadInput(float Delta);
 void CalibrationTick();
};
