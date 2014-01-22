#ifndef __NIMBUS_STILEMAP
#define __NIMBUS_STILEMAP

#include <iostream>
#include <irrlicht.h>
#include "Tile.h"

namespace nimbus
{
  // Commonly used namespace stuff.
  using namespace irr;
  
  /* CLASS: STileMap
   * Basically just a reformed TileMap class based on Hazen's work.
   * Attempting to make the TileMap separate completely from the geometry
   *   of the world.
   */
  class STileMap
  {
  private:
    // Tile map information
    core::dimension2df worldSize;
    core::vector2d<u32> tileCount;
    
    // Scene members. Careful with unbounded containers.
    //   Possibly move to objects in the future.
    scene::ISceneNode* root;
    Tile*** tiles;
    core::vector2d<f32>*** vectorField;
    
  public:
    // Contructors
    STileMap(IrrlichtDevice* device);
    STileMap(IrrlichtDevice* device, core::dimension2df worldSize, core::vector2d<u32> tileCount);
    
    // Destructors
    virtual ~STileMap();
    
    // Object Methods
    void update(void);
    video::ITexture* generateTexture(void);
  };
}

#endif
