#include <iostream>
#include <irrlicht.h>

#include "..\STileMap.h"
#include "..\Tile.h"

using namespace std;
using namespace irr;

int main(int argc, char* argv[])
{
  IrrlichtDevice* device = createDevice(video::EDT_NULL, core::dimension2d<u32>(1024, 768), 16, false, false, false, 0);
  nimbus::STileMap* test = new nimbus::STileMap(device);
  
  cout << "Initial tile count: " << nimbus::Tile::count << endl;
  
  cout << "Goodbye." << endl;
  
  delete test;
  
  cout << "Final tile count: " << nimbus::Tile::count << endl;
  
  return 0;
}

