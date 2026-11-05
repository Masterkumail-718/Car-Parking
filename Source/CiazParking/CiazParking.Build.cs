using UnrealBuildTool;
public class CiazParking : ModuleRules {
 public CiazParking(ReadOnlyTargetRules Target):base(Target) {
  PCHUsage=PCHUsageMode.UseExplicitOrSharedPCHs;
  PublicDependencyModuleNames.AddRange(new string[]{"Core","CoreUObject","Engine","InputCore","ProceduralMeshComponent","Json","JsonUtilities","PhysicsCore","ImageWrapper","RenderCore","RHI"});
  PrivateDependencyModuleNames.Add("SlateCore");
  if(Target.Platform==UnrealTargetPlatform.Win64) PublicSystemLibraries.AddRange(new string[]{"dinput8.lib","dxguid.lib","user32.lib"});
 }
}
