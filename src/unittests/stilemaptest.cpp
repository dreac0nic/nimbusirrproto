#include <iostream>
#include <irrlicht.h>

#include "..\STileMap.h"
#include "..\Tile.h"

using namespace std;
using namespace irr;

int main(int argc, char* argv[])
{
  IrrlichtDevice* device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(800,600), 16, false, false, false, 0);
  nimbus::STileMap* test = new nimbus::STileMap(device);
  nimbus::Tile* tileThing = new nimbus::Tile(device);
  
  device->setWindowCaption(L"Texture Tile Map Demo");
  
  video::IVideoDriver* driver = device->getVideoDriver();
  gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
  
  cout << "Initial tile count: " << nimbus::Tile::count << endl;
  
  guienv->addImage(driver->getTexture("./assets/textures/terrain/grass/simple1_small.jpg"), core::vector2d<s32>(0.0f, 0.0f));
  
  video::ITexture* texture = tileThing->getTexture();
  if(texture != NULL) {
    guienv->addImage(texture, core::vector2d<s32>(100.0, 100.0));
  } else {
    cerr << "Something happened." << endl;
  }
  
  test->getTexture();
  
  while(device->run()) {
    driver->beginScene(true, true, video::SColor(255, 100, 100, 140));
    
    guienv->drawAll();
    
    driver->endScene();
  }
  
  cout << "Goodbye." << endl;
  
  delete test;
  
  cout << "Final tile count: " << nimbus::Tile::count << endl;
  
  return 0;
}

