@echo off
setlocal

cd /d "%~dp0"
cd ..

echo Building GoNe in Debug mode...
echo.

rem Debug build:
rem -g                       Enable TCC runtime debug information
rem -DGONE_DEBUG_BUILD=1    Define our own Debug build macro
rem -D_DEBUG=1              Optional compatibility macro

call tools\tcc.bat ^
    -g ^
    -DGONE_DEBUG_BUILD=1 ^
    -D_DEBUG=1 ^
    -Iengine ^
    -IGoNe ^
    GoNe\main.c ^
    GoNe\Camera\Camera.c ^
    GoNe\Debug\DebugHUD.c ^
    GoNe\Fonts\Fonts.c ^
    GoNe\Game\GameMode.c ^
    GoNe\Player\Player.c ^
    GoNe\Scripts\Script.c ^
    GoNe\TimeBomb\Timebomb.c ^
    engine\engine.c ^
    -o gone.exe ^
    -lws2_32 ^
    -lgdi32 ^
    -lwinmm ^
    -ldbghelp ^
    -lole32 ^
    -lshell32 ^
    -lcomdlg32

if errorlevel 1 (
    echo.
    echo Debug build FAILED!
    pause
    exit /b 1
)

echo.
echo Debug build successful! Starting GoNe...
echo.

start "" gone.exe

endlocal