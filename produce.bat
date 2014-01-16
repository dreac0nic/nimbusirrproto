@echo off
echo.
echo BUILDING PROJECT FOR PRODUCTION
echo -----------------------------------------------
echo Statically linking standard libraries ...
echo CAUTION: Irrlicht dynamic link forces dynamic libraries due to library bounds. Please consider this when distributing.
echo.
pause

g++ -static-libgcc -static-libstdc++ src\main.cpp -o build\NimbusPrototype.exe -Ic:\irrlicht-1.8.1\include -Lc:\irrlicht-1.8.1\lib\Win32-gcc -lIrrlicht -v
