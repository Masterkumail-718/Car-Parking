#include "ParkingGameMode.h"
#include "HAL/IConsoleManager.h"
#include "CiazPawn.h"
#include "ParkingSave.h"
#include "ParkingHUD.h"
#include "Components/StaticMeshComponent.h"
#include "ProceduralMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/Material.h"
#include "MaterialDomain.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "Engine/PostProcessVolume.h"
#include "Engine/OverlapResult.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/GameUserSettings.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "InputCoreTypes.h"
#include "Sound/SoundWave.h"
#if PLATFORM_ANDROID
#include "Misc/CoreDelegates.h"
#endif

AParkingGameMode::AParkingGameMode(){
 PrimaryActorTick.bCanEverTick=true;PrimaryActorTick.TickGroup=TG_PrePhysics;
 DefaultPawnClass=nullptr;HUDClass=AParkingHUD::StaticClass();
}
void AParkingGameMode::BeginPlay(){
 Super::BeginPlay();
#if PLATFORM_ANDROID
 FCoreDelegates::ApplicationWillDeactivateDelegate.AddUObject(this,&AParkingGameMode::SuspendTouch);
 FCoreDelegates::ApplicationWillEnterBackgroundDelegate.AddUObject(this,&AParkingGameMode::SuspendTouch);
#endif
 Save=Cast<UParkingSave>(UGameplayStatics::LoadGameFromSlot(TEXT("CiazParking"),0));
 if(!Save)Save=Cast<UParkingSave>(UGameplayStatics::CreateSaveGameObject(UParkingSave::StaticClass()));
 CreateLevels();
 Save->Unlocked=FMath::Clamp(Save->Unlocked,1,Levels.Num());Save->Transmission=FMath::Clamp(Save->Transmission,0,2);
 // A partially edited/older save must not index beyond calibration arrays.
 if(Save->Axes.Num()!=4||Save->Minimum.Num()!=4||Save->Maximum.Num()!=4||Save->Rest.Num()!=4||Save->Invert.Num()!=4){
  Save->Axes={0,5,1,6};Save->Minimum={0,0,0,0};Save->Maximum={1,1,1,1};Save->Rest={.5f,1,1,1};Save->Invert={false,true,true,true};Save->Calibrated=false;
 }
 for(int32 Index=0;Index<4;++Index){
  if(Save->Axes[Index]<0||Save->Axes[Index]>7){Save->Axes[Index]=Index;Save->Calibrated=false;}
  if(!FMath::IsFinite(Save->Minimum[Index])||!FMath::IsFinite(Save->Maximum[Index])||!FMath::IsFinite(Save->Rest[Index])||Save->Maximum[Index]-Save->Minimum[Index]<.01f){
   Save->Minimum[Index]=0;Save->Maximum[Index]=1;Save->Rest[Index]=Index==0?.5f:1.f;Save->Calibrated=false;
  }
 }
 // Upgrade uncalibrated legacy defaults for the owner's T248 and T3PA pedals.
 if(!Save->Calibrated && Save->Axes==TArray<int32>({0,1,2,5}))Save->Axes={0,5,1,6};
 TSet<int32> AssignedAxes;for(int32 Axis:Save->Axes)AssignedAxes.Add(Axis);
 if(AssignedAxes.Num()!=4||!Parking::SteeringCalibrationValid(Save->Minimum[0],Save->Maximum[0],Save->Rest[0]))Save->Calibrated=false;
 for(int32 I=1;I<4;++I)if(!Parking::PedalAtRest(Save->Minimum[I],Save->Maximum[I],Save->Rest[I]))Save->Calibrated=false;
 Save->FeedbackStrength=FMath::IsFinite(Save->FeedbackStrength)?FMath::Clamp(Save->FeedbackStrength,0.f,.35f):.35f;
 Save->ShiftUp=FMath::Clamp(Save->ShiftUp,0,127);Save->ShiftDown=FMath::Clamp(Save->ShiftDown,0,127);
 Save->MasterVolume=FMath::IsFinite(Save->MasterVolume)?FMath::Clamp(Save->MasterVolume,0.f,1.f):.7f;
 Save->InteriorFOV=FMath::IsFinite(Save->InteriorFOV)?FMath::Clamp(Save->InteriorFOV,ACiazPawn::MinInteriorFOV,ACiazPawn::MaxInteriorFOV):85.f;
 for(int32 Axis=0;Axis<3;++Axis){
  double& Value=Save->InteriorCameraOffset[Axis];
  Value=FMath::IsFinite(Value)?FMath::Clamp(Value,-60.0,60.0):0.0;
 }
 Save->InteriorCameraRotation.Pitch=FMath::IsFinite(Save->InteriorCameraRotation.Pitch)?FMath::Clamp(Save->InteriorCameraRotation.Pitch,-50.0,65.0):0.0;
 Save->InteriorCameraRotation.Yaw=FMath::IsFinite(Save->InteriorCameraRotation.Yaw)?FMath::Clamp(Save->InteriorCameraRotation.Yaw,-135.0,135.0):0.0;
 Save->InteriorCameraRotation.Roll=0;
 if(!FMath::IsFinite(Save->RideHeightOffsetCm)||Save->RideHeightOffsetCm<0.f)
  Save->RideHeightOffsetCm=GetDefault<ACiazPawn>()->RideHeightOffsetCm;
 Save->RideHeightOffsetCm=FMath::Clamp(Save->RideHeightOffsetCm,0.f,float(ACiazPawn::MaxRideHeightOffsetCm));
 Save->KeyboardSteeringSensitivity=FMath::Clamp(Save->KeyboardSteeringSensitivity,1,5);
 Save->MouseSensitivity=FMath::Clamp(Save->MouseSensitivity,1,5);
 // Short-range world-space SSAO supplies tyre/ground and car/wall contact cues.
 // The saved AO switch remains authoritative, including when post processing is Low.
 if(auto* ContactVolume=GetWorld()->SpawnActor<APostProcessVolume>()){
  ContactVolume->bUnbound=true;
  auto& PP=ContactVolume->Settings;
  PP.bOverride_AmbientOcclusionIntensity=true;PP.AmbientOcclusionIntensity=.85f;
  PP.bOverride_AmbientOcclusionRadius=true;PP.AmbientOcclusionRadius=70.f;
  PP.bOverride_AmbientOcclusionRadiusInWS=true;PP.AmbientOcclusionRadiusInWS=true;
  PP.bOverride_AmbientOcclusionPower=true;PP.AmbientOcclusionPower=1.4f;
  PP.bOverride_AmbientOcclusionQuality=true;PP.AmbientOcclusionQuality=60.f;
 }
 LoadObstacles();ConfigureQuality();
 Save->VehicleIndex=FMath::Clamp(Save->VehicleIndex,0,1);
 Car=GetWorld()->SpawnActorDeferred<ACiazPawn>(ACiazPawn::StaticClass(),FTransform::Identity);
 if(Car){Car->VehicleIndex=Save->VehicleIndex;Car->RideHeightOffsetCm=Save->RideHeightOffsetCm;Car->FinishSpawning(FTransform::Identity);if(auto* PC=GetWorld()->GetFirstPlayerController())PC->Possess(Car);}
 Save->InteriorFOV=FMath::Clamp(Save->InteriorFOV,ACiazPawn::MinInteriorFOV,ACiazPawn::MaxInteriorFOV);
 if(!Car){UE_LOG(LogTemp,Error,TEXT("Could not spawn player car"));return;}
 Car->AddTickPrerequisiteActor(this);
 Car->SetInteriorFOV(Save->InteriorFOV);
 Car->SetInteriorCamera(Save->InteriorCameraOffset,Save->InteriorCameraRotation);
 StartLevel(0);SetScreen(1);
 if(!Car->AssetLoaded)Toast(TEXT("Car assets missing: run SetupProject.cmd, then restart."));
}
void AParkingGameMode::EndPlay(const EEndPlayReason::Type Reason){
#if PLATFORM_ANDROID
 FCoreDelegates::ApplicationWillDeactivateDelegate.RemoveAll(this);
 FCoreDelegates::ApplicationWillEnterBackgroundDelegate.RemoveAll(this);
#endif
 Wheel.Disconnect();Super::EndPlay(Reason);
}
void AParkingGameMode::Toast(const FString& Text){Notice=Text;NoticeTime=5;}
void AParkingGameMode::SaveProgress(){UGameplayStatics::SaveGameToSlot(Save,TEXT("CiazParking"),0);}
namespace {
 const int32 GraphicsCounts[]={4,3,6,2,5,4,4,4,3,4,4,2,2,2};
 const FIntPoint Resolutions[]={FIntPoint(1280,720),FIntPoint(1600,900),FIntPoint(1920,1080),FIntPoint(2560,1440)};
 const float FrameCaps[]={30,60,90,120,144,0};
 const float RenderScales[]={50,67,75,85,100};
 void SetGraphicsCVar(const TCHAR* Name,int32 Value){
  if(auto* Variable=IConsoleManager::Get().FindConsoleVariable(Name))Variable->Set(Value,ECVF_SetByCode);
 }
}
void AParkingGameMode::GraphicsPreset(int32 PresetLevel){
 PresetLevel=FMath::Clamp(PresetLevel,0,3);
 GraphicsDraft={PresetLevel==0?0:2,0,PresetLevel==0?0:1,0,4,PresetLevel,PresetLevel,PresetLevel,PresetLevel==0?1:2,PresetLevel,PresetLevel,1,PresetLevel>0?1:0,1};
}
void AParkingGameMode::ConfigureQuality(){
 auto* Settings=UGameUserSettings::GetGameUserSettings();if(!Settings)return;
 if(Save->Graphics.Num()!=14){GraphicsPreset(Save->Quality==0?0:1);Save->Graphics=GraphicsDraft;}
 auto& V=Save->Graphics;
 for(int32 Index=0;Index<14;++Index)V[Index]=FMath::Clamp(V[Index],0,GraphicsCounts[Index]-1);
 Settings->SetScreenResolution(Resolutions[V[0]]);
 const EWindowMode::Type Modes[]={EWindowMode::Windowed,EWindowMode::WindowedFullscreen,EWindowMode::Fullscreen};
 Settings->SetFullscreenMode(Modes[V[1]]);Settings->SetFrameRateLimit(FrameCaps[V[2]]);
 Settings->SetVSyncEnabled(V[3]!=0);Settings->SetResolutionScaleValueEx(RenderScales[V[4]]);
 Settings->SetViewDistanceQuality(V[5]);Settings->SetTextureQuality(V[6]);Settings->SetShadowQuality(V[7]);
 Settings->SetAntiAliasingQuality(V[8]==0?0:2);Settings->SetVisualEffectQuality(V[9]);Settings->SetPostProcessingQuality(V[10]);
 Settings->ApplySettings(false);
 SetGraphicsCVar(TEXT("t.MaxFPS"),int32(FrameCaps[V[2]]));
 SetGraphicsCVar(TEXT("r.AntiAliasingMethod"),V[8]);
 SetGraphicsCVar(TEXT("r.AmbientOcclusionLevels"),V[11]);
 SetGraphicsCVar(TEXT("r.AmbientOcclusionMaxQuality"),V[11]?60:0);
 // Screen-space contact rays create stippled false wall shadows at distance.
 // Use cascaded shadow maps plus SSAO for stable proximity shading at every AA mode.
 SetGraphicsCVar(TEXT("r.ContactShadows"),0);
 SetGraphicsCVar(TEXT("r.MaxAnisotropy"),V[6]==0?4:(V[6]<2?8:16));
 SetGraphicsCVar(TEXT("r.Shadow.MaxResolution"),V[7]<2?1024:2048);
 SetGraphicsCVar(TEXT("r.BloomQuality"),V[13]?3:0);
 Save->Quality=V[12]; // Mirror rendering budget is now independent of other quality groups.
}
void AParkingGameMode::RevertGraphics(){
 if(!GraphicsConfirm)return;
 Save->Graphics=GraphicsPrevious;GraphicsConfirm=false;ConfigureQuality();
 GraphicsDraft=Save->Graphics;Toast(TEXT("Previous graphics settings restored."));
}
FString AParkingGameMode::GraphicsLabel(int32 Index) const{
 if(GraphicsDraft.Num()!=14)return TEXT("Loading settings");
 const int32 Value=GraphicsDraft[Index];
 const TCHAR* Names[]={TEXT("Resolution"),TEXT("Display mode"),TEXT("Frame-rate cap"),TEXT("VSync"),TEXT("Render scale"),TEXT("View distance"),TEXT("Textures"),TEXT("Shadows"),TEXT("Anti-aliasing"),TEXT("Effects"),TEXT("Post processing"),TEXT("Ambient occlusion"),TEXT("Mirror quality"),TEXT("Bloom")};
 const TCHAR* QualityNames[]={TEXT("Low"),TEXT("Medium"),TEXT("High"),TEXT("Epic")};
 FString ValueLabel;
 if(Index==0)ValueLabel=FString::Printf(TEXT("%d x %d"),Resolutions[Value].X,Resolutions[Value].Y);
 else if(Index==1){const TCHAR* Modes[]={TEXT("Windowed"),TEXT("Borderless"),TEXT("Fullscreen")};ValueLabel=Modes[Value];}
 else if(Index==2)ValueLabel=Value==5?TEXT("Unlimited"):FString::Printf(TEXT("%.0f FPS"),FrameCaps[Value]);
 else if(Index==4)ValueLabel=FString::Printf(TEXT("%.0f%%"),RenderScales[Value]);
 else if(Index==8){const TCHAR* AA[]={TEXT("Off"),TEXT("FXAA"),TEXT("TAA")};ValueLabel=AA[Value];}
 else if(Index==3||Index==11||Index==13)ValueLabel=Value?TEXT("On"):TEXT("Off");
 else if(Index==12)ValueLabel=Value?TEXT("Standard"):TEXT("Performance");
 else ValueLabel=QualityNames[Value];
 return FString(Names[Index])+TEXT(":  ")+ValueLabel;
}
void AParkingGameMode::SetScreen(int S){
 if(Screen==8 && S!=8){RevertGraphics();GraphicsDraft=Save->Graphics;SaveProgress();}
 if(Screen==9 && S!=9){Calibrating=false;CaptureAction=-1;SaveProgress();}
 if(Screen==7 && S!=7)CaptureKey.Empty();
 if(S==8 && Screen!=8)GraphicsDraft=Save->Graphics;
 if(S==0&&(!Car||!Car->AssetLoaded||!ObstacleAssetsReady||!TargetMaterial||Rules.failed||Rules.complete)){Toast(TEXT("Start or retry a level before driving."));return;}
 Screen=S;
#if PLATFORM_ANDROID
 TouchInput.Cancel();
 if(Car){Car->Throttle=0;Car->Brake=0;Car->Clutch=0;}
#endif
 if(Car)Car->SetFrozen(S!=0);
 Wheel.SetForce(0);
 if(auto* PC=GetWorld()->GetFirstPlayerController()){
  PC->bShowMouseCursor=!PLATFORM_ANDROID&&S!=0;
  if(S==0){
   FInputModeGameOnly Mode;Mode.SetConsumeCaptureMouseDown(false);PC->SetInputMode(Mode);
  }else{
   FInputModeGameAndUI Mode;Mode.SetHideCursorDuringCapture(false);
   Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);PC->SetInputMode(Mode);
  }
 }
}
void AParkingGameMode::StartLevel(int I){
 if(!Car||!Car->AssetLoaded){Toast(TEXT("Vehicle assets missing: run SetupProject.cmd."));return;}
 if(!ObstacleAssetsReady){Toast(TEXT("Obstacle assets missing: close the editor and run SetupProject.cmd."));return;}
 if(!Levels.IsValidIndex(I)||I>=Save->Unlocked)return;
 for(AActor* A:LevelActors)if(IsValid(A))A->Destroy();LevelActors.Empty();
 Level=I;Rules.reset();Time=0;BuildLevel();
 Car->ResetAt(Levels[I].Spawn,Levels[I].SpawnYaw);
#if PLATFORM_ANDROID
 Car->Drive.setMode(Parking::Mode::Automatic);
#else
 Car->Drive.setMode(static_cast<Parking::Mode>(Save->Transmission));
#endif
 SetScreen(0);Toast(Levels[I].Hint);
}
UStaticMeshComponent* AParkingGameMode::Box(FVector P,FVector Size,FLinearColor Color,bool Collide,float Yaw){
 auto* A=GetWorld()->SpawnActor<AActor>();LevelActors.Add(A);
 auto* M=NewObject<UStaticMeshComponent>(A);A->SetRootComponent(M);A->AddInstanceComponent(M);
 M->SetMobility(EComponentMobility::Movable);
 M->SetStaticMesh(LoadObject<UStaticMesh>(nullptr,TEXT("/Engine/BasicShapes/Cube.Cube")));
 M->SetCollisionEnabled(Collide?ECollisionEnabled::QueryAndPhysics:ECollisionEnabled::NoCollision);
 M->SetCollisionResponseToAllChannels(ECR_Block);M->SetGenerateOverlapEvents(false);
 M->RegisterComponent();A->SetActorLocationAndRotation(P,FRotator(0,Yaw,0));M->SetWorldScale3D(Size/100);
 if(auto* Base=LoadObject<UMaterialInterface>(nullptr,TEXT("/Game/Materials/M_Solid.M_Solid"))){
  auto* D=UMaterialInstanceDynamic::Create(Base,this);D->SetVectorParameterValue(TEXT("Tint"),Color);
  D->SetScalarParameterValue(TEXT("Roughness"),.85);M->SetMaterial(0,D);
 }
 if(Collide)A->Tags.Add(TEXT("Obstacle"));else M->SetCastShadow(false);
 return M;
}
void AParkingGameMode::BuildLevel(){
 const auto& L=Levels[Level];
 auto* Ground=Box(FVector(0,0,-25),FVector(L.GroundSize.X,L.GroundSize.Y,50),FLinearColor(.055,.065,.075),true);
 if(auto* Asphalt=LoadObject<UMaterialInterface>(nullptr,TEXT("/Game/Materials/M_Asphalt.M_Asphalt")))Ground->SetMaterial(0,Asphalt);
 else UE_LOG(LogTemp,Warning,TEXT("Asphalt material missing: run SetupProject.cmd"));
 Ground->GetOwner()->Tags.Empty();Ground->GetOwner()->Tags.Add(TEXT("Ground"));
 if(!L.Obstacles.ContainsByPredicate([](const FParkingLevel::FObstacle& O){return O.Asset==TEXT("Marking");})){
  for(int X=-2500;X<2700;X+=400)
   Box(FVector(X,-1700,1),FVector(180,8,2),FLinearColor(.6,.65,.62),false);
 }
 for(const auto& O:L.Obstacles)SpawnObstacle(O);
 auto* Base=LoadObject<UMaterialInterface>(nullptr,TEXT("/Game/Materials/M_Target.M_Target"));
 if(!Base)Base=UMaterial::GetDefaultMaterial(MD_Surface);
 TargetMaterial=UMaterialInstanceDynamic::Create(Base,this);
 TargetMaterial->SetVectorParameterValue(TEXT("Tint"),FLinearColor(1,.55,.035));
 const FRotator R(0,L.TargetYaw,0);
 for(float Side:{-1.f,1.f}){
  auto* M=Box(L.Target+R.RotateVector(FVector(0,Side*L.Width/2,2)),FVector(L.Length,5,3),FLinearColor::White,false,L.TargetYaw);M->SetMaterial(0,TargetMaterial);
  M=Box(L.Target+R.RotateVector(FVector(Side*L.Length/2,0,2)),FVector(5,L.Width,3),FLinearColor::White,false,L.TargetYaw);M->SetMaterial(0,TargetMaterial);
 }
 // Arrow inside target points to the required front of the vehicle.
 auto* M=Box(L.Target+FVector(0,0,2),FVector(110,5,2),FLinearColor::White,false,L.TargetYaw);M->SetMaterial(0,TargetMaterial);
 for(float Side:{-1.f,1.f}){
  M=Box(L.Target+R.RotateVector(FVector(35,Side*17,2)),FVector(50,5,2),FLinearColor::White,false,L.TargetYaw-Side*45);M->SetMaterial(0,TargetMaterial);
 }
}
void AParkingGameMode::LoadObstacles(){
 ObstacleAssetsReady=true;
 const TCHAR* Keys[]={TEXT("Car1"),TEXT("Car2"),TEXT("Car3"),TEXT("Barrier"),TEXT("Bollard"),TEXT("Cone"),TEXT("Wall"),TEXT("Curb"),TEXT("CurbCorner"),TEXT("Marking")};
 for(const TCHAR* Key:Keys){
  const FString Path=FString::Printf(TEXT("/Game/Obstacles/SM_%s.SM_%s"),Key,Key);
  UStaticMesh* Mesh=LoadObject<UStaticMesh>(nullptr,*Path);
  if(!Mesh){
   if(FCString::Strcmp(Key,TEXT("Marking"))==0){UE_LOG(LogTemp,Warning,TEXT("Missing Level 12 marking mesh: %s"),*Path);}
   else {ObstacleAssetsReady=false;UE_LOG(LogTemp,Error,TEXT("Missing obstacle: %s"),*Path);}
  }
  else ObstacleMeshes.Add(FString(Key),Mesh);
 }
}
void AParkingGameMode::SpawnObstacle(const FParkingLevel::FObstacle& O){
 const bool bMarking=O.Asset==TEXT("Marking");
 const auto* Found=ObstacleMeshes.Find(O.Asset);if(!Found||!Found->Get())return;
 UStaticMesh* Mesh=Found->Get();const FBox Bounds=Mesh->GetBoundingBox();
 const FVector Size=Bounds.GetSize();
 // Align each model's longest horizontal dimension to the layout's X axis.
 const float ImportYaw=Size.Y>Size.X?90.f:0.f;
 FVector Scale(O.Asset==TEXT("Car2")?470.f/float(FMath::Max(1.,FMath::Max(Size.X,Size.Y))):1.f);
 if(!O.Footprint.IsZero()){
  const bool bLongAxisIsY=Size.Y>Size.X;
  Scale.X=(bLongAxisIsY?O.Footprint.Y:O.Footprint.X)/FMath::Max(1.,Size.X);
  Scale.Y=(bLongAxisIsY?O.Footprint.X:O.Footprint.Y)/FMath::Max(1.,Size.Y);
 }
 if(bMarking&&Size.Z>0.) Scale.Z=.25/Size.Z;
 const FRotator Rotation(0,O.Yaw+ImportYaw,0);
 const FVector Anchor(Bounds.GetCenter().X,Bounds.GetCenter().Y,Bounds.Min.Z);
 AActor* Actor=GetWorld()->SpawnActor<AActor>();LevelActors.Add(Actor);
 UStaticMeshComponent* Component=NewObject<UStaticMeshComponent>(Actor);
 Actor->SetRootComponent(Component);Actor->AddInstanceComponent(Component);
 Component->SetStaticMesh(Mesh);
 Component->SetWorldScale3D(Scale);
 Component->SetWorldLocationAndRotation(O.P-Rotation.RotateVector(Anchor*Scale),Rotation);
 Component->SetMobility(EComponentMobility::Static);
 Component->SetCollisionEnabled(bMarking?ECollisionEnabled::NoCollision:ECollisionEnabled::QueryAndPhysics);
 Component->SetCollisionResponseToAllChannels(ECR_Block);
 Component->SetGenerateOverlapEvents(false);Component->SetCastShadow(!bMarking);
 if(!bMarking) Actor->Tags.Add(TEXT("Obstacle"));
 Component->RegisterComponent();
}
#include "ParkingLevels.inl"
void AParkingGameMode::Collision(AActor* Other,float Impact){
 if(Screen!=0||!Other)return;
 if(Rules.contact(Other->GetUniqueID(),Time,Impact)){
  Toast(FString::Printf(TEXT("Collision %d / 3"),Rules.collisions));
  UGameplayStatics::PlaySound2D(this,LoadObject<USoundWave>(nullptr,TEXT("/Game/Audio/Impact.Impact")),Save->MasterVolume);
  if(Rules.failed){SetScreen(6);UGameplayStatics::PlaySound2D(this,LoadObject<USoundWave>(nullptr,TEXT("/Game/Audio/Failure.Failure")),Save->MasterVolume);}
 }
}
void AParkingGameMode::CalibrationTick(){
 if(!Calibrating)return;
 for(int i=0;i<8;i++){CalMin[i]=FMath::Min(CalMin[i],Wheel.Axes[i]);CalMax[i]=FMath::Max(CalMax[i],Wheel.Axes[i]);}
}
FKey AParkingGameMode::BoundKey(FKey Default) const {
 if(const FString* Name=Save->KeyBindings.Find(Default.ToString()))return FKey(FName(**Name));
 return Default;
}
#if PLATFORM_ANDROID
void AParkingGameMode::SuspendTouch(){
 TouchInput.Cancel();
 if(Screen==0)SetScreen(2);
}
void AParkingGameMode::ReadTouchInput(APlayerController& Controller,float DT){
 using namespace ParkingTouch;
 int32 ViewWidth=0,ViewHeight=0;
 Controller.GetViewportSize(ViewWidth,ViewHeight);
 std::array<Sample,FingerCount> Samples{};
 for(int I=0;I<FingerCount;++I){
  auto& Sample=Samples[I];
  double X=0,Y=0;
  Controller.GetInputTouchState(static_cast<ETouchIndex::Type>(I),X,Y,Sample.Down);
  Sample.Position=ToLayout({X,Y},ViewWidth,ViewHeight);
 }
 const bool Driving=Screen==0&&Car->AssetLoaded;
 TouchInput.Update(Samples,Driving,Save->AndroidSteeringWheel);
 if(!Driving)return;
 if(TouchInput.Pressed(Control::Pause)||Controller.WasInputKeyJustPressed(EKeys::Android_Back)){SetScreen(2);return;}
 if(TouchInput.Pressed(Control::Camera))Car->ToggleCamera();
 if(TouchInput.Pressed(Control::Handbrake))Car->Handbrake=!Car->Handbrake;
 const bool Left=TouchInput.Down(Control::Left),Right=TouchInput.Down(Control::Right);
 if(Save->AndroidSteeringWheel){
  Car->Steering.angle=Parking::approach(Car->Steering.angle,TouchInput.Steering(),DT*4.);
 }else{
  Car->Steering.keyboard(DT,Left,Right,Left==Right,Car->Speed,5);
 }
 Car->Brake=TouchInput.Down(Control::Brake)?1.f:0.f;
 Car->Throttle=TouchInput.Down(Control::Accelerator)&&Car->Brake==0
  ?FMath::FInterpConstantTo(Car->Throttle,1.f,DT,2.2f):0.f;
 if(TouchInput.Pressed(Control::Drive)||TouchInput.Pressed(Control::Neutral)||TouchInput.Pressed(Control::Reverse)){
  const int Gear=TouchInput.Pressed(Control::Neutral)?0:(TouchInput.Pressed(Control::Reverse)?-1:1);
  if(!Car->Drive.select(Gear,Car->Speed,0))Toast(TEXT("Stop before changing direction."));
 }
}
#endif
void AParkingGameMode::ReadInput(float DT){
 auto* PC=GetWorld()->GetFirstPlayerController();if(!PC||!Save||!Car)return;
#if PLATFORM_ANDROID
 ReadTouchInput(*PC,DT);
#else
 if(!CaptureKey.IsEmpty()){
  TArray<FKey> Keys;EKeys::GetAllKeys(Keys);
  for(const FKey& Key:Keys){
   if(Key.IsMouseButton()||Key.IsGamepadKey()||Key.IsAnalog())continue;
   if(PC->WasInputKeyJustPressed(Key)){
    if(Key!=EKeys::Escape){
     if(Key==EKeys::F1||Key==EKeys::F4||Key==EKeys::F5||Key==EKeys::Up||Key==EKeys::Down||Key==EKeys::Left||Key==EKeys::Right){
      Toast(TEXT("That key is reserved for menus or alternate driving controls."));return;
     }
     const FKey Defaults[]={EKeys::W,EKeys::S,EKeys::A,EKeys::D,EKeys::X,EKeys::SpaceBar,EKeys::One,EKeys::N,EKeys::R,EKeys::Q,EKeys::E,EKeys::LeftShift,EKeys::I,EKeys::T,EKeys::C,EKeys::V,EKeys::L,EKeys::Two,EKeys::Three,EKeys::Four,EKeys::Five};
     FKey Previous=BoundKey(FKey(FName(*CaptureKey)));
     for(FKey Other:Defaults)if(Other.ToString()!=CaptureKey&&BoundKey(Other)==Key)Save->KeyBindings.Add(Other.ToString(),Previous.ToString());
     Save->KeyBindings.Add(CaptureKey,Key.ToString());SaveProgress();Toast(TEXT("Keyboard binding saved; conflicting action swapped."));
    }
    CaptureKey.Empty();return;
   }
  }return;
 }
 auto Press=[this,PC](FKey K){return PC->WasInputKeyJustPressed(BoundKey(K));};
 auto Down=[this,PC](FKey K){return PC->IsInputKeyDown(BoundKey(K));};
 if(Press(EKeys::Escape)){
  if(GraphicsConfirm){RevertGraphics();return;}
  if(Screen==0)SetScreen(2);else if(Screen==2)SetScreen(0);else if(Screen==8||Screen==9||Screen==7||Screen==10)SetScreen(4);else if(Screen==4)SetScreen(ReturnScreen);else SetScreen(1);
 }
 if(Press(EKeys::F1)){ReturnScreen=(Screen==0||Screen==2)?2:(Screen==1?1:ReturnScreen);SetScreen(7);}
 if(Press(EKeys::F4)){ReturnScreen=(Screen==0||Screen==2)?2:(Screen==1?1:ReturnScreen);SetScreen(4);}
 if(CaptureAction>=0 && Wheel.IsConnected()){
  for(int i=0;i<128;i++)if(Wheel.Buttons[i]&&!OldButtons[i]){
   if(CaptureAction==0)Save->ShiftUp=i;else Save->ShiftDown=i;
   CaptureAction=-1;SaveProgress();Toast(TEXT("Paddle/button saved."));break;
  }
 }
 if(Screen!=0||!Car->AssetLoaded)return;
 if(Press(EKeys::F5)){StartLevel(Level);return;}
 if(Press(EKeys::C))Car->ToggleCamera();
 if(Press(EKeys::L))Car->ToggleLights();
 Car->Handbrake=Parking::HandbrakeInput(Car->Handbrake,Save->HandbrakeHold,Press(EKeys::SpaceBar),Down(EKeys::SpaceBar));
 if(Press(EKeys::T)){
  if(FMath::Abs(Car->Speed)<.2f){
   Save->Transmission=(Save->Transmission+1)%3;Car->Drive.setMode(static_cast<Parking::Mode>(Save->Transmission));SaveProgress();
  }else Toast(TEXT("Stop before changing transmission mode."));
 }
 if(auto* CameraPC=GetWorld()->GetFirstPlayerController()){
  float MouseX=0,MouseY=0;CameraPC->GetInputMouseDelta(MouseX,MouseY);
  const float MouseScale=.5f+.25f*(Save->MouseSensitivity-1);
  Car->MouseLook(MouseX*MouseScale,MouseY*MouseScale,Down(EKeys::V),DT);
 }
 const bool UseWheel=Save->WheelEnabled&&Save->Calibrated&&Wheel.IsConnected();
 if(!UseWheel)Wheel.SetForce(0);
 if(UseWheel){
  for(int i=0;i<4;i++){
   int Axis=FMath::Clamp(Save->Axes[i],0,7);float Raw=Wheel.Axes[Axis],Value=0;
   if(i==0){
    float Centre=Save->Rest[0];
    Value=Raw>=Centre?(Raw-Centre)/FMath::Max(.01f,Save->Maximum[0]-Centre):(Raw-Centre)/FMath::Max(.01f,Centre-Save->Minimum[0]);
    if(Save->Invert[0])Value=-Value;
    Car->Steering.angle=FMath::Abs(Value)<.015f?0:FMath::Clamp(Value,-1.f,1.f);
   }else{
    const float Range=FMath::Max(.01f,Save->Maximum[i]-Save->Minimum[i]);
    Value=FMath::Clamp((Raw-Save->Minimum[i])/Range,0.f,1.f);
    if(Save->Invert[i])Value=1-Value;
    Value=Value<.025f?0:Value;
    if(i==1)Car->Throttle=Value;if(i==2)Car->Brake=Value;if(i==3)Car->Clutch=Value;
   }
  }
 }else{
  Car->Steering.keyboard(DT,Down(EKeys::A)||Down(EKeys::Left),Down(EKeys::D)||Down(EKeys::Right),Down(EKeys::X),Car->Speed,Save->KeyboardSteeringSensitivity);
  Car->Throttle=FMath::FInterpConstantTo(Car->Throttle,Down(EKeys::W)||Down(EKeys::Up)?1.f:0.f,DT,2.2f);
  Car->Brake=FMath::FInterpConstantTo(Car->Brake,Down(EKeys::S)||Down(EKeys::Down)?1.f:0.f,DT,4.f);
  Car->Clutch=FMath::FInterpConstantTo(Car->Clutch,Down(EKeys::LeftShift)?1.f:0.f,DT,Down(EKeys::LeftShift)?6.f:1.2f);
 }
 auto Select=[this](int Gear){if(!Car->Drive.select(Gear,Car->Speed,Car->Clutch))Toast(TEXT("Stop to change direction; depress clutch in full manual."));};
 if(Press(EKeys::R))Select(-1);
 if(Press(EKeys::N))Select(0);
 if(Press(EKeys::One))Select(1);
 if(Car->Drive.mode==Parking::Mode::Clutch){
  if(Press(EKeys::Two))Select(2);if(Press(EKeys::Three))Select(3);
  if(Press(EKeys::Four))Select(4);if(Press(EKeys::Five))Select(5);
 }
 bool Up=Press(EKeys::E),Dn=Press(EKeys::Q);
 if(UseWheel){
  int U=FMath::Clamp(Save->ShiftUp,0,127),D=FMath::Clamp(Save->ShiftDown,0,127);
  Up|=Wheel.Buttons[U]&&!OldButtons[U];Dn|=Wheel.Buttons[D]&&!OldButtons[D];
 }
 if(Up||Dn){
  if(Car->Drive.mode==Parking::Mode::Automatic){
   // Paddles explicitly choose R -> N -> D. Forward gears remain automatic.
   int Selector=Car->Drive.gear<0?-1:(Car->Drive.gear>0?1:0);Select(FMath::Clamp(Selector+(Up?1:-1),-1,1));
  }else if(!Car->Drive.shift(Up?1:-1,Car->Speed,Car->Clutch))Toast(TEXT("Depress clutch before shifting."));
 }
 if(Press(EKeys::I)&&!Car->Drive.restart(Car->Speed,Car->Clutch))Toast(TEXT("Select neutral or depress clutch to restart."));
 if(UseWheel&&Save->Feedback){
  Wheel.SetForce(float(Parking::WheelCenteringForce(Car->Steering.angle,Car->Speed,Save->FeedbackStrength,Save->FeedbackInvert)));
 }else Wheel.SetForce(0);
#endif
}
void AParkingGameMode::Tick(float DT){
 Super::Tick(DT);if(!Save||!Car)return;
 if(GraphicsConfirm && FPlatformTime::Seconds()>=GraphicsDeadline)RevertGraphics();
 DT=FMath::Min(DT,.05f);
 NoticeTime=FMath::Max(0.f,NoticeTime-DT);
 bool Connected=Wheel.Poll();
 if(WasWheelConnected&&!Connected&&Save->WheelEnabled&&Screen==0){SetScreen(2);Toast(TEXT("Wheel disconnected. Reconnect, then resume."));}
 WasWheelConnected=Connected;
 CalibrationTick();ReadInput(DT);
 FMemory::Memcpy(OldButtons,Wheel.Buttons,sizeof(OldButtons));
 if(Screen!=0||!Car||!TargetMaterial||!Levels.IsValidIndex(Level))return;
 Time+=DT;
 const auto& L=Levels[Level];
 const FTransform Transform=Car->Body->GetComponentTransform();
 Parking::Vec2 Wheels[4];
 for(int32 Index=0;Index<4;++Index){
  const FVector Centre=Transform.TransformPosition(Car->WheelOffsets[Index]+FVector(0,0,Car->WheelTravel[Index]));
  Wheels[Index]={Centre.X/100.,Centre.Y/100.};
 }
 const bool Inside=Parking::wheelsFit(Wheels,FMath::DegreesToRadians(Car->GetActorRotation().Yaw),
  {L.Target.X/100.,L.Target.Y/100.},FMath::DegreesToRadians(L.TargetYaw),L.Length/100.,L.Width/100.);
 TArray<FOverlapResult> Overlaps;
 FComponentQueryParams Query;Query.AddIgnoredActor(Car.Get());
 GetWorld()->ComponentOverlapMulti(Overlaps,Car->Body.Get(),Car->Body->GetComponentLocation(),
  Car->Body->GetComponentQuat(),Query,FCollisionObjectQueryParams::AllObjects);
 bool Touch=false;
 for(const auto& O:Overlaps)if(O.GetActor()&&O.GetActor()->ActorHasTag(TEXT("Obstacle"))){
  Touch=true;
  auto It=Rules.lastContact.find(O.GetActor()->GetUniqueID());
  if(It!=Rules.lastContact.end())It->second=Time; // maintain an existing contact episode
 }
 Rules.park(DT,Inside,Car->Body->GetPhysicsLinearVelocity().Size()/100.,Touch||Rules.touching(Time)||Car->Body->GetPhysicsAngularVelocityInDegrees().Size()>1.5||FVector::DotProduct(Car->GetActorUpVector(),FVector::UpVector)<.85);
 TargetMaterial->SetVectorParameterValue(TEXT("Tint"),Inside?FLinearColor(.06,1,.3):FLinearColor(1,.55,.035));
 if(Rules.complete){Save->Unlocked=FMath::Max(Save->Unlocked,FMath::Min(Level+2,Levels.Num()));SaveProgress();SetScreen(5);UGameplayStatics::PlaySound2D(this,LoadObject<USoundWave>(nullptr,TEXT("/Game/Audio/Success.Success")),Save->MasterVolume);}
}
void AParkingGameMode::HandleAction(int A){
 if(!Save||!Car)return;
 if(A>=500 && A<514){
  if(Screen==8 && !GraphicsConfirm && GraphicsDraft.Num()==14){const int32 Index=A-500;GraphicsDraft[Index]=(GraphicsDraft[Index]+1)%GraphicsCounts[Index];}return;
 }
 if(A>=540 && A<=543){if(Screen==8&&!GraphicsConfirm)GraphicsPreset(A-540);return;}
 if(A==530){
  if(Screen!=8||GraphicsConfirm||GraphicsDraft==Save->Graphics)return;
  GraphicsPrevious=Save->Graphics;Save->Graphics=GraphicsDraft;ConfigureQuality();
  GraphicsConfirm=true;GraphicsDeadline=FPlatformTime::Seconds()+15.;return;
 }
 if(A==531){if(GraphicsConfirm){GraphicsConfirm=false;if(auto* Settings=UGameUserSettings::GetGameUserSettings())Settings->ConfirmVideoMode();SaveProgress();Toast(TEXT("Graphics settings saved."));}return;}
 if(A==532){RevertGraphics();return;}
 if(A==533){GraphicsDraft=Save->Graphics;Toast(TEXT("Unapplied changes discarded."));return;}

 if(GraphicsConfirm)return;
 if(A>=HeightActionBase && A<=HeightActionBase+ACiazPawn::MaxRideHeightOffsetCm){
  if(Screen==1){
   Car->RideHeightOffsetCm=Save->RideHeightOffsetCm=float(A-HeightActionBase);
   SaveProgress();
  }
  return;
 }
 if(A>SteeringSensitivityActionBase && A<=SteeringSensitivityActionBase+5){
  if(Screen==7){
   Save->KeyboardSteeringSensitivity=A-SteeringSensitivityActionBase;
   SaveProgress();
  }
  return;
 }
 if(A>MouseSensitivityActionBase && A<=MouseSensitivityActionBase+5){
  if(Screen==7){
   Save->MouseSensitivity=A-MouseSensitivityActionBase;
   SaveProgress();
  }
  return;
 }
 if(A>=FOVActionBase && A<=FOVActionBase+int(ACiazPawn::MaxInteriorFOV-ACiazPawn::MinInteriorFOV)){
  Save->InteriorFOV=float(A-FOVActionBase)+ACiazPawn::MinInteriorFOV;Car->SetInteriorFOV(Save->InteriorFOV);return;
 }
 if(A==480){SaveProgress();return;}
 if(A==800){
  if(Screen==4){
   Car->Cockpit=true;Car->SetInteriorCamera(Save->InteriorCameraOffset,Save->InteriorCameraRotation);SetScreen(10);
  }
  return;
 }
 if(A>=810 && A<=822){
  if(Screen!=10)return;
  if(A==822){
   Save->InteriorCameraOffset=FVector::ZeroVector;Save->InteriorCameraRotation=FRotator::ZeroRotator;Save->InteriorFOV=85.f;
  }else{
   const int32 Row=(A-810)/2;
   const float Direction=(A%2)?1.f:-1.f;
   if(Row<3)Save->InteriorCameraOffset[Row]=FMath::Clamp(Save->InteriorCameraOffset[Row]+Direction*2.0,-60.0,60.0);
   else if(Row==3)Save->InteriorCameraRotation.Pitch=FMath::Clamp(Save->InteriorCameraRotation.Pitch+Direction*2.0,-50.0,65.0);
   else if(Row==4)Save->InteriorCameraRotation.Yaw=FMath::Clamp(Save->InteriorCameraRotation.Yaw+Direction*2.0,-135.0,135.0);
   else Save->InteriorFOV=FMath::Clamp(Save->InteriorFOV+Direction,ACiazPawn::MinInteriorFOV,ACiazPawn::MaxInteriorFOV);
  }
  Car->SetInteriorFOV(Save->InteriorFOV);Car->SetInteriorCamera(Save->InteriorCameraOffset,Save->InteriorCameraRotation);
  SaveProgress();return;
 }
 if(A==823){if(Screen==10)SetScreen(4);return;}
 if(A>=300&&A<321){
  const FKey Keys[]={EKeys::W,EKeys::S,EKeys::A,EKeys::D,EKeys::X,EKeys::SpaceBar,EKeys::One,EKeys::N,EKeys::R,EKeys::Q,EKeys::E,EKeys::LeftShift,EKeys::I,EKeys::T,EKeys::C,EKeys::V,EKeys::L,EKeys::Two,EKeys::Three,EKeys::Four,EKeys::Five};
  CaptureKey=Keys[A-300].ToString();Toast(TEXT("Press a keyboard key. Escape cancels."));return;
 }
 if(A>=100&&Levels.IsValidIndex(A-100)){StartLevel(A-100);return;}
 if(A>=200&&A<204){int I=A-200;Save->Axes[I]=(Save->Axes[I]+1)%8;Save->Calibrated=false;SaveProgress();return;}
 if(A>=210&&A<214){int I=A-210;Save->Invert[I]=!Save->Invert[I];SaveProgress();return;}
 switch(A){
#if PLATFORM_ANDROID
 case TouchButtonsAction:
 case TouchWheelAction:
  if(Screen==9){Save->AndroidSteeringWheel=A==TouchWheelAction;TouchInput.Cancel();SaveProgress();}
  break;
#endif
 case 1:StartLevel(Save->Unlocked-1);break;
 case 2:SetScreen(3);break;
 case 3:ReturnScreen=Screen;SetScreen(4);break;
 case 4:ReturnScreen=Screen;SetScreen(9);break;
 case 5:if(auto* PC=GetWorld()->GetFirstPlayerController())PC->ConsoleCommand(TEXT("quit"));break;
 case 6:SetScreen(0);break;
 case 7:StartLevel(Level);break;
 case 8:SetScreen(1);break;
 case 9:StartLevel(FMath::Min(Level+1,Levels.Num()-1));break;
 case 10:SetScreen(ReturnScreen);break;
 case 11:SetScreen(4);break;
 case 12:SetScreen(8);break;
 case 13:SetScreen(9);break;
 case 14:SetScreen(7);break;
 case 20:Save->WheelEnabled=!Save->WheelEnabled;SaveProgress();break;
 case 21:Save->Transmission=(Save->Transmission+1)%3;Car->Drive.setMode(static_cast<Parking::Mode>(Save->Transmission));SaveProgress();break;

 case 23:
  if(!Wheel.IsConnected()){Toast(TEXT("Connect the T248 first."));break;}
  if(!Calibrating){
   Calibrating=true;for(int i=0;i<8;i++)CalMin[i]=CalMax[i]=Wheel.Axes[i];
   Toast(TEXT("Turn fully both ways and press every pedal. Then centre wheel, release pedals, and click Finish."));
  }else{
   bool Valid=true;
   TSet<int> UniqueAxes;for(int Axis:Save->Axes)UniqueAxes.Add(Axis);
   if(UniqueAxes.Num()!=4){Toast(TEXT("Assign a different axis to steering and each pedal."));break;}
   const TCHAR* ControlNames[]={TEXT("Steering"),TEXT("Accelerator"),TEXT("Brake"),TEXT("Clutch")};
   for(int i=0;i<4;i++){
    const int Axis=Save->Axes[i];
    if(CalMax[Axis]-CalMin[Axis]<.3f){
     Toast(FString::Printf(TEXT("%s on axis %d needs more travel. Check its assignment."),ControlNames[i],Axis));
     Valid=false;break;
    }
   }
   if(!Valid)break;
   const int SteeringAxis=Save->Axes[0];
   if(!Parking::SteeringCalibrationValid(CalMin[SteeringAxis],CalMax[SteeringAxis],Wheel.Axes[SteeringAxis])){
    Toast(TEXT("Centre the steering wheel before finishing calibration."));break;
   }
   for(int i=1;i<4;++i){const int Axis=Save->Axes[i];
    if(!Parking::PedalAtRest(CalMin[Axis],CalMax[Axis],Wheel.Axes[Axis])){Valid=false;break;}
   }
   if(!Valid){Toast(TEXT("Release all pedals before finishing calibration."));break;}
   for(int i=0;i<4;i++){
    int Axis=Save->Axes[i];Save->Minimum[i]=CalMin[Axis];Save->Maximum[i]=CalMax[Axis];Save->Rest[i]=Wheel.Axes[Axis];
    if(i>0)Save->Invert[i]=Wheel.Axes[Axis]>(CalMin[Axis]+CalMax[Axis])*.5f;
   }
   Calibrating=false;Save->Calibrated=true;SaveProgress();Toast(TEXT("Calibration saved. Verify pedals and steering before driving."));
  }break;
 case 24:Save->Feedback=!Save->Feedback;SaveProgress();break;
 case 25:Save->FeedbackInvert=!Save->FeedbackInvert;SaveProgress();break;
 case 26:Save->MasterVolume=Save->MasterVolume>=.999f?0:FMath::Min(1.f,(FMath::FloorToFloat(Save->MasterVolume*4.f)+1.f)/4.f);SaveProgress();break;
 case 27:CaptureAction=0;Toast(TEXT("Press the shift-up paddle/button."));break;
 case 30:if(Screen==1)SelectVehicle(1-Save->VehicleIndex);break;
 case 29:Save->HandbrakeHold=!Save->HandbrakeHold;Car->Handbrake=false;SaveProgress();break;
 case 28:CaptureAction=1;Toast(TEXT("Press the shift-down paddle/button."));break;
 }
}

void AParkingGameMode::SelectVehicle(int32 Index){
 if(Screen!=1||!Car)return;
 auto* Replacement=GetWorld()->SpawnActorDeferred<ACiazPawn>(ACiazPawn::StaticClass(),FTransform::Identity);
 if(!Replacement){Toast(TEXT("Could not create vehicle"));return;}
 Replacement->VehicleIndex=FMath::Clamp(Index,0,1);Replacement->RideHeightOffsetCm=Save->RideHeightOffsetCm;
 Replacement->FinishSpawning(FTransform::Identity);
 if(!Replacement->AssetLoaded){Replacement->Destroy();Toast(TEXT("Vehicle assets missing. Run SetupProject.cmd."));return;}
 Car->SetFrozen(true);Car->Destroy();Car=Replacement;
 Save->VehicleIndex=Replacement->VehicleIndex;SaveProgress();
 if(auto* Controller=GetWorld()->GetFirstPlayerController())Controller->Possess(Car);
 Car->AddTickPrerequisiteActor(this);Car->SetInteriorFOV(Save->InteriorFOV);
 Car->SetInteriorCamera(Save->InteriorCameraOffset,Save->InteriorCameraRotation);
 StartLevel(Level);SetScreen(1);
}
