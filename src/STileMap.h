#ifndef __NIMBUS_STILEMAP
#define __NIMBUS_STILEMAP

#include <iostream>
#include <irrlicht.h>

namespace nimbus
{
  // Commonly used namespace stuff.
  using namespace irr;
  
  /* CLASS: STileMap
   * Basically just a reformed TileMap class based on Hazen's work.
   * Attempting to make the TileMap separate completely from the geometry
   *   of the world.
   */
  class STileMap: public irr::scene::ISceneNode
  {
  private:
    // Tile map information
    irr::core::dimension2d<float> worldSize;
    irr::core::vector2d<int> tileCount;
    
    // Scene members. Careful with unbounded containers.
    //   Possibly move to objects in the future.
    nimbus::Tile*** tiles;
    irr::scene::vector2d<float>*** vectorField;
    
  public:
    // Contructors
    STileMap();
    STileMap(irr::core::dimension2d<float> worldSize, irr::core::vector2d<int> tileCount);
    
    // Destructors
    virtual ~STileMap();
  }
}

#endif
