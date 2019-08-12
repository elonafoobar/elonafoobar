@echo off

mkdir lib include > nul 2>&1

xcopy /y /e /s .\windows\SDL2-2.0.8\include .\include
xcopy /y /e /s .\windows\SDL2-2.0.8\lib\x64 .\lib

xcopy /y /e /s .\windows\SDL2_mixer-2.0.2\include .\include
xcopy /y /e /s .\windows\SDL2_mixer-2.0.2\lib\x64 .\lib

rem Both SDL2 ttf and SDL2 image contain zlib.lib, which conflicts with each other.
rem As SDL2 image's zlib is newer than SDL2 ttf's, we must copy SDL2 ttf first, and then SDL2 image.
xcopy /y /e /s .\windows\SDL2_ttf-2.0.14\include .\include
xcopy /y /e /s .\windows\SDL2_ttf-2.0.14\lib\x64 .\lib

xcopy /y /e /s .\windows\SDL2_image-2.0.3\include .\include
xcopy /y /e /s .\windows\SDL2_image-2.0.3\lib\x64 .\lib

xcopy /y /e /s .\windows\lua-5.3.4-wstring\include .\include
xcopy /y /e /s .\windows\lua-5.3.4-wstring\lib\x64 .\lib

xcopy /y /e /s .\windows\zlib-1.2.11\include .\include
xcopy /y /e /s .\windows\zlib-1.2.11\lib\x64 .\lib

echo Done.
