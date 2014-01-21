#include <iostream>
#include <irrlicht.h>

#include "..\STileMap.h"
#include "..\Tile.h"

using namespace std;

int main(int argc, char* argv[])
{
  nimbus::STileMap* test = new nimbus::STileMap();
  
  cout << "Initial tile count: " << nimbus::Tile::count << endl;
  
  cout << "Goodbye." << endl;
  
  delete test;
  
  cout << "Final tile count: " << nimbus::Tile::count << endl;
  
  return 0;
}

