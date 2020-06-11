KataProfiler
============

This tool is similar to `AdrenoProfiler` but it can run on all GPUs (not only `Adreno`). The latest version is `2.3`, which supports both Android, Tizen, and Win32. It contains 2 parts: Server and Client. The Server must run first so that the Client can connect to the Server.

## Android/Tizen Server

Server is a static library (`.a` file), so you can link it to your program (game).

Link the corresponding `.a` file (`libkataprofiler.a`) to your program. These files can be found in the folders `android` and `tizen`.

After `eglSwapBuffers()` in your program, insert these 2 lines:
```cpp
void KPSwapBuffers();
KPSwapBuffers();
```

In case you have `C` code, insert:
```cpp
void C_KPSwapBuffers();
C_KPSwapBuffers();
```

If the code is not inside Global Scope (e.g., inside a namespace), move the first line to Global Scope (usually in the beginning of the file).

## Win32 Server

Using the Win32 Server is much easier, no need to modify source code of your program.

Copy `bootstrap.exe` and `kataprofiler.dll` to your Win32 program folder.

Execute: `bootstrap.exe <program>.exe`, for example: `bootstrap.exe Asphalt8.exe`

That's it!

## Client

The Client is a *Windows Form Application* written in `C#`. Run it: `KataProfiler.exe`.

## Contact

Email: nghia.buivan@gameloft.com
Skype: live:katatunix
