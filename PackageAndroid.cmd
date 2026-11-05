@echo off
setlocal DisableDelayedExpansion
if /i "%~1"=="--help" goto usage
set "CIAZ_INTERACTIVE="
if "%~1"=="" set "CIAZ_INTERACTIVE=1"
cd /d "%~dp0" || goto failed
set "CIAZ_TAG=%~1"
set "CIAZ_ENGINE=%~2"
if not defined CIAZ_ENGINE set "CIAZ_ENGINE=D:\Unreal\UE_5.4"
set "CIAZ_REPO=Masterkumail-718/Car-Parking"

if not exist "%CIAZ_ENGINE%\Engine\Build\BatchFiles\RunUAT.bat" (
 echo Unreal Engine was not found at "%CIAZ_ENGINE%".
 goto failed
)
if exist "%CIAZ_ENGINE%\Engine\Build\InstalledBuild.txt" if not exist "%CIAZ_ENGINE%\Engine\Binaries\Android\UnrealGame.target" (
 echo Install the Android target platform component for Unreal Engine 5.4.4.
 goto failed
)
if not exist "%~dp0Content\Maps\Parking.umap" (
 echo Parking.umap is missing. Run SetupProject.cmd before packaging.
 goto failed
)
if not exist "%~dp0Content\Obstacles\SM_Marking.uasset" (
 echo The Level 12 marking asset is missing. Run SetupProject.cmd before packaging.
 goto failed
)

where gh.exe >nul 2>&1
if errorlevel 1 (
 echo Install GitHub CLI and run gh auth login.
 goto failed
)
gh auth status --hostname github.com >nul 2>&1
if errorlevel 1 (
 echo Sign in to GitHub CLI with gh auth login.
 goto failed
)
set "CIAZ_GIT="
for /f "delims=" %%G in ('where git.exe 2^>nul') do if not defined CIAZ_GIT set "CIAZ_GIT=%%G"
if not defined CIAZ_GIT if exist "%ProgramFiles%\Git\cmd\git.exe" set "CIAZ_GIT=%ProgramFiles%\Git\cmd\git.exe"
if not defined CIAZ_GIT if exist "%USERPROFILE%\.cache\codex-runtimes\codex-primary-runtime\dependencies\native\git\cmd\git.exe" set "CIAZ_GIT=%USERPROFILE%\.cache\codex-runtimes\codex-primary-runtime\dependencies\native\git\cmd\git.exe"
if not defined CIAZ_GIT (
 echo Git for Windows was not found. Install it and reopen this script.
 goto failed
)
if defined CIAZ_INTERACTIVE (
 echo Enter a fresh GitHub release tag, for example android-v1.7.17.
 echo The APK will be published as a prerelease to %CIAZ_REPO%.
 set /p "CIAZ_TAG=Release tag (leave blank to cancel): "
)
if not defined CIAZ_TAG (
 echo Packaging cancelled.
 goto failed
)
powershell.exe -NoProfile -Command "if ($env:CIAZ_TAG -cnotmatch '^[A-Za-z0-9][A-Za-z0-9._-]*$') { exit 1 }"
if errorlevel 1 (
 echo Use letters, digits, dots, underscores or hyphens in the release tag.
 goto failed
)
"%CIAZ_GIT%" check-ref-format "refs/tags/%CIAZ_TAG%"
if errorlevel 1 (
 echo Invalid release tag: "%CIAZ_TAG%"
 goto failed
)
set "CIAZ_BASE="
for /f "usebackq" %%H in (`call "%CIAZ_GIT%" rev-parse --verify HEAD`) do set "CIAZ_BASE=%%H"
if not defined CIAZ_BASE (
 echo Could not determine the source checkout's base commit.
 goto failed
)
gh api "repos/%CIAZ_REPO%/commits/%CIAZ_BASE%" --silent
if errorlevel 1 (
 echo The base commit must be accessible in %CIAZ_REPO% before publishing.
 goto failed
)
gh release view --repo "%CIAZ_REPO%" -- "%CIAZ_TAG%" >nul 2>&1
if not errorlevel 1 (
 echo Release "%CIAZ_TAG%" already exists. Choose a new tag.
 goto failed
)

rem A fresh archive directory prevents a failed build from selecting an older APK.
set "CIAZ_RUN="
for /f "usebackq" %%I in (`powershell.exe -NoProfile -Command "[guid]::NewGuid().ToString('N')"`) do set "CIAZ_RUN=%%I"
if not defined CIAZ_RUN goto failed
set "CIAZ_OUTPUT=%~dp0Packaged\Android\%CIAZ_RUN%"
mkdir "%CIAZ_OUTPUT%" || goto failed
call "%CIAZ_ENGINE%\Engine\Build\BatchFiles\RunUAT.bat" Turnkey -command=VerifySdk -platform=Android -project="%~dp0CiazParking.uproject" -unattended
if errorlevel 1 (
 echo Android SDK verification failed. See the AutomationTool output.
 goto failed
)
call "%CIAZ_ENGINE%\Engine\Build\BatchFiles\RunUAT.bat" BuildCookRun -project="%~dp0CiazParking.uproject" -noP4 -platform=Android -cookflavor=ETC2 -clientconfig=Development -build -cook -map=/Game/Maps/Parking -stage -pak -package -archive -archivedirectory="%CIAZ_OUTPUT%" -unattended -utf8output
if errorlevel 1 (
 echo APK packaging failed. See the AutomationTool output.
 goto failed
)

set "CIAZ_APK="
for /f "usebackq delims=" %%F in (`powershell.exe -NoProfile -Command "$ErrorActionPreference='Stop'; $files=@(Get-ChildItem -LiteralPath $env:CIAZ_OUTPUT -Recurse -File -Filter '*.apk'); if ($files.Count -ne 1) { throw 'Expected exactly one APK in the fresh archive' }; $apk=$files[0]; if ($apk.Length -ge 2GB) { throw 'APK exceeds the GitHub release asset size limit' }; Add-Type -AssemblyName System.IO.Compression.FileSystem; $zip=[IO.Compression.ZipFile]::OpenRead($apk.FullName); try { if (-not ($zip.GetEntry('AndroidManifest.xml') -and $zip.GetEntry('assets/main.obb.png'))) { throw 'APK is missing its manifest or embedded game data' } } finally { $zip.Dispose() }; $apk.FullName"`) do set "CIAZ_APK=%%F"
if not defined CIAZ_APK (
 echo No verified standalone APK to upload. Inspect "%CIAZ_OUTPUT%".
 goto failed
)

echo APK: "%CIAZ_APK%"
gh release create --repo "%CIAZ_REPO%" --target "%CIAZ_BASE%" --prerelease --title "Ciaz Parking Android %CIAZ_TAG%" --notes "Android ETC2 Development APK built from a local checkout based on %CIAZ_BASE%. The APK may include local changes beyond the tagged source." -- "%CIAZ_TAG%" "%CIAZ_APK%"
if errorlevel 1 (
 echo GitHub publication failed. The verified APK is still at "%CIAZ_APK%".
 goto failed
)
echo Published "%CIAZ_TAG%" to %CIAZ_REPO%.
if defined CIAZ_INTERACTIVE call :keep_open
exit /b 0

:usage
echo Usage: PackageAndroid.cmd android-v1.7.17 ["D:\Unreal\UE_5.4"]
echo Builds an Android ETC2 Development APK and publishes it as a GitHub prerelease.
exit /b 0

:failed
if defined CIAZ_INTERACTIVE call :keep_open
exit /b 1

:keep_open
echo.
echo This window stays open. Type exit or close the window when finished.
"%ComSpec%" /d /k
exit /b 0
