@echo off

where /q 7z > nul

if errorlevel 1 (
    ECHO 7z.exe was not found. Ensure it is placed in your PATH.
    EXIT /B
)

mkdir include lib > nul 2>&1

echo Downloading SDL2...
powershell -Command "(New-Object Net.WebClient).DownloadFile('http://www.libsdl.org/release/SDL2-devel-2.0.8-VC.zip', 'SDL2-devel-2.0.8-VC.zip')"

7z x SDL2-devel-2.0.8-VC.zip > nul
copy SDL2-2.0.8\include\* .\include > nul
copy SDL2-2.0.8\lib\x64\* .\lib > nul
rd /s /q SDL2-2.0.8

echo Downloading SDL2_image...
powershell -Command "(New-Object Net.WebClient).DownloadFile('http://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.3-VC.zip', 'SDL2_image-devel-2.0.3-VC.zip')"

7z x SDL2_image-devel-2.0.3-VC.zip > nul
copy SDL2_image-2.0.3\include\* .\include > nul
copy SDL2_image-2.0.3\lib\x64\* .\lib > nul
rd /s /q SDL2_image-2.0.3

echo Downloading SDL2_mixer...
powershell -Command "(New-Object Net.WebClient).DownloadFile('http://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-2.0.2-VC.zip', 'SDL2_mixer-devel-2.0.2-VC.zip')"

7z x SDL2_mixer-devel-2.0.2-VC.zip > nul
copy SDL2_mixer-2.0.2\include\* .\include > nul
copy SDL2_mixer-2.0.2\lib\x64\* .\lib > nul
rd /s /q SDL2_mixer-2.0.2

echo Downloading SDL2_ttf...
powershell -Command "(New-Object Net.WebClient).DownloadFile('https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.14-VC.zip', 'SDL2_ttf-devel-2.0.14-VC.zip')"

7z x SDL2_ttf-devel-2.0.14-VC.zip > nul
copy SDL2_ttf-2.0.14\include\* .\include > nul
copy SDL2_ttf-2.0.14\lib\x64\* .\lib > nul
rd /s /q SDL2_ttf-2.0.14

echo Downloading lua...
powershell -Command "(New-Object Net.WebClient).DownloadFile('http://downloads.sourceforge.net/luabinaries/lua-5.3.4_Win64_vc14_lib.zip', 'lua-5.3.4_Win64_vc14_lib.zip')"

7z x lua-5.3.4_Win64_vc14_lib.zip -olua53 > nul
copy lua53\include\* .\include > nul
copy lua53\lua53.lib .\lib > nul
rd /s /q lua53

del /s /q *.zip > nul

echo Done.
