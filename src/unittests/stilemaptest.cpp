#include <iostream>
#include <irrlicht.h>

#include "..\STileMap.h"
#include "..\Tile.h"

using namespace std;
using namespace irr;

int main(int argc, char* argv[])
{
  IrrlichtDevice* device = createDevice(video::EDT_SOFTWARE, core::dimension2d<u32>(200,100), 16, false, false, false, 0);
  nimbus::STileMap* test = new nimbus::STileMap(device);
  
  cout << "Initial tile count: " << nimbus::Tile::count << endl;
  
  test->getTexture();
  
  cout << "Goodbye." << endl;
  
  delete test;
  
  cout << "Final tile count: " << nimbus::Tile::count << endl;
  
  return 0;
}

