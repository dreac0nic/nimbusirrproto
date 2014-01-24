g++ src\*.cpp -o build\tmpbuild.exe -Ic:\irrlicht-1.8.1\include -Lc:\irrlicht-1.8.1\lib\Win32-gcc -lIrrlicht -std=c++11

build\tmpbuild.exe
del build\tmpbuild.exe