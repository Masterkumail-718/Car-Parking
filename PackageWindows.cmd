@echo off
setlocal
cd /d "%~dp0"
set "CIAZ_ENGINE=%~1"
if not defined CIAZ_ENGINE set "CIAZ_ENGINE=D:\Unreal\UE_5.4"
set "CIAZ_OUTPUT=%~2"
if not defined CIAZ_OUTPUT set "CIAZ_OUTPUT=%~dp0Packaged"
if not exist "%CIAZ_ENGINE%\Engine\Build\BatchFiles\RunUAT.bat" (
 echo Unreal Engine was not found at %CIAZ_ENGINE%.
 echo Run PackageWindows.cmd "D:\Unreal\UE_5.4"
 exit /b 1
)
echo Close Unreal Editor before continuing. Build output: %CIAZ_OUTPUT%
call "%~dp0SetupProject.cmd" "%CIAZ_ENGINE%" --no-editor
if errorlevel 1 exit /b 1
call "%CIAZ_ENGINE%\Engine\Build\BatchFiles\RunUAT.bat" BuildCookRun -project="%~dp0CiazParking.uproject" -noP4 -platform=Win64 -clientconfig=Shipping -build -cook -map=/Game/Maps/Parking -stage -pak -package -archive -archivedirectory="%CIAZ_OUTPUT%" -prereqs -utf8output
if errorlevel 1 (
 echo Packaging failed. Keep the first error and the AutomationTool log.
 exit /b 1
)
if not exist "%CIAZ_OUTPUT%\Windows\CiazParking.exe" (
 echo UAT completed but the expected launcher was not found. Inspect %CIAZ_OUTPUT%.
 exit /b 1
)
echo SUCCESS: %CIAZ_OUTPUT%\Windows\CiazParking.exe
echo Keep the complete Windows folder together. The EXE alone is not the game.
endlocal
