set TARGET=build

if exist %TARGET% rd /s /q %TARGET%

md %TARGET%
md %TARGET%\android
md %TARGET%\android\armeabi-v7a
md %TARGET%\android\armeabi
md %TARGET%\android\x86
md %TARGET%\android\arm64-v8a
md %TARGET%\win32
md %TARGET%\win64

set CLIENT=Client\KataProfiler\bin\Release
copy %CLIENT%\KataProfiler.exe %TARGET%
copy %CLIENT%\FastColoredTextBox.dll %TARGET%
copy %CLIENT%\TexDecomp.dll %TARGET%

copy Server\projects\android\release\armeabi-v7a\kataprofiler\libkataprofiler.a %TARGET%\android\armeabi-v7a
copy Server\projects\android\release\armeabi\kataprofiler\libkataprofiler.a %TARGET%\android\armeabi
copy Server\projects\android\release\x86\kataprofiler\libkataprofiler.a %TARGET%\android\x86
copy Server\projects\android\release\arm64-v8a\kataprofiler\libkataprofiler.a %TARGET%\android\arm64-v8a

copy Server\projects\win32\Release\kataprofiler.dll %TARGET%\win32
copy Server\projects\win32\Release\bootstrap.exe %TARGET%\win32

copy Server\projects\win32\x64\Release\kataprofiler.dll %TARGET%\win64
copy Server\projects\win32\x64\Release\bootstrap.exe %TARGET%\win64

copy readme.md %TARGET%

pause
