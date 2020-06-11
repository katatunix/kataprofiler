@echo off

call config.bat

set CHIPSET=
if "%2"=="a7" (
	set CHIPSET=armeabi-v7a
) else if "%2"=="a6" (
	set CHIPSET=armeabi
) else if "%2"=="x86" (
	set CHIPSET=x86
) else if "%2"=="a8" (
	set CHIPSET=arm64-v8a
)

call %WIN2TIZ% -i Win2Tiz.xml -t %1 -g %CHIPSET% -j 2
