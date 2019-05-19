@echo off

mkdir lib include > nul 2>&1

for /f %%a in ('dir /b .\windows\')do (
echo %%a
    xcopy /D /y /e /s .\windows\%%a\include .\include
    xcopy /D /y /e /s .\windows\%%a\lib\x64 .\lib
)
popd

echo Done.
