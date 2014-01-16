#include <irrlicht.h>
#include <iostream>

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main(int argc, char* argv[])
{
  // VARIABLES
  char chbuffer;
  IrrlichtDevice* device;
  video::E_DRIVER_TYPE driverType;
  
  // Initialize rendering device.
  cout << "Please select the rendering device you would like to use:" << endl
       << " (a) OpenGL 3.1" << endl
       << " (b) Direct3D 9.0c" << endl
       << " (c) Direct3D 8.1" << endl
       << " (d) Burning Software Render" << endl
       << " (e) Software Renderer" << endl
       << " (f) Null Device" << endl
       << " (x) Exit (or any other key)" << endl
       << "\nChoice: ";
  
  cin >> chbuffer;
  
  switch(chbuffer) {
  case 'a':
    driverType = video::EDT_OPENGL;
    break;
    
  case 'b':
    driverType = video::EDT_DIRECT3D9;
    break;
    
  case 'c':
    driverType = video::EDT_DIRECT3D8;
    break;
    
  case 'd':
    driverType = video::EDT_BURNINGSVIDEO;
    break;
    
  case 'e':
    driverType = video::EDT_SOFTWARE;
    break;
    
  case 'f':
    driverType = video::EDT_NULL;
    break;
    
  default:
    return 1;
  }
  
  // Create device and exit if creation failed.
  device = createDevice(driverType, core::dimension2d<u32>(640, 480));
  
  if(device == 0) return 1;
  
  // Setup device.
  device->setWindowCaption(L"IRRLICHT WINDOW");
  
  IVideoDriver* driver = device->getVideoDriver();
  ISceneManager* smgr = device->getSceneManager();
  IGUIEnvironment* guienv = device->getGUIEnvironment();
  
  guienv->addStaticText(L"Hello, world! This is an irrlicht test build!", rect<s32>(10, 10, 260, 22), true);
  
  // Setup camera.
  ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS(0, 100.0f, 1.2f);
  
  camera->setPosition(vector3df(0.0f, 0.0f, 0.0f));
  camera->setTarget(vector3df(0.0f, 0.0f, 0.0f));
  camera->setFarValue(42000.0f);
  
  // Setup terrain.
  ITerrainSceneNode* terrain = smgr->addTerrainSceneNode(
    "./assets/textures/hm/hm1_valley.bmp", // Asset
    0, -1, // Parent ID, Node ID
    vector3df(0.0f, 0.0f, 0.0f),   // Node Position
    vector3df(0.0f, 0.0f, 0.0f),   // Rotation
    vector3df(40.0f, 4.4f, 40.0f), // Scaling
    video::SColor(255, 255, 255, 255), // Vertex Color
    5, // Maximum LOD
    ETPS_17, // Patch size
    4); // Smoothing factor
  
  // Simple game loop.
  while(device->run()) {
    driver->beginScene(true, true, SColor(255, 100, 101, 140));
    
    smgr->drawAll();
    guienv->drawAll();
    
    driver->endScene();
  }
  
  // Uninitialize
  device->drop();
  
  return 0;
}
