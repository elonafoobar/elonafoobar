@echo off

set SDL2_VERSION=2.0.8
set SDL2_MIXER_VERSION=2.0.2
set SDL2_TTF_VERSION=2.0.14
set SDL2_IMAGE_VERSION=2.0.3
set LUA_VERSION=5.3.4

REM These shouldn't need be changed.
set SDL2=SDL2-%SDL2_VERSION%
set SDL2_MIXER=SDL2_mixer-%SDL2_MIXER_VERSION%
set SDL2_TTF=SDL2_ttf-%SDL2_TTF_VERSION%
set SDL2_IMAGE=SDL2_image-%SDL2_IMAGE_VERSION%
set LUA=lua-%LUA_VERSION%

set SDL2_ARCHIVE=SDL2-devel-%SDL2_VERSION%-VC.zip
set SDL2_MIXER_ARCHIVE=SDL2_mixer-devel-%SDL2_MIXER_VERSION%-VC.zip
set SDL2_TTF_ARCHIVE=SDL2_ttf-devel-%SDL2_TTF_VERSION%-VC.zip
set SDL2_IMAGE_ARCHIVE=SDL2_image-devel-%SDL2_IMAGE_VERSION%-VC.zip
set LUA_ARCHIVE=%LUA%.tar.gz


where /q 7z > nul

if errorlevel 1 (
    echo "7z.exe was not found. Ensure it is placed on your PATH."
    EXIT /B
)

where /q patch > nul

if errorlevel 1 (
    echo "patch.exe was not found. Ensure it is placed on your PATH. (It is included with Git for Windows.)"
    exit /B
)


mkdir lib include > nul 2>&1


: SDL2
if not exist %SDL2_ARCHIVE% (
    echo Downloading %SDL2%...
    powershell -Command "(New-Object Net.WebClient).DownloadFile('http://www.libsdl.org/release/%SDL2_ARCHIVE%', '%SDL2_ARCHIVE%')"
)

if not exist lib\SDL2.lib (
    echo Extracting %SDL2%...
    7z x %SDL2_ARCHIVE% > nul
    copy %SDL2%\include\* .\include > nul
    copy %SDL2%\lib\x64\* .\lib > nul
    rd /s /q %SDL2%
)


: SDL2 Mixer
if not exist %SDL2_MIXER_ARCHIVE% (
    echo Downloading %SDL2_MIXER%...
    powershell -Command "(New-Object Net.WebClient).DownloadFile('http://www.libsdl.org/projects/SDL_mixer/release/%SDL2_MIXER_ARCHIVE%', '%SDL2_MIXER_ARCHIVE%')"
)

if not exist lib\SDL2_mixer.lib (
    echo Extracting %SDL2_MIXER%...
    7z x %SDL2_MIXER_ARCHIVE% > nul
    copy %SDL2_MIXER%\include\* .\include > nul
    copy %SDL2_MIXER%\lib\x64\* .\lib > nul
    rd /s /q %SDL2_MIXER%
)


: SDL2 TTF
if not exist %SDL2_TTF_ARCHIVE% (
    echo Downloading SDL2_ttf...
    powershell -Command "(New-Object Net.WebClient).DownloadFile('https://www.libsdl.org/projects/SDL_ttf/release/%SDL2_TTF_ARCHIVE%', '%SDL2_TTF_ARCHIVE%')"
)

if not exist lib\SDL2_ttf.lib (
    echo Extracting %SDL2_TTF%...
    7z x %SDL2_TTF_ARCHIVE% > nul
    copy %SDL2_TTF%\include\* .\include > nul
    copy %SDL2_TTF%\lib\x64\* .\lib > nul
    rd /s /q %SDL2_TTF%
)


: SDL2 Image
if not exist %SDL2_IMAGE_ARCHIVE% (
    echo Downloading %SDL2_IMAGE%...
    powershell -Command "(New-Object Net.WebClient).DownloadFile('http://www.libsdl.org/projects/SDL_image/release/%SDL2_IMAGE_ARCHIVE%', '%SDL2_IMAGE_ARCHIVE%')"
)

if not exist lib\SDL2_image.lib (
    echo Extracting %SDL2_IMAGE%...
    7z x %SDL2_IMAGE_ARCHIVE% > nul
    copy %SDL2_IMAGE%\include\* .\include > nul
    copy %SDL2_IMAGE%\lib\x64\* .\lib > nul
    rd /s /q %SDL2_IMAGE%
)


: Lua 5.3.4
if not exist %LUA_ARCHIVE% (
    echo Downloading %LUA%...
    powershell -Command "(New-Object Net.WebClient).DownloadFile('https://www.lua.org/ftp/%LUA_ARCHIVE%', '%LUA_ARCHIVE%')"
)

if not exist lib\lua (
    echo Extracting %LUA%...
    mkdir lib\lua
    copy ..\cmake\lua\* lib\lua
    7z x %LUA_ARCHIVE% -so | 7z x -aoa -si -ttar > nul
    move %LUA%\src lib\lua\ > nul
    pushd lib\lua\src
    patch -p0 --binary < ..\lua_wstring_5.3.4.patch
    popd
    rd /q /s %LUA%
)


echo Done.
