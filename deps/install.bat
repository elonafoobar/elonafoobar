@echo off

mkdir lib include > nul 2>&1

for /f %%a in ('dir /b .\windows\')do (
echo %%a
    xcopy /D /y /e /s .\windows\%%a\include .\include
    xcopy /D /y /e /s .\windows\%%a\lib\x64 .\lib
)
popd

rem The prebuilt SDL2_image includes its own zlib, so it should be removed to avoid conflicts.
del lib\zlib1.dll

echo Done.
