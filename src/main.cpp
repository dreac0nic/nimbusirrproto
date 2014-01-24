#include <iostream>
#include <sstream>
#include <irrlicht.h>

#include "STileMap.h"
#include "Tile.h"
#include "tileMap.h"
#include "RTSControlReceiver.h"

#define PI 3.14159

#define CAMERA_HEIGHT    450.0f
#define CAMERA_ANGLE     30.0f*PI/180.0f
#define CAMERA_MAXVELO   5.0f
#define CAMERA_ACCEL     1.0f
#define CAMERA_SLOWDOWN  0.8f
#define CAMERA_LOCKBOUND 1024.0f

#define EDGE_TOLERENCE 15

#define MAP_FARLANDS 2.5f

#define HM_SIZE 1024
#define HM_SCALEXZ 2.0f
#define HM_SCALEY 1.0f

#define WATER_TILESIZE 50.0f
#define WATER_TILEFACTOR 8

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
  IVideoDriver* driver;
  ISceneManager* smgr;
  IGUIEnvironment* guienv;

  // Setup controls.
  RTSControlReceiver controls;
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

  if(heightmap == "n") heightmap = "hm3_simpleisland.bmp";

  heightmap = "./assets/textures/hm/" + heightmap;

  cout << "Using heightmap: " << heightmap << endl << endl;

  // Create device and exit if creation failed.
  device = createDevice(driverType, core::dimension2d<u32>(1024, 768), 16, false, false, false, &controls);

  if(device == 0) return 1;

  // Setup device.
  device->setWindowCaption(L"IRRLICHT WINDOW");

  driver = device->getVideoDriver();
  smgr = device->getSceneManager();
  guienv = device->getGUIEnvironment();

  // Setup camera.
  ICameraSceneNode* camera = smgr->addCameraSceneNode(0, vector3df(0.0f, CAMERA_HEIGHT, 0.0f), vector3df(0.0f, 0.0f, tan(CAMERA_ANGLE)*CAMERA_HEIGHT));

  camera->setFarValue(2400.0f);

  // Setup terrain.
  ITexture* hm = driver->getTexture(heightmap.c_str());
  
  if(!hm) {
    cerr << "Your HM is bad and you should feel bad." << endl;
    
    heightmap = "./assets/textures/hm/hm3_simpleisland.bmp";
  } else {
    hm->drop();
  }
  
  cerr << "\t Creating terrain." << endl;
  
  ITerrainSceneNode* terrain = smgr->addTerrainSceneNode(
    heightmap.c_str(), // Asset
    0, -1, // Parent ID, Node ID
    vector3df(-HM_SIZE*HM_SCALEXZ/2, 0.0f, -HM_SIZE*HM_SCALEXZ/2), // Node Position
    vector3df(0.0f, 0.0f, 0.0f), // Rotation
    vector3df(HM_SCALEXZ, HM_SCALEY, HM_SCALEXZ), // Scaling
    video::SColor(25, 25, 25, 100), // Vertex Color
    5, // Maximum LOD
    ETPS_33, // Patch size
    8); // Smoothing factor
  
  terrain->setMaterialTexture(0, driver->getTexture("./assets/textures/terrain/grass/simple1_small.jpg"));
  terrain->setMaterialFlag(video::EMF_LIGHTING, true);
  terrain->scaleTexture(20.0f);
  // terrain->setMaterialFlag(video::EMF_WIREFRAME, true);
  
  cerr << "\t Creating gravel!" << endl;
  
  // Setup gravel bed.
  IAnimatedMesh* gravelBedMesh = smgr->addHillPlaneMesh("gravelBedMesh", dimension2d<f32>(HM_SIZE*HM_SCALEXZ*MAP_FARLANDS - 512.0f/WATER_TILEFACTOR, HM_SIZE*HM_SCALEXZ*MAP_FARLANDS - 512.0f/WATER_TILEFACTOR), dimension2d<u32>(1, 1), 0, 0.0f, dimension2d<f32>(0.0f, 0.0f), dimension2d<f32>(20.0f, 20.0f));
  
  IMeshSceneNode* gravelBed = smgr->addMeshSceneNode(gravelBedMesh);
  
  gravelBed->setPosition(vector3df(-512.0f/WATER_TILEFACTOR/2, 8.0f, -512.0f/WATER_TILEFACTOR/2));
  
  gravelBed->setMaterialTexture(0, driver->getTexture("./assets/textures/terrain/gravel/dark1_bed.jpg"));
  // gravelBed->setMaterialFlag(video::EMF_WIREFRAME, true);
  
  cerr << "\t Creating water." << endl;
  
  // Setup water.
  IAnimatedMesh* mesh = smgr->addHillPlaneMesh(
    "waterHillMesh", // Mesh name
    dimension2d<f32>(512.0f/WATER_TILEFACTOR, 512.0f/WATER_TILEFACTOR), // Size of hill tiles
    dimension2d<u32>((int)(HM_SIZE*HM_SCALEXZ*MAP_FARLANDS/512*WATER_TILEFACTOR) - 1, (int)(HM_SIZE*HM_SCALEXZ*MAP_FARLANDS/512*WATER_TILEFACTOR) - 1), // Tally of the tiles
    0, 0.0f, // Mesh material, and hill height
    dimension2d<f32>(0.0f, 0.0f), // Number of hills in the plane
    dimension2d<f32>(10.0f, 10.0f)); // Texture repeat count

  ISceneNode* waterSurface = smgr->addWaterSurfaceSceneNode(
    mesh->getMesh(0), // Mesh in question
    2.0f,   // Height
    500.0f,  // Speed
    300.0f); // Length

  waterSurface->setPosition(vector3df(-512.0f/WATER_TILEFACTOR/2.0f, 80.0f, -512.0f/WATER_TILEFACTOR/2.0f));
  
  cerr << "\t\t LOADING TEXTURE..." << endl;
  
  waterSurface->setMaterialTexture(0, driver->getTexture("./assets/textures/terrain/water/shallow1_clear.png"));

  waterSurface->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
  
  // -- Test with water wireframe
  // waterSurface->setMaterialFlag(video::EMF_WIREFRAME, true);

  // Setup simple collision for the camera
  // -- Selector
  ITriangleSelector* selector = smgr->createTerrainTriangleSelector(terrain, 0);
  terrain->setTriangleSelector(selector);

  // -- Setup Collision
  // CAUTION: STILL RELEVANT DO NOT REMOVE
  /*ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
    selector, // Collisioner
    camera, // Effected entity
    vector3df(60.0f, 100.0f, 60.0f), // Bounding
    vector3df(0.0f, 0.0f, 0.0f), // Gravity
    vector3df(0.0f, 50.0f, 0.0f)); // Translation of bounding area

  camera->addAnimator(anim);
  
  // -- Cleanup
  selector->drop();
  anim->drop();*/

  cerr << "\t Initializing Tile Map" << endl;
  
  // Setup the tilemap
  TileMap tileMap(32, HM_SIZE*HM_SCALEXZ);

  tileMap.addToSceneGraph(0, vector3df(0,70,0), smgr, driver, guienv);
  
  // Setup the STileMap!
  // nimbus::STileMap map(dimension2df(HM_SIZE*HM_SCALEXZ, HM_SIZE*HM_SCALEXZ), vector2d<u32>(10, 10));

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

  // Game Variables
  bool lockCamera = true;
  bool trapCursor = true;
  bool cursorVisible = true;
  bool lastKeys[KEY_KEY_CODES_COUNT];
  
  vector3df camVelocity(0.0f, 0.0f, 0.0f);
  unsigned long long int tick = 0;
  
  std::cerr << "Time to loop!" << std::endl;
  
  // Setup
  for(u32 key = 0; key < KEY_KEY_CODES_COUNT; ++key)
    lastKeys[key] = false;
  
  // Simple game loop.
  while(device->run()) {
    if(device->isWindowFocused()){
      // Setup HUD
      wstringstream buffer; // HUD FOR ME

      // FOR MEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE ...
      buffer << driver->getName() << endl
	     << "Heightmap Used: " << heightmap.c_str() << endl
	     << "Framerate: " << driver->getFPS() << endl
	     << "Height: " << terrain->getHeight(camera->getAbsolutePosition().X, camera->getAbsolutePosition().Z) << endl;
    
      // Check debug controls
      if(controls.IsKeyDown(KEY_F9) && !lastKeys[KEY_F9])
	trapCursor = !trapCursor;
    
      if(controls.IsKeyDown(KEY_F10) && !lastKeys[KEY_F10]) {
	cursorVisible = !cursorVisible;
      
	device->getCursorControl()->setVisible(cursorVisible);
      }
    
      if(controls.IsKeyDown(KEY_F11) && !lastKeys[KEY_F11])
	lockCamera = !lockCamera;
    
      // Controls
      buffer << endl
	     << "User Input --" << endl
	     << "Arrow Keys [UDLR]: "
	     << controls.IsKeyDown(KEY_UP) << ", "
	     << controls.IsKeyDown(KEY_DOWN) << ", "
	     << controls.IsKeyDown(KEY_LEFT) << ", "
	     << controls.IsKeyDown(KEY_RIGHT) << endl
	     << endl
	     << "Cursor Screen Position: " << device->getCursorControl()->getPosition().X << ", " << device->getCursorControl()->getPosition().Y << endl
	     << "Trap Cursor: " << (trapCursor ? "true" : "false") << "[" << (cursorVisible ? "true" : "false") << "]" << endl;
    
      // Trap cursor
      if(trapCursor) {
	bool changed = false;
	vector2d<int> cursorPos = device->getCursorControl()->getPosition();
	int height = driver->getScreenSize().Height;
	int width = driver->getScreenSize().Width;
      
	if(cursorPos.X < 0) {
	  cursorPos.X = 0;
	
	  changed = true;
	} else if(cursorPos.X > width) {
	  cursorPos.X = width;
	
	  changed = true;
	}
      
	if(cursorPos.Y < 0) {
	  cursorPos.Y = 0;
	
	  changed = true;
	} else if(cursorPos.Y > height) {
	  cursorPos.Y = height;
	
	  changed = true;
	}
      
	if(changed)
	  device->getCursorControl()->setPosition(cursorPos);
      }
    
      // Camera movement
      if(controls.IsKeyDown(KEY_UP) || device->getCursorControl()->getPosition().Y <= EDGE_TOLERENCE) {
	camVelocity.Z = (camVelocity.Z > CAMERA_MAXVELO ? CAMERA_MAXVELO : camVelocity.Z + CAMERA_ACCEL);
      } else if(controls.IsKeyDown(KEY_DOWN) || device->getCursorControl()->getPosition().Y >= driver->getScreenSize().Height - EDGE_TOLERENCE) {
	camVelocity.Z = (camVelocity.Z < -CAMERA_MAXVELO ? -CAMERA_MAXVELO : camVelocity.Z - CAMERA_ACCEL);
      } else {
	if(abs(camVelocity.Z) < CAMERA_SLOWDOWN) camVelocity.Z = 0;
	else camVelocity.Z += (camVelocity.Z > 0 ? -1 : 1)*CAMERA_SLOWDOWN;
      }
    
      if(controls.IsKeyDown(KEY_RIGHT) || device->getCursorControl()->getPosition().X >= driver->getScreenSize().Width - EDGE_TOLERENCE) {
	camVelocity.X = (camVelocity.X > CAMERA_MAXVELO ? CAMERA_MAXVELO : camVelocity.X + CAMERA_ACCEL);
      } else if(controls.IsKeyDown(KEY_LEFT) || device->getCursorControl()->getPosition().X <= EDGE_TOLERENCE) {
	camVelocity.X = (camVelocity.X < -CAMERA_MAXVELO ? -CAMERA_MAXVELO : camVelocity.X - CAMERA_ACCEL);
      } else {
	if(abs(camVelocity.X) < CAMERA_SLOWDOWN) camVelocity.X = 0;
	else camVelocity.X += (camVelocity.X > 0 ? -1 : 1)*CAMERA_SLOWDOWN;
      }

      buffer << endl
	     << "Camera -- " << (lockCamera ? "LOCKED" : "FREE") << endl
	     << "Position: " << camera->getAbsolutePosition().X << ", " << camera->getAbsolutePosition().Y << ", " << camera->getAbsolutePosition().Z << ": " << camera->getTarget().X << ", " << camera->getTarget().Y << ", " << camera->getTarget().Z << endl
	     << "Velocity: " << camVelocity.X << ", " << camVelocity.Y << ", " << camVelocity.Z;
    
      // Check camera lock.
      if(lockCamera) {
	vector3df camPos = camera->getPosition();
	vector3df newCamPos = camPos + camVelocity;
	vector3df properDelta = camVelocity;
      
	if(newCamPos.X > CAMERA_LOCKBOUND)
	  properDelta.X = 0;
	else if(newCamPos.X < -CAMERA_LOCKBOUND)
	  properDelta.X = 0;
      
	if(newCamPos.Z > CAMERA_LOCKBOUND)
	  properDelta.Z = 0;
	else if(newCamPos.Z < -CAMERA_LOCKBOUND)
	  properDelta.Z = 0;
      
	buffer << " [" << properDelta.X << ", " << properDelta.Y << ", " << properDelta.Z << "]" << endl;
      
	camera->setPosition(camera->getPosition() + properDelta);
	camera->setTarget(camera->getTarget() + properDelta);
      } else { // Set position
	buffer << endl;
      
	camera->setPosition(camera->getPosition() + camVelocity);
	camera->setTarget(camera->getTarget() + camVelocity);
      }
    
      // SO YOU THINK YOU CAN STREAM ME AND RENDER THE SCENE
      driver->beginScene(true, true, SColor(255, 100, 101, 140));

      // SO YOU THINK YOU CAN LEAVE ME AND DRAW ALL THE MANAGERS
      smgr->drawAll();
      guienv->drawAll(); // OOooooooooooh baby. Can't do this to me baby ...

      // Just gotta get drawn, just gotta drawn right on to here!
      guienv->getBuiltInFont()->draw(buffer.str().c_str(), rect<s32>(10, 10, 260, 22), video::SColor(255, 255, 255, 255));

      // Sigh... I admit... something similar to de-feet... all three of them
      tileMap.update(guienv, driver);

      driver->endScene();

      // Increaase the tick.
      ++tick;
    
      // Cycle keys
      for(u32 key = 0; key < KEY_KEY_CODES_COUNT; ++key)
	lastKeys[key] = controls.IsKeyDown((EKEY_CODE)key);
    }
  }

  // Uninitialize
  device->drop();

  return 0;
}
