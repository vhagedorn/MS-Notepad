@echo off
REM Simple build command matching your exact format

REM Path variables for easier maintenance
set "VS_ROOT=C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207"
set "WINSDK_ROOT=winsdk-10"
set "OFFICIAL_WINSDK_ROOT=C:\Program Files (x86)\Windows Kits\10"
set "WINSDK_VER=10.0.10240.0"
set "OFFICIAL_WINSDK_VER=10.0.26100.0"
set "OFFICIAL_WINSDK_LIB_VER=10.0.19041.0"


copy /Y "%WINSDK_ROOT%\Include\%WINSDK_VER%\um\WinNls.h" "winsdk-10\Include\10.0.10240.0\um\winnlsp.h"


echo Compiling C files...
"%VS_ROOT%\bin\Hostx64\x64\cl.exe" ^
    /I"%WINSDK_ROOT%\Include\%WINSDK_VER%\um" ^
    /I"%WINSDK_ROOT%\Include\%WINSDK_VER%\shared" ^
    /I"%WINSDK_ROOT%\Include\%WINSDK_VER%\km" ^
    /I"%WINSDK_ROOT%\Include\%WINSDK_VER%\km\crt" ^
    /I"%VS_ROOT%\include" ^
    /I"mkuni" ^
    /MT ^
    /D"WIN32" ^
    /D"NDEBUG" ^
    /D"_WINDOWS" ^
    /D"UNICODE" ^
    /D"_UNICODE" ^
    /D"NT" ^
    /D"_CRT_SECURE_NO_WARNINGS" ^
    /c ^
    notepad.c ^
    npdate.c ^
    npfile.c ^
    npinit.c ^
    npmisc.c ^
    npprint.c ^
    nputf.c ^
    uniconv.c ^
    uconvert.c ^
    mkuni\mkuni.c

if %errorlevel% neq 0 (
    echo Compilation failed!
    exit /b 1
)

echo Compiling resource file...
"%OFFICIAL_WINSDK_ROOT%\bin\%OFFICIAL_WINSDK_VER%\x64\rc.exe" ^
    /nologo ^
    /I"%WINSDK_ROOT%\Include\%WINSDK_VER%\um" ^
    /I"%WINSDK_ROOT%\Include\%WINSDK_VER%\shared" ^
    /I"%WINSDK_ROOT%\Include\%WINSDK_VER%\km" ^
    /I"%WINSDK_ROOT%\Include\%WINSDK_VER%\km\crt" ^
    /fo notepad.res ^
    notepad.rc

if %errorlevel% neq 0 (
    echo Resource compilation failed!
    exit /b 1
)

echo Linking...
"%VS_ROOT%\bin\Hostx64\x64\link.exe" ^
    /nologo ^
    /subsystem:windows ^
    /LIBPATH:"%VS_ROOT%\lib\x64" ^
    /LIBPATH:"%OFFICIAL_WINSDK_ROOT%\Lib\%OFFICIAL_WINSDK_LIB_VER%\um\x64" ^
    /LIBPATH:"%OFFICIAL_WINSDK_ROOT%\Lib\%OFFICIAL_WINSDK_LIB_VER%\ucrt\x64" ^
    /out:notepad.exe ^
    notepad.obj ^
    npdate.obj ^
    npfile.obj ^
    npinit.obj ^
    npmisc.obj ^
    npprint.obj ^
    nputf.obj ^
    uniconv.obj ^
    uconvert.obj ^
    mkuni.obj ^
    notepad.res ^
    kernel32.lib ^
    user32.lib ^
    gdi32.lib ^
    winspool.lib ^
    comdlg32.lib ^
    advapi32.lib ^
    shell32.lib ^
    ole32.lib ^
    oleaut32.lib ^
    uuid.lib ^
    odbc32.lib ^
    odbccp32.lib ^
    comctl32.lib ^
    htmlhelp.lib ^
    libcmt.lib ^
    libucrt.lib ^
    libvcruntime.lib ^
    legacy_stdio_definitions.lib

if %errorlevel% neq 0 (
    echo Linking failed!
    exit /b 1
)

echo Build completed successfully!
echo Output: notepad.exe
