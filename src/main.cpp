#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main(int argc, char* argv[])
{
  IrrlichtDevice* device = createDevice(video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 16, false, false, false, 0);
  
  if(!device) return 1;
  
  device->setWindowCaption(L"IRRLICHT WINDOW");
  
  IVideoDriver* driver = device->getVideoDriver();
  ISceneManager* smgr = device->getSceneManager();
  IGUIEnvironment* guienv = device->getGUIEnvironment();
  
  guienv->addStaticText(L"Hello, world! This is an irrlicht test build!", rect<s32>(10, 10, 260, 22), true);
  
  while(device->run()) {
    driver->beginScene(true, true, SColor(255, 100, 101, 140));
    
    smgr->drawAll();
    guienv->drawAll();
    
    driver->endScene();
  }
  
  device->drop();
  
  return 0;
}
