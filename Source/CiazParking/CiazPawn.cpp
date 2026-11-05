#include "CiazPawn.h"
#include "VehicleDataValidation.h"
#include "VehicleDynamics.h"
#include "ParkingGameMode.h"
#include "ParkingSave.h"
#include "Components/AudioComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/SpotLightComponent.h"
#include "ProceduralMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Sound/SoundWave.h"
#include "ImageUtils.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/StaticMesh.h"
#include "Engine/Texture2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Components/SceneCaptureComponent2D.h"

namespace {
void BuildSwiftTangents(const TArray<FVector>& Vertices,const TArray<int32>& Indices,
 const TArray<FVector>& Normals,const TArray<FVector2D>& UVs,TArray<FProcMeshTangent>& Tangents){
 TArray<FVector> TangentSums,BitangentSums;
 TangentSums.Init(FVector::ZeroVector,Vertices.Num());
 BitangentSums.Init(FVector::ZeroVector,Vertices.Num());
 for(int32 Index=0;Index<Indices.Num();Index+=3){
  const int32 A=Indices[Index],B=Indices[Index+1],C=Indices[Index+2];
  const FVector EdgeB=Vertices[B]-Vertices[A],EdgeC=Vertices[C]-Vertices[A];
  const FVector2D UVB=UVs[B]-UVs[A],UVC=UVs[C]-UVs[A];
  const double Determinant=UVB.X*UVC.Y-UVB.Y*UVC.X;
  if(FMath::Abs(Determinant)<=UE_DOUBLE_SMALL_NUMBER)continue;
  const FVector Tangent=((EdgeB*UVC.Y-EdgeC*UVB.Y)/Determinant).GetSafeNormal();
  const FVector Bitangent=((EdgeC*UVB.X-EdgeB*UVC.X)/Determinant).GetSafeNormal();
  for(const int32 Corner:{A,B,C}){
   TangentSums[Corner]+=Tangent;
   BitangentSums[Corner]+=Bitangent;
  }
 }
 Tangents.Reserve(Vertices.Num());
 for(int32 Index=0;Index<Vertices.Num();++Index){
  const FVector Normal=Normals[Index].GetSafeNormal(UE_DOUBLE_SMALL_NUMBER,FVector::UpVector);
  FVector Tangent=(TangentSums[Index]-Normal*FVector::DotProduct(Normal,TangentSums[Index])).GetSafeNormal();
  if(Tangent.IsNearlyZero()){
   FVector UnusedBitangent;
   Normal.FindBestAxisVectors(Tangent,UnusedBitangent);
  }
  Tangents.Emplace(Tangent,FVector::DotProduct(FVector::CrossProduct(Normal,Tangent),BitangentSums[Index])<0.);
 }
}
}

ACiazPawn::ACiazPawn(){
 GaugeNeedles.SetNum(2);
 PrimaryActorTick.bCanEverTick=true;PrimaryActorTick.TickGroup=TG_PrePhysics;
 Body=CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ChassisCollision"));
 SetRootComponent(Body);
 Body->bUseComplexAsSimpleCollision=false;Body->bUseAsyncCooking=false;
 Body->SetCollisionProfileName(TEXT("PhysicsActor"));
 Body->SetSimulatePhysics(false);Body->SetNotifyRigidBodyCollision(true);
 Body->SetLinearDamping(.06f);Body->SetAngularDamping(.45f);
 Body->SetUseCCD(true);
 Boom=CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
 Boom->SetupAttachment(Body);Boom->TargetArmLength=720;Boom->SetRelativeLocation(FVector(0,0,120));
 Boom->SetAbsolute(false,true,false);Boom->SetRelativeRotation(FRotator(-24,0,0));Boom->bEnableCameraLag=true;Boom->CameraLagSpeed=7;
 Camera=CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));Camera->SetupAttachment(Boom);
 Camera->SetFieldOfView(72);
 EngineAudio=CreateDefaultSubobject<UAudioComponent>(TEXT("EngineAudio"));EngineAudio->SetupAttachment(Body);EngineAudio->bAutoActivate=false;
 LoadAudio=CreateDefaultSubobject<UAudioComponent>(TEXT("EngineLoad"));LoadAudio->SetupAttachment(Body);LoadAudio->bAutoActivate=false;
 BeepAudio=CreateDefaultSubobject<UAudioComponent>(TEXT("SensorAudio"));BeepAudio->SetupAttachment(Body);BeepAudio->bAutoActivate=false;
 for(int i=0;i<4;i++)WheelOffsets[i]=FVector(i<2?139:-126,(i%2)?73:-73,-51);
}
void ACiazPawn::BeginPlay(){
 Super::BeginPlay();ConfigureVehicle();RideHeightOffsetCm=FMath::Clamp(RideHeightOffsetCm,0.f,float(MaxRideHeightOffsetCm));if(VehicleIndex==1)BuildSwiftCollision();else BuildBodyCollision();
 Body->SetMassOverrideInKg(NAME_None,VehicleMass,true);
 // Keep the previous intended COM position despite the new compound geometry.
 const FVector NaturalCOM=GetActorTransform().InverseTransformPosition(Body->GetCenterOfMass());
 Body->SetCenterOfMass(FVector(VehicleIndex==1?16.8f:20.f,0,VehicleIndex==1?-28.f:-20.f)-NaturalCOM);
 Body->OnComponentHit.AddDynamic(this,&ACiazPawn::OnHit);LoadVehicle();
 EngineAudio->SetSound(LoadObject<USoundWave>(nullptr,TEXT("/Game/Audio/EngineIdle.EngineIdle")));
 LoadAudio->SetSound(LoadObject<USoundWave>(nullptr,TEXT("/Game/Audio/EngineLoad.EngineLoad")));
 BeepAudio->SetSound(LoadObject<USoundWave>(nullptr,TEXT("/Game/Audio/SensorTone.SensorTone")));
 for(float Side:{-1.f,1.f}){
  auto* L=NewObject<USpotLightComponent>(this);AddInstanceComponent(L);L->SetupAttachment(Body);
  L->SetRelativeLocation(FVector(VehicleLength*.44f,Side*65,-10));L->SetRelativeRotation(FRotator(-5,0,0));
  L->SetIntensity(12000);L->SetAttenuationRadius(1800);L->SetOuterConeAngle(37);L->SetInnerConeAngle(20);
  L->SetCastShadows(false);L->RegisterComponent();L->SetVisibility(false);Headlights.Add(L);
 }
}
void ACiazPawn::LoadVehicle(){
 AssetLoaded=false;if(!CollisionReady)return;
 const FString Folder=VehicleFolder();
 FString Text;if(!FFileHelper::LoadFileToString(Text,*(Folder/TEXT("vehicle.json"))))return;
 TSharedPtr<FJsonObject> Root;
 if(!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),Root)||!Root.IsValid())return;
 if(!VehicleDataValidation::Manifest(Root,VehicleIndex==1)){UE_LOG(LogTemp,Error,TEXT("Invalid vehicle manifest: %s"),*Folder);return;}
 double ModelWheelRadius=0.;
 if(VehicleIndex==1 && Root->TryGetNumberField(TEXT("wheel_radius"),ModelWheelRadius)
    && ModelWheelRadius>=20. && ModelWheelRadius<=50.){
  WheelRadius=float(ModelWheelRadius);
  Drive.tireRadius=ModelWheelRadius/100.;
 }
 auto* Base=LoadObject<UMaterialInterface>(nullptr,TEXT("/Game/Materials/M_Car.M_Car"));
 auto* Paint=LoadObject<UMaterialInterface>(nullptr,TEXT("/Game/Materials/M_Paint.M_Paint"));
 auto* Interior=LoadObject<UMaterialInterface>(nullptr,TEXT("/Game/Materials/M_Interior.M_Interior"));
 auto* Glass=LoadObject<UMaterialInterface>(nullptr,TEXT("/Game/Materials/M_Glass.M_Glass"));
 auto* Instrument=LoadObject<UMaterialInterface>(nullptr,TEXT("/Game/Materials/M_Instrument.M_Instrument"));
 if(!Base||!Glass||!Paint||!Interior||!Instrument)return;
 for(auto Entry:Root->GetArrayField(TEXT("materials"))){
  auto O=Entry->AsObject();bool IsGlass=O->GetBoolField(TEXT("glass"));
  bool IsInterior=false;O->TryGetBoolField(TEXT("interior"),IsInterior);
  bool IsPaint=false;O->TryGetBoolField(TEXT("paint"),IsPaint);
  UMaterialInterface* SwiftMaterial=nullptr;
  if(VehicleIndex==1)SwiftMaterial=LoadObject<UMaterialInterface>(nullptr,*FString::Printf(TEXT("/Game/SwiftMaterials/M_Swift_%02d.M_Swift_%02d"),Materials.Num(),Materials.Num()));
  if(VehicleIndex==1&&!SwiftMaterial){UE_LOG(LogTemp,Error,TEXT("Swift material missing: run SetupProject.cmd"));return;}
  auto* M=UMaterialInstanceDynamic::Create(SwiftMaterial?SwiftMaterial:(IsGlass?Glass:(IsPaint&&Paint?Paint:(IsInterior&&Interior?Interior:Base))),this);
  auto Color=O->GetArrayField(TEXT("color"));
  M->SetVectorParameterValue(TEXT("Tint"),FLinearColor(Color[0]->AsNumber(),Color[1]->AsNumber(),Color[2]->AsNumber(),1));
  M->SetScalarParameterValue(TEXT("Metallic"),O->GetNumberField(TEXT("metallic")));
  M->SetScalarParameterValue(TEXT("Roughness"),O->GetNumberField(TEXT("roughness")));
  FString Texture=O->GetStringField(TEXT("texture"));
  if(!Texture.IsEmpty()){
   FString TextureAsset;O->TryGetStringField(TEXT("texture_asset"),TextureAsset);
   auto* T=TextureAsset.IsEmpty()?nullptr:LoadObject<UTexture2D>(nullptr,*TextureAsset);
   if(!T)T=FImageUtils::ImportFileAsTexture2D(Folder/TEXT("Textures")/Texture);
   if(!T){UE_LOG(LogTemp,Error,TEXT("Missing vehicle texture: %s"),*Texture);return;}
   if(T){
    M->SetTextureParameterValue(TEXT("BaseTexture"),T);M->SetVectorParameterValue(TEXT("Tint"),FLinearColor::White);
   }
  }
  double Specular=.5,Opacity=IsGlass?.16:1.;
  O->TryGetNumberField(TEXT("specular"),Specular);O->TryGetNumberField(TEXT("opacity"),Opacity);
  M->SetScalarParameterValue(TEXT("Specular"),float(Specular));
  M->SetScalarParameterValue(TEXT("Opacity"),float(Opacity));Materials.Add(M);
 }
 for(auto Entry:Root->GetArrayField(TEXT("parts"))){
  auto O=Entry->AsObject();TArray<uint8> Bytes;
  if(!FFileHelper::LoadFileToArray(Bytes,*(Folder/O->GetStringField(TEXT("file")))) || Bytes.Num()<12)continue;
  uint32 Header[3];FMemory::Memcpy(Header,Bytes.GetData(),12);
  uint32 N=Header[1],Count=Header[2];
  if(Header[0]!=0x43505A31 || N>2000000 || Count>6000000 ||
    int64(Bytes.Num())!=12+int64(N)*32+int64(Count)*4)continue;
  TArray<FVector> V,Normals;TArray<FVector2D> UV;TArray<int32> Indices;
  V.Reserve(N);Normals.Reserve(N);UV.Reserve(N);Indices.SetNum(Count);
  for(uint32 i=0;i<N;i++){
   float F[8];FMemory::Memcpy(F,Bytes.GetData()+12+i*32,32);
   V.Add(FVector(F[0],F[1],F[2]));Normals.Add(FVector(F[3],F[4],F[5]));UV.Add(FVector2D(F[6],F[7]));
  }
  FMemory::Memcpy(Indices.GetData(),Bytes.GetData()+12+N*32,Count*4);
  bool ValidMesh=N>0&&Count>0&&Count%3==0;
  for(int32 Index:Indices)if(Index<0||Index>=int32(N)){ValidMesh=false;break;}
  for(const FVector& Position:V)if(Position.ContainsNaN()){ValidMesh=false;break;}
  for(const FVector& Normal:Normals)if(Normal.ContainsNaN()){ValidMesh=false;break;}
  for(const FVector2D& Texcoord:UV)if(Texcoord.ContainsNaN()){ValidMesh=false;break;}
  if(!ValidMesh){UE_LOG(LogTemp,Error,TEXT("Invalid vehicle mesh indices or vertices"));continue;}
  auto* Mesh=NewObject<UProceduralMeshComponent>(this);AddInstanceComponent(Mesh);Mesh->SetupAttachment(Body);
  Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);Mesh->SetCastShadow(true);
  Mesh->RegisterComponent();
  TArray<FProcMeshTangent> Tangents;
  if(VehicleIndex==1)BuildSwiftTangents(V,Indices,Normals,UV,Tangents);
  Mesh->CreateMeshSection_LinearColor(0,V,Indices,Normals,UV,TArray<FLinearColor>(),Tangents,false);
  int Mat=O->GetIntegerField(TEXT("material"));if(Materials.IsValidIndex(Mat))Mesh->SetMaterial(0,Materials[Mat]);
  int Group=O->GetIntegerField(TEXT("group"));auto P=O->GetArrayField(TEXT("pivot"));
  const bool IsNeedle=(Group==5||Group==6)||(VehicleIndex==0&&Mat==7&&O->GetStringField(TEXT("file")).StartsWith(TEXT("gauge_")));
  const bool IsDial=(VehicleIndex==0&&Mat==32)||(VehicleIndex==1&&Mat==1&&!IsNeedle);
  if(IsNeedle||IsDial){
   auto* Lit=UMaterialInstanceDynamic::Create(Instrument,this);
   auto* DialTexture=LoadObject<UTexture2D>(nullptr,IsNeedle?TEXT("/Game/Materials/T_White.T_White"):
    (VehicleIndex==0?TEXT("/Game/Materials/Instruments/T_Ciaz_Dials.T_Ciaz_Dials"):TEXT("/Game/Materials/Instruments/T_Swift_Dials.T_Swift_Dials")));
   if(!DialTexture){UE_LOG(LogTemp,Error,TEXT("Instrument textures missing: run SetupProject.cmd"));return;}
   Lit->SetTextureParameterValue(TEXT("BaseTexture"),DialTexture);
   Lit->SetScalarParameterValue(TEXT("VehicleAtlas"),IsNeedle?0.f:(VehicleIndex==0?1.f:2.f));
   Lit->SetScalarParameterValue(TEXT("Backlight"),HeadlightsOn?1.2f:0.f);
   Lit->SetVectorParameterValue(TEXT("Tint"),IsNeedle?FLinearColor(.7f,.12f,.06f):FLinearColor::White);
   Lit->SetVectorParameterValue(TEXT("EmissionColor"),IsNeedle?FLinearColor(1.f,.055f,.015f):FLinearColor(1.f,.92f,.8f));
   Mesh->SetMaterial(0,Lit);InstrumentMaterials.Add(Lit);
  }
  FVector Pivot(P[0]->AsNumber(),P[1]->AsNumber(),P[2]->AsNumber());
  Mesh->SetRelativeLocation(Pivot);
  Mesh->ComponentTags.Add(FName(*FString::FromInt(Group)));
  if(Group>=0 && Group<4)WheelOffsets[Group]=Pivot;
  if(Group==4){SteeringPivot=Pivot;
   if(VehicleIndex==1){const auto& Axis=O->GetArrayField(TEXT("axis"));SteerAxis=FVector(Axis[0]->AsNumber(),Axis[1]->AsNumber(),Axis[2]->AsNumber());}
  }
  if(Group==5 || Group==6){
   const int32 GaugeIndex=Group-5;
   const auto& Axis=O->GetArrayField(TEXT("axis"));
   GaugeAxes[GaugeIndex]=FVector(Axis[0]->AsNumber(),Axis[1]->AsNumber(),Axis[2]->AsNumber()).GetSafeNormal();
   GaugeZero[GaugeIndex]=float(O->GetNumberField(TEXT("zero_angle")));
   double Sweep=-270.;O->TryGetNumberField(TEXT("sweep"),Sweep);GaugeSweep[GaugeIndex]=float(Sweep);
   GaugeNeedles[GaugeIndex]=Mesh;
   Mesh->SetCastShadow(false);
  }
  if(Group>=7 && Group<=9)AddMirror(Mesh,Group-7,Pivot);
  Visuals.Add(Mesh);
 }
 AssetLoaded=Visuals.Num()==Root->GetArrayField(TEXT("parts")).Num() && Visuals.Num()>0 && MirrorCaptures.Num()==3;
}
void ACiazPawn::SetFrozen(bool V){
 if(!V&&!AssetLoaded)return;
 if(Frozen==V)return;
 Frozen=V;
 if(V){
  for(auto& Point:PreviousSkidPoint)Point.Reset();
  PausedLinear=Body->GetPhysicsLinearVelocity();PausedAngular=Body->GetPhysicsAngularVelocityInDegrees();
  Throttle=Brake=0;Body->SetSimulatePhysics(false);
  for(auto& Corner:SuspensionCorners)Corner.Release();
  EngineAudio->Stop();LoadAudio->Stop();BeepAudio->Stop();
 }else{
  Body->SetSimulatePhysics(true);Body->SetPhysicsLinearVelocity(PausedLinear);
  Body->SetPhysicsAngularVelocityInDegrees(PausedAngular);
 }
}
void ACiazPawn::ResetAt(FVector P,float Yaw){
 if(SkidMarks)SkidMarks->ClearInstances();
 NextSkidMark=0;
 for(auto& Point:PreviousSkidPoint)Point.Reset();
 SetFrozen(true);PausedLinear=PausedAngular=FVector::ZeroVector;SetActorLocationAndRotation(P,FRotator(0,Yaw,0),false,nullptr,ETeleportType::TeleportPhysics);
 OrbitIdle=0;ChaseYaw=Yaw;ChasePitch=-24;CockpitYaw=InteriorCameraRotation.Yaw;CockpitPitch=-5+InteriorCameraRotation.Pitch;ApplyCamera();
 Drive.reset();Steering.angle=0;Throttle=Brake=Clutch=0;Handbrake=true;Speed=0;RearGripRecovery=0;
 for(int i=0;i<4;i++){Spin[i]=0;WheelTravel[i]=-RideHeightOffsetCm;WheelSteer[i]=0;SuspensionCorners[i]=VehicleDynamics::SuspensionState{};}
 SensorClock=BeepClock=MirrorClock=0;for(float& Distance:Sensors)Distance=300;
 UpdateWheelVisuals();UpdateSensors();
 GaugeValues[0]=0;GaugeValues[1]=float(Drive.rpm);UpdateGauges(0);
}
void ACiazPawn::ToggleCamera(){
 Cockpit=!Cockpit;OrbitIdle=0;ApplyCamera();
}
void ACiazPawn::ApplyCamera(){
 Boom->bUsePawnControlRotation=false;
 Boom->SetAbsolute(false,!Cockpit,false);
 Boom->bEnableCameraRotationLag=false;
 Boom->bDoCollisionTest=!Cockpit;
 if(Cockpit){
  Boom->TargetArmLength=0;Boom->SetRelativeLocation(CockpitPosition+InteriorCameraOffset);
  Boom->SetRelativeRotation(FRotator(CockpitPitch,CockpitYaw,0));
  Boom->bEnableCameraLag=false;Camera->SetFieldOfView(InteriorFOV);
 }else{
  Boom->TargetArmLength=720;Boom->SetRelativeLocation(FVector(0,0,120));
  Boom->SetWorldRotation(FRotator(ChasePitch,ChaseYaw,0));
  Boom->bEnableCameraLag=true;Camera->SetFieldOfView(72);
 }
}
void ACiazPawn::SetInteriorFOV(float Value){
 InteriorFOV=FMath::Clamp(Value,MinInteriorFOV,MaxInteriorFOV);
 if(Cockpit)Camera->SetFieldOfView(InteriorFOV);
}
void ACiazPawn::SetInteriorCamera(FVector Offset,FRotator Rotation){
 InteriorCameraOffset=Offset;InteriorCameraRotation=Rotation;
 CockpitYaw=Rotation.Yaw;CockpitPitch=-5+Rotation.Pitch;
 ApplyCamera();
}
void ACiazPawn::MouseLook(float X,float Y,bool LookBack,float Delta){
 // Mouse deltas already represent movement this frame: do not multiply by DT.
 constexpr float Sensitivity=.15f;
 if(Cockpit){
  CockpitYaw=FMath::Clamp(CockpitYaw+X*Sensitivity,-135.f,135.f);
  CockpitPitch=FMath::Clamp(CockpitPitch+Y*Sensitivity,-55.f,65.f);
  // The look-back shortcut also respects the 270-degree head-turn limit.
  const float Yaw=LookBack?(CockpitYaw<0?-135.f:135.f):CockpitYaw;
  Boom->SetRelativeRotation(FRotator(CockpitPitch,Yaw,0));
 }else{
  const bool Looking=FMath::Abs(X)+FMath::Abs(Y)>.01f;
  OrbitIdle=(Looking||LookBack)?0.f:OrbitIdle+Delta;
  if(OrbitIdle>.75f){
   const float Rate=FMath::Clamp((FMath::Abs(Speed)-.05f)*.12f,0.f,1.2f);
   ChaseYaw+=FMath::FindDeltaAngleDegrees(ChaseYaw,GetActorRotation().Yaw)*(1.f-FMath::Exp(-Rate*Delta));
  }
  ChaseYaw=FRotator::NormalizeAxis(ChaseYaw+X*Sensitivity);
  ChasePitch=FMath::Clamp(ChasePitch+Y*Sensitivity,-75.f,10.f);
  Boom->SetWorldRotation(FRotator(ChasePitch,ChaseYaw+(LookBack?180.f:0.f),0));
 }
}
void ACiazPawn::ToggleLights(){
 HeadlightsOn=!HeadlightsOn;
 for(USpotLightComponent* L:Headlights)L->SetVisibility(HeadlightsOn);
 for(UMaterialInstanceDynamic* M:InstrumentMaterials)M->SetScalarParameterValue(TEXT("Backlight"),HeadlightsOn?1.2f:0.f);
}
void ACiazPawn::Physics(float DT){
 if(DT<=0)return;
 RearGripRecovery=Handbrake?0.f:FMath::Min(1.f,RearGripRecovery+DT/.22f);
 const FTransform Transform=GetActorTransform();const FVector Up=GetActorUpVector();
 const FVector Velocity=Body->GetPhysicsLinearVelocity();
 Speed=FVector::DotProduct(Velocity,GetActorForwardVector())/100.f;
 // Advance engine state in small steps even when a rendering frame is long.
 float Remaining=DT;DriveForce=0;
 while(Remaining>0.f){const float Step=FMath::Min(Remaining,1.f/120.f);
  DriveForce+=float(Drive.step(Step,Speed,Throttle,Brake,Clutch))*Step/DT;Remaining-=Step;}
 struct FContact{bool Grounded=false,OnAsphalt=false;FVector Point,Normal,Forward,Right,ContactVelocity;float Compression=0,Load=0;};
 FContact Contacts[4];Slip=0;
 FCollisionQueryParams Params(SCENE_QUERY_STAT(Tires),false,this);
 const float TotalMass=Body->GetMass();
 const FVector Gravity(0,0,GetWorld()->GetGravityZ()/100.f);
 for(int32 Index=0;Index<4;++Index){
  auto& Contact=Contacts[Index];
  WheelSteer[Index]=Index<2?float(VehicleDynamics::Ackermann(Steering.angle,WheelOffsets[Index].Y,FMath::Abs(WheelOffsets[0].X-WheelOffsets[2].X)/100.,FMath::Abs(WheelOffsets[Index].Y)/100.)):0.f;
  const FVector Mount=Transform.TransformPosition(WheelOffsets[Index]+FVector(0,0,25-RideHeightOffsetCm));
  const FVector WheelForward=GetActorForwardVector().RotateAngleAxis(FMath::RadiansToDegrees(WheelSteer[Index]),Up);
  const FVector WheelRight=FVector::CrossProduct(Up,WheelForward).GetSafeNormal();
  const float Radius=WheelRadius,MaxLength=37.f;
  float BestLength=MaxLength;FHitResult BestHit;float BestOffset=0;bool Supported=false;
  int32 BestProbe=-1;float CentreLength=1e6f,ShoulderLength[2]={1e6f,1e6f};FVector CentrePoint=FVector::ZeroVector,ShoulderPoint[2]={FVector::ZeroVector,FVector::ZeroVector};
  // Seven longitudinal samples model the lower tire arc; two shoulder rays
  // detect one-sided support without pretending the tire is a wide sphere.
  const float Offsets[]={-.95f,-.75f,-.45f,0.f,.45f,.75f,.95f,0.f,0.f};
  for(int32 Probe=0;Probe<9;++Probe){
   const float Offset=Offsets[Probe]*Radius;
   const float Side=Probe==7?-8.f:(Probe==8?8.f:0.f);
   const FVector ProbeStart=Mount+WheelForward*Offset+WheelRight*Side;
   FHitResult Hit;
   if(!GetWorld()->LineTraceSingleByChannel(Hit,ProbeStart,ProbeStart-Up*(MaxLength+Radius),ECC_Visibility,Params))continue;
   if(Hit.bStartPenetrating||FVector::DotProduct(Hit.ImpactNormal,Up)<.45f)continue;
   const float Length=float(VehicleDynamics::TireEnvelopeLength(Hit.Distance/100.,Offset/100.,Radius/100.))*100.f;
   if(Probe==3){CentreLength=Length;CentrePoint=Hit.ImpactPoint;}
   else if(Probe>=7){ShoulderLength[Probe-7]=Length;ShoulderPoint[Probe-7]=Hit.ImpactPoint;}
   if(Length<BestLength){BestLength=Length;BestHit=Hit;BestOffset=Offset;BestProbe=Probe;Supported=true;}
  }
  // Beta 1.7.8: when support comes from the centre line or a shoulder, apply the
  // wheel load at a point that moves continuously with how much lower each
  // shoulder is. Snapping to the lowest probe shifted the load +/-8 cm on a
  // microscopic roll and made the parked car rock (and the hold timer restart).
  if(Supported&&(BestProbe==3||BestProbe>=7)&&CentreLength<1e5f){
   FVector Blended=CentrePoint;
   for(int32 Shoulder=0;Shoulder<2;++Shoulder)if(ShoulderLength[Shoulder]<1e5f)
    Blended+=(ShoulderPoint[Shoulder]-CentrePoint)*float(VehicleDynamics::ShoulderWeight(CentreLength/100.,ShoulderLength[Shoulder]/100.));
   BestHit.ImpactPoint=Blended;
  }
  auto& Corner=SuspensionCorners[Index];
  if(!Supported){PreviousSkidPoint[Index].Reset();Corner.Release();WheelTravel[Index]=FMath::FInterpConstantTo(WheelTravel[Index],-12.f-RideHeightOffsetCm,DT,60.f);continue;}
  const float Length=FMath::Clamp(BestLength,5.f,MaxLength);
  Contact.Grounded=true;Contact.Point=BestHit.ImpactPoint;
  const AActor* Surface=BestHit.GetActor();
  Contact.OnAsphalt=Surface && Surface->ActorHasTag(TEXT("Ground"));
  // Contact normal follows the tire arc around a curb edge. This provides
  // approach resistance and lift through forces, not a chassis teleport.
  Contact.Normal=(Up*FMath::Sqrt(FMath::Max(0.f,Radius*Radius-BestOffset*BestOffset))-WheelForward*BestOffset).GetSafeNormal();
  if(FMath::Abs(BestOffset)<.01f)Contact.Normal=BestHit.ImpactNormal;
  Contact.Compression=(25.f-Length)/100.f;
  Contact.ContactVelocity=Body->GetPhysicsLinearVelocityAtPoint(Contact.Point)/100.f;
  const float SprungMass=TotalMass*(Index<2?FrontWeight:1.f-FrontWeight)*.5f;
  const float InitialRate=-FVector::DotProduct(Contact.ContactVelocity,Up);
  Contact.Load=float(Corner.Step(Length/100.,InitialRate,DT,SprungMass,Index<2,SuspensionScale));
  Contact.Forward=FVector::VectorPlaneProject(WheelForward,Contact.Normal).GetSafeNormal();
  Contact.Right=FVector::CrossProduct(Contact.Normal,Contact.Forward).GetSafeNormal();
  WheelTravel[Index]=25.f-Length-RideHeightOffsetCm;
 }
 // Transfer support between the two tires of an axle, preserving total support.
 for(int32 Axle=0;Axle<2;++Axle){
  auto& Left=Contacts[Axle*2];auto& Right=Contacts[Axle*2+1];
  if(Left.Grounded&&Right.Grounded){
   float Transfer=(Left.Compression-Right.Compression)*(Axle==0?6500.f:4500.f)*SuspensionScale;
   Transfer=FMath::Clamp(Transfer,-Left.Load,Right.Load);
   Left.Load+=Transfer;Right.Load-=Transfer;
  }
 }
 for(int32 Index=0;Index<4;++Index){
  const auto& Contact=Contacts[Index];if(!Contact.Grounded)continue;
  const float NormalLoad=Contact.Load/FMath::Max(.3f,float(FVector::DotProduct(Contact.Normal,Up)));
  VehicleDynamics::TireInput Input;
  Input.dt=DT;Input.load=NormalLoad;Input.mass=TotalMass*(Index<2?FrontWeight:1.f-FrontWeight)*.5;
  Input.longSpeed=FVector::DotProduct(Contact.ContactVelocity,Contact.Forward);
  Input.sideSpeed=FVector::DotProduct(Contact.ContactVelocity,Contact.Right);
  Input.drive=Index<2?DriveForce*.5:0;Input.brake=Brake;
  Input.rear=Index>=2;Input.handbrake=Handbrake;
  Input.rearGripRecovery=RearGripRecovery;Input.corneringScale=VehicleIndex==1?.84:1.;
  Input.gravityLong=FVector::DotProduct(Gravity,Contact.Forward)*Input.mass;
  Input.gravitySide=FVector::DotProduct(Gravity,Contact.Right)*Input.mass;
  const auto Force=VehicleDynamics::Tire(Input);
  if(Contact.OnAsphalt && Force.sliding)AddSkidMark(Index,Contact.Point);
  else PreviousSkidPoint[Index].Reset();
  Body->AddForceAtLocation((Contact.Normal*NormalLoad+Contact.Forward*Force.longitudinal+Contact.Right*Force.lateral)*100.f,Contact.Point);
  // Rear wheels stop rotating while the handbrake is engaged, even if the
  // chassis is sliding. Spin returns progressively after releasing it.
  const float SpinFactor=Index>=2?(Handbrake?0.f:RearGripRecovery):1.f;
  Spin[Index]=FMath::Fmod(Spin[Index]+FMath::RadiansToDegrees(float(Input.longSpeed)/(WheelRadius/100.f)*DT)*SpinFactor,360.f);
  Slip=FMath::Max(Slip,float(FMath::Abs(Input.sideSpeed)));
 }
 // Aerodynamic drag in SI units, converted once to Unreal force units.
 const FVector VelocityMetres=Velocity/100.f;
 Body->AddForce(-VelocityMetres*VelocityMetres.Size()*.5f*1.225f*.30f*2.2f*100.f);
 UpdateWheelVisuals();
}
void ACiazPawn::AddSkidMark(int32 Wheel,const FVector& Point){
 constexpr int32 MaxMarks=1024;
 constexpr double MinSpacing=12.;
 constexpr double MaxSpacing=180.;
 auto& Previous=PreviousSkidPoint[Wheel];
 if(!Previous.IsSet()){
  Previous=Point;
  return;
 }
 const FVector Delta=Point-Previous.GetValue();
 const double Length=Delta.Size2D();
 if(Length<MinSpacing)return;
 const FVector Centre=(Point+Previous.GetValue())*.5+FVector(0,0,.2);
 Previous=Point;
 if(Length>MaxSpacing)return;
 if(!SkidMarks){
  auto* Mesh=LoadObject<UStaticMesh>(nullptr,TEXT("/Engine/BasicShapes/Cube.Cube"));
  auto* Material=LoadObject<UMaterialInterface>(nullptr,TEXT("/Game/Materials/M_Solid.M_Solid"));
  if(!Mesh || !Material)return;
  SkidMarks=NewObject<UInstancedStaticMeshComponent>(this,TEXT("SkidMarks"));
  AddInstanceComponent(SkidMarks);
  SkidMarks->SetMobility(EComponentMobility::Movable);
  SkidMarks->SetCollisionProfileName(TEXT("NoCollision"));
  SkidMarks->SetGenerateOverlapEvents(false);
  SkidMarks->SetCanEverAffectNavigation(false);
  SkidMarks->SetCastShadow(false);
  SkidMarks->SetStaticMesh(Mesh);
  auto* Rubber=UMaterialInstanceDynamic::Create(Material,SkidMarks);
  Rubber->SetVectorParameterValue(TEXT("Tint"),FLinearColor(.018f,.016f,.014f));
  Rubber->SetScalarParameterValue(TEXT("Roughness"),.96f);
  SkidMarks->SetMaterial(0,Rubber);
  SkidMarks->RegisterComponent();
 }
 const FRotator Rotation(0,FMath::RadiansToDegrees(FMath::Atan2(Delta.Y,Delta.X)),0);
 const FTransform Segment(Rotation,Centre,FVector((Length+1.)/100.,.15,.001));
 if(SkidMarks->GetInstanceCount()<MaxMarks)SkidMarks->AddInstance(Segment,true);
 else SkidMarks->UpdateInstanceTransform(NextSkidMark,Segment,true,true,true);
 NextSkidMark=(NextSkidMark+1)%MaxMarks;
}
void ACiazPawn::UpdateWheelVisuals(){
 for(UProceduralMeshComponent* Mesh:Visuals){
  const int G=FCString::Atoi(*Mesh->ComponentTags[0].ToString());
  if(G>=0&&G<4){
   Mesh->SetRelativeLocation(WheelOffsets[G]+FVector(0,0,WheelTravel[G]));
   const FQuat Steer(FVector::UpVector,WheelSteer[G]);
   const FQuat Roll(FVector::RightVector,FMath::DegreesToRadians(Spin[G]));
   Mesh->SetRelativeRotation(Steer*Roll);
  }else if(G==4){
   // Axis and rim centre measured from the supplied Ciaz steering-wheel geometry.
   const FVector Axis=SteerAxis.GetSafeNormal();
   const FVector CentreOffset=SteerCentreOffset;
   const FQuat Rotation(Axis,FMath::DegreesToRadians(-float(Steering.angle)*450.f));
   Mesh->SetRelativeLocation(SteeringPivot+CentreOffset-Rotation.RotateVector(CentreOffset));
   Mesh->SetRelativeRotation(Rotation);
  }
 }
}
void ACiazPawn::UpdateSensors(){
 FCollisionQueryParams Params(SCENE_QUERY_STAT(ParkingSensors),false,this);
 for(int z=0;z<6;z++){
  bool Front=z<3;int Lane=z%3;float Side=(Lane-1)*65.f;
  FVector Start=GetActorTransform().TransformPosition(FVector((Front?1.f:-1.f)*(VehicleLength*.5f+1.f),Side,-35));
  Sensors[z]=300;
  for(int ray=-1;ray<=1;ray++){
   float A=((Lane-1)*16.f+ray*10.f)*(Front?1.f:-1.f);
   FVector Direction=(Front?GetActorForwardVector():-GetActorForwardVector()).RotateAngleAxis(A,GetActorUpVector());
   FHitResult H;
   if(GetWorld()->SweepSingleByChannel(H,Start,Start+Direction*250,FQuat::Identity,ECC_Visibility,FCollisionShape::MakeSphere(6),Params))
    Sensors[z]=FMath::Min(Sensors[z],H.Distance);
  }
 }
}
void ACiazPawn::Tick(float DT){
 Super::Tick(DT);DT=FMath::Clamp(DT,0.f,.1f);if(Frozen)return;
 Physics(DT);UpdateGauges(DT);UpdateMirrors(DT);
 SensorClock+=DT;if(SensorClock>.05f){UpdateSensors();SensorClock=0;}
 float Nearest=300;for(float D:Sensors)Nearest=FMath::Min(Nearest,D);
 BeepClock+=DT;const float Interval=FMath::GetMappedRangeValueClamped(FVector2D(30,220),FVector2D(.12,.85),Nearest);
 bool Tone=FMath::Abs(Speed)<4 && Nearest<220 && (Nearest<30 || FMath::Fmod(BeepClock,Interval)<.08f);
 auto* GM=Cast<AParkingGameMode>(GetWorld()->GetAuthGameMode());float Volume=GM&&GM->Save?GM->Save->MasterVolume:.7f;
 BeepAudio->SetVolumeMultiplier(Volume*.45f);
 if(Tone&&!BeepAudio->IsPlaying())BeepAudio->Play();
 if(!Tone&&BeepAudio->IsPlaying())BeepAudio->Stop();
 if(Drive.running){
  if(!EngineAudio->IsPlaying())EngineAudio->Play();
  if(!LoadAudio->IsPlaying())LoadAudio->Play();
  LoadAudio->SetPitchMultiplier(FMath::Clamp(float(Drive.rpm/2200.),.65f,2.3f));
  LoadAudio->SetVolumeMultiplier(Volume*Throttle*.5f);
  EngineAudio->SetPitchMultiplier(FMath::Clamp(float(Drive.rpm/1100.),.65f,3.f));
  EngineAudio->SetVolumeMultiplier(Volume*(.25f+.5f*Throttle));
 }else {EngineAudio->Stop();LoadAudio->Stop();}
}
void ACiazPawn::OnHit(UPrimitiveComponent*,AActor* Other,UPrimitiveComponent*,FVector Impulse,const FHitResult& Hit){
 if(Frozen||!Other||!Other->ActorHasTag(TEXT("Obstacle")))return;
 auto* GM=Cast<AParkingGameMode>(GetWorld()->GetAuthGameMode());
 if(GM)GM->Collision(Other,FMath::Max(FMath::Abs(Speed),float(Impulse.Size())/(VehicleMass*100.f)));
}

#include "CiazCollision.inl"

void ACiazPawn::UpdateGauges(float Delta){
 const float Targets[2]={FMath::Abs(Speed)*3.6f,Drive.running?float(Drive.rpm):0.f};
 const float Ranges[2]={220.f,8000.f};
 for(int32 GaugeIndex=0;GaugeIndex<2;++GaugeIndex){
  const float Target=FMath::Clamp(Targets[GaugeIndex],0.f,Ranges[GaugeIndex]);
  // Exponential smoothing is independent of the frame rate and cannot overshoot.
  const float Blend=1.f-FMath::Exp(-10.f*FMath::Max(Delta,0.f));
  GaugeValues[GaugeIndex]+=Blend*(Target-GaugeValues[GaugeIndex]);
  const float Angle=GaugeZero[GaugeIndex]+GaugeSweep[GaugeIndex]*GaugeValues[GaugeIndex]/Ranges[GaugeIndex];
  for(UProceduralMeshComponent* Needle:Visuals){
   if(Needle->ComponentTags.Num()>0 && FCString::Atoi(*Needle->ComponentTags[0].ToString())==GaugeIndex+5)
    Needle->SetRelativeRotation(FQuat(GaugeAxes[GaugeIndex],FMath::DegreesToRadians(Angle)));
  }
 }
}

void ACiazPawn::AddMirror(UProceduralMeshComponent* Mesh,int32 Index,FVector Pivot){
 auto* MirrorBase=LoadObject<UMaterialInterface>(nullptr,TEXT("/Game/Materials/M_Mirror.M_Mirror"));
 if(!MirrorBase)return;
 auto* Target=NewObject<UTextureRenderTarget2D>(this);
 Target->RenderTargetFormat=RTF_RGBA8;Target->ClearColor=FLinearColor(.12f,.15f,.18f);
 Target->InitAutoFormat(Index==2?384:256,128);
 auto* Capture=NewObject<USceneCaptureComponent2D>(this);AddInstanceComponent(Capture);
 Capture->SetupAttachment(Body);Capture->SetRelativeLocation(Pivot-FVector(6,0,0));
 Capture->SetRelativeRotation(FRotator(-3,Index==0?195.f:(Index==1?165.f:180.f),0));
 Capture->FOVAngle=Index==2?60.f:65.f;Capture->TextureTarget=Target;
 Capture->CaptureSource=ESceneCaptureSource::SCS_FinalColorLDR;
 // A small mirror-only exposure lift keeps reflected parking details readable.
 Capture->PostProcessSettings.bOverride_AutoExposureBias=true;
 Capture->PostProcessSettings.AutoExposureBias=.4f;
 Capture->PostProcessBlendWeight=1.f;
 Capture->bCaptureEveryFrame=false;Capture->bCaptureOnMovement=false;
 Capture->MaxViewDistanceOverride=6500;
 Capture->ShowFlags.SetMotionBlur(false);Capture->ShowFlags.SetAmbientOcclusion(false);
 Capture->ShowFlags.SetDynamicShadows(false);
 Capture->HiddenActors.Add(this);Capture->RegisterComponent();
 auto* Mat=UMaterialInstanceDynamic::Create(MirrorBase,this);
 Mat->SetTextureParameterValue(TEXT("MirrorTexture"),Target);Mesh->SetMaterial(0,Mat);
 Mesh->SetCastShadow(false);Materials.Add(Mat);
 MirrorCaptures.Add(Capture);MirrorTargets.Add(Target);
}
void ACiazPawn::UpdateMirrors(float Delta){
 if(MirrorCaptures.Num()!=3)return;
 const auto* GameMode=Cast<AParkingGameMode>(GetWorld()->GetAuthGameMode());
 const int32 Quality=GameMode&&GameMode->Save?GameMode->Save->Quality:0;
 if(MirrorQuality!=Quality){
  MirrorQuality=Quality;
  for(int32 Index=0;Index<3;++Index){
   const int32 Scale=Quality==0?1:2;
   MirrorTargets[Index]->ResizeTarget((Index==2?384:256)*Scale,128*Scale);
  }
 }
 // One capture per frame at most. Rotate through mirrors to spread GPU cost.
 const float Rate=Cockpit?(Quality==0?8.f:15.f):2.f;
 MirrorClock+=Delta;
 if(MirrorClock>=1.f/(Rate*3.f)){
  MirrorClock=FMath::Fmod(MirrorClock,1.f/(Rate*3.f));MirrorCaptures[NextMirror]->CaptureScene();NextMirror=(NextMirror+1)%3;
 }
}

FString ACiazPawn::VehicleFolder() const{return FPaths::ProjectContentDir()/(VehicleIndex==1?TEXT("SwiftData"):TEXT("VehicleData"));}
void ACiazPawn::ConfigureVehicle(){
 if(VehicleIndex!=1)return;
 VehicleLength=384;VehicleWidth=185;VehicleMass=930;WheelRadius=30.495f;FrontWeight=.61f;
 // Eye position behind the full-detail model's steering rim and above its hub.
 SuspensionScale=.76f;CockpitPosition=FVector(-20,33,46);SteerCentreOffset=FVector::ZeroVector;
 Drive.swift=true;Drive.tireRadius=WheelRadius/100.;
}
void ACiazPawn::BuildSwiftCollision(){
 FString Text;TSharedPtr<FJsonObject> Root;
 if(!FFileHelper::LoadFileToString(Text,*(VehicleFolder()/TEXT("collision.json")))||!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),Root)||!Root.IsValid())return;
 const TArray<TSharedPtr<FJsonValue>>* Entries=nullptr;
 if(!Root->TryGetArrayField(TEXT("hulls"),Entries)||Entries->Num()==0||Entries->Num()>128)return;
 TArray<TArray<FVector>> Hulls;
 for(const auto& Entry:*Entries){
  if(!Entry.IsValid()||Entry->Type!=EJson::Array||Entry->AsArray().Num()<4||Entry->AsArray().Num()>256)return;
  TArray<FVector> Hull;for(const auto& Point:Entry->AsArray()){
   if(!Point.IsValid()||Point->Type!=EJson::Array||!VehicleDataValidation::Vector(Point->AsArray()))return;
   const auto& V=Point->AsArray();Hull.Add(FVector(V[0]->AsNumber(),V[1]->AsNumber(),V[2]->AsNumber()));
  }
  bool HasVolume=false;
  for(int32 A=1;A<Hull.Num()&&!HasVolume;++A)for(int32 B=A+1;B<Hull.Num()&&!HasVolume;++B)
   for(int32 C=B+1;C<Hull.Num();++C)if(FMath::Abs(FVector::DotProduct(FVector::CrossProduct(Hull[A]-Hull[0],Hull[B]-Hull[0]),Hull[C]-Hull[0]))>.001){HasVolume=true;break;}
  if(!HasVolume)return;Hulls.Add(Hull);
 }
 TArray<FVector> BoundsVertices;TArray<int32> BoundsTriangles;
 for(const auto& Hull:Hulls){const int32 BaseIndex=BoundsVertices.Num();BoundsVertices.Append(Hull);
  for(int32 I=1;I+1<Hull.Num();++I)BoundsTriangles.Append({BaseIndex,BaseIndex+I,BaseIndex+I+1});
 }
 Body->CreateMeshSection_LinearColor(0,BoundsVertices,BoundsTriangles,TArray<FVector>(),TArray<FVector2D>(),TArray<FLinearColor>(),TArray<FProcMeshTangent>(),false);
 Body->SetMeshSectionVisible(0,false);Body->SetCollisionConvexMeshes(Hulls);CollisionReady=true;
}
