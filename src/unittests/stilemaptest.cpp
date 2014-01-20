#include <iostream>
#include <irrlicht.h>

#include "..\STileMap.h"
#include "..\Tile.h"

using namespace std;

int main(int argc, char* argv[])
{
  nimbus::STileMap* test = new nimbus::STileMap();
  
  cout << "Goodbye." << endl;
  
  delete test;
  
  return 0;
}
