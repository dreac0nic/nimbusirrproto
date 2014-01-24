@echo off
echo.
echo BUILDING PROJECT FOR PRODUCTION
echo -----------------------------------------------
echo Statically linking standard libraries ...
echo CAUTION: Irrlicht dynamic link forces dynamic libraries due to library bounds. Please consider this when distributing.
echo.
pause

g++ -static-libgcc -static-libstdc++ src\*.cpp -o build\NimbusPrototype.exe -Ic:\irrlicht-1.8.1\include -Lc:\irrlicht-1.8.1\lib\Win32-gcc -lIrrlicht -v -std=c++11

echo.
echo BUILD COMPLETE
echo -----------------------------------------------
echo Moving built files into primary directory.
move .\build\NimbusPrototype.exe .\
copy .\build\Irrlicht.dll .\
echo.
echo.
echo Build complete. Would you like to run and then clean the project?
set /p runWipe=Run and wipe? [y/N] 
IF %runWipe%==y (
   echo.
   echo Running application ...
   .\NimbusPrototype.exe
   echo.
   echo.
   echo Deleting built files.
   del NimbusPrototype.exe
   del Irrlicht.dll
   echo.
   echo SUCCESS. Exiting ...
)
