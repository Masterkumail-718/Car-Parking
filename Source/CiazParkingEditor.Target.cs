using UnrealBuildTool;
public class CiazParkingEditorTarget : TargetRules {
 public CiazParkingEditorTarget(TargetInfo Target):base(Target){
  Type=TargetType.Editor;DefaultBuildSettings=BuildSettingsVersion.V5;IncludeOrderVersion=EngineIncludeOrderVersion.Unreal5_4;
  if(Target.Platform==UnrealTargetPlatform.Win64) WindowsPlatform.CompilerVersion="14.38.33130";
  ExtraModuleNames.Add("CiazParking");
 }
}
