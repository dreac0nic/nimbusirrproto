#include <iostream>
#include <sstream>
#include <irrlicht.h>

#define HM_SIZE 1024
#define HM_SCALEXZ 40.0f
#define HM_SCALEY 10.0f

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
       << " (a) OpenGL 3.1 (RECOMMENDED)" << endl
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
  
  // Heightmap
  std::string heightmap;
  cout << "Heightmap (n for default): ";
  
  cin >> heightmap;
  
  if(heightmap == "n") heightmap = "hm1_valley.bmp";
  
  heightmap = "./assets/textures/hm/" + heightmap;
  
  cout << "Using heightmap: " << heightmap << endl << endl;
  
  // Create device and exit if creation failed.
  device = createDevice(driverType, core::dimension2d<u32>(1024, 768));
  
  if(device == 0) return 1;
  
  // Setup device.
  device->setWindowCaption(L"IRRLICHT WINDOW");
  
  IVideoDriver* driver = device->getVideoDriver();
  ISceneManager* smgr = device->getSceneManager();
  IGUIEnvironment* guienv = device->getGUIEnvironment();
  
  // Setup camera.
  ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS(0, 100.0f, 1.2f);
  
  camera->setPosition(vector3df(0.0f, (255)*HM_SCALEY/2, 0.0f));
  camera->setTarget(vector3df(HM_SIZE*HM_SCALEXZ, 0.0f, 0.0f));
  camera->setFarValue(42000.0f);
  
  device->getCursorControl()->setVisible(false);
  
  // Setup terrain.
  ITerrainSceneNode* terrain = smgr->addTerrainSceneNode(
							 heightmap.c_str(), // Asset
    0, -1, // Parent ID, Node ID
    vector3df(-HM_SIZE*HM_SCALEXZ/2, 0.0f, -HM_SIZE*HM_SCALEXZ/2), // Node Position
    vector3df(0.0f, 0.0f, 0.0f), // Rotation
    vector3df(HM_SCALEXZ, HM_SCALEY, HM_SCALEXZ), // Scaling
    video::SColor(25, 25, 25, 255), // Vertex Color
    3, // Maximum LOD
    ETPS_17, // Patch size
    4); // Smoothing factor
  
  terrain->setMaterialTexture(0, driver->getTexture("./assets/textures/terrain/grass/simple1_small.jpg"));
  terrain->scaleTexture(20.0f);
  
  // Setup simple collision for the camera
  // -- Selector
  ITriangleSelector* selector = smgr->createTerrainTriangleSelector(terrain, 0);
  terrain->setTriangleSelector(selector);
  
  // -- Setup Collision
  ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
    selector, // Collisioner
    camera, // Effected entity
    vector3df(60.0f, 100.0f, 60.0f), // Bounding
    vector3df(0.0f, 0.0f, 0.0f), // Gravity
    vector3df(0.0f, 50.0f, 0.0f)); // Translation of bounding area
  
  camera->addAnimator(anim);
  
  // -- Cleanup
  selector->drop();
  anim->drop();
  
  // Add some super basic lighting.
  double sunDistance = HM_SIZE*HM_SCALEXZ*2;
  double sunFactor = 14.4;
  double angleInSky = 0.95993;
  double tweakAngle = 0.69813;
  
  ILightSceneNode* sun = smgr->addLightSceneNode(
    0, // Parent Node
    vector3df(-1*sunDistance*sin(angleInSky), sunDistance*cos(angleInSky), sunDistance*sin(tweakAngle)), // Position
    video::SColor(255, 247, 247, 87), // Color
    HM_SIZE*HM_SCALEXZ*sunFactor + sunDistance); // Radius
  
  ILightSceneNode* cameraLight = smgr->addLightSceneNode(0, vector3df(0.0f, 0.0f, 0.0f), video::SColor(255, 247, 247, 87), 1800.0f);
  
  unsigned long long int tick = 0;
  
  // Simple game loop.
  while(device->run()) {
    // Setup HUD
    wstringstream buffer; // HUD FOR ME
    
    // FOR MEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE ...
    buffer << driver->getName() << "\n"
           << "Heightmap Used: " << heightmap.c_str() << "\n"
           << "Framerate: " << driver->getFPS() << "\n"
           << "Height: " << terrain->getHeight(camera->getAbsolutePosition().X, camera->getAbsolutePosition().Z) << "\n";
    
    // Update light
    // light->setRadius(HM_SIZE*HM_SCALEXZ*1.3/2 + HM_SIZE*HM_SCALEXZ*1.2*(tick%LIGHT_PULSE_MODIFIER));
    // cameraLight->setPosition(vector3df(camera->getAbsolutePosition().X, camera->getAbsolutePosition().Y, camera->getAbsolutePosition().Z));
    
    // SO YOU THINK YOU CAN STREAM ME AND RENDER THE SCENE
    driver->beginScene(true, true, SColor(255, 100, 101, 140));
    
    // SO YOU THINK YOU CAN LEAVE ME AND DRAW ALL THE MANAGERS
    smgr->drawAll();
    guienv->drawAll(); // OOooooooooooh baby. Can't do this to me baby ...
    
    // Just gotta get drawn, just gotta drawn right on to here!
    guienv->getBuiltInFont()->draw(buffer.str().c_str(), rect<s32>(10, 10, 260, 22), video::SColor(255, 255, 255, 255));
    
    driver->endScene();
    
    // Increaase the tick.
    ++tick;
  }
  
  // Uninitialize
  device->drop();
  
  return 0;
}
