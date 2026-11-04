#pragma once
#include "CoreMinimal.h"
#include "Dom/JsonObject.h"
namespace VehicleDataValidation {
inline bool Number(const TSharedPtr<FJsonValue>& V){return V.IsValid()&&V->Type==EJson::Number&&FMath::IsFinite(V->AsNumber());}
inline bool Vector(const TArray<TSharedPtr<FJsonValue>>& A){
 if(A.Num()!=3)return false;
 for(const auto& V:A)if(!Number(V)||FMath::Abs(V->AsNumber())>10000.)return false;
 return true;
}
inline bool VectorField(const TSharedPtr<FJsonObject>& O,const TCHAR* Key){
 const TArray<TSharedPtr<FJsonValue>>* A=nullptr;return O->TryGetArrayField(Key,A)&&Vector(*A);
}
inline bool Scalar(const TSharedPtr<FJsonObject>& O,const TCHAR* Key){double V=0;return O->TryGetNumberField(Key,V)&&FMath::IsFinite(V);}
inline bool Manifest(const TSharedPtr<FJsonObject>& Root,bool Swift){
 const TArray<TSharedPtr<FJsonValue>>* Mats=nullptr;const TArray<TSharedPtr<FJsonValue>>* Parts=nullptr;
 if(!Root.IsValid()||!Root->TryGetArrayField(TEXT("materials"),Mats)||!Root->TryGetArrayField(TEXT("parts"),Parts)||Mats->Num()==0||Mats->Num()>256||Parts->Num()==0||Parts->Num()>512)return false;
 for(const auto& Entry:*Mats){
  if(!Entry.IsValid()||Entry->Type!=EJson::Object)return false;const auto O=Entry->AsObject();
  FString Texture;bool Glass=false;
  if(!VectorField(O,TEXT("color"))||!O->TryGetBoolField(TEXT("glass"),Glass)||!O->TryGetStringField(TEXT("texture"),Texture)||!Scalar(O,TEXT("roughness"))||!Scalar(O,TEXT("metallic")))return false;
 }
 bool Groups[10]={};
 for(const auto& Entry:*Parts){
  if(!Entry.IsValid()||Entry->Type!=EJson::Object)return false;const auto O=Entry->AsObject();
  FString File;double Group=0,Mat=0;
  if(!O->TryGetStringField(TEXT("file"),File)||File.IsEmpty()||File.Contains(TEXT(".."))||!VectorField(O,TEXT("pivot"))||!O->TryGetNumberField(TEXT("group"),Group)||!O->TryGetNumberField(TEXT("material"),Mat))return false;
  if(!FMath::IsFinite(Group)||!FMath::IsFinite(Mat)||Group<-1||Group>9||Mat<0||Mat>=Mats->Num()||Group!=double(int32(Group))||Mat!=double(int32(Mat)))return false;
  const int32 G=int32(Group);if(G>=0)Groups[G]=true;
  if(G==5||G==6||(Swift&&G==4)){
   if(!VectorField(O,TEXT("axis")))return false;const auto& A=O->GetArrayField(TEXT("axis"));
   if(FVector(A[0]->AsNumber(),A[1]->AsNumber(),A[2]->AsNumber()).IsNearlyZero())return false;
  }
  if((G==5||G==6)&&!Scalar(O,TEXT("zero_angle")))return false;
 }
 for(bool Present:Groups)if(!Present)return false;
 return true;
}
}
