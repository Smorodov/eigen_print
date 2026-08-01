@echo off
chcp 65001 > nul
set LOGFILE=build_log.txt
echo Build started at %date% %time% > %LOGFILE%
mkdir build 2>nul
cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_CXX_FLAGS="-static-libgcc -static-libstdc++ -static -fexec-charset=UTF-8 -finput-charset=UTF-8" >> ..\%LOGFILE% 2>&1
if errorlevel 1 (
    type ..\%LOGFILE%
    cd ..
    pause
    exit /b 1
)
cmake --build . -- -j4 >> ..\%LOGFILE% 2>&1
if errorlevel 1 (
    type ..\%LOGFILE%
    cd ..
    pause
    exit /b 1
)
cd ..
echo Build complete
echo.
echo To run tests, type: run.cmd
pause