#ifndef __NIMBUS_STILEMAP
#define __NIMBUS_STILEMAP

#include <irrlicht.h>

using namespace irr;

namespace nimbus {
  
  /* CLASS: STileMap
   * Basically just a reformed TileMap class based on Hazen's work.
   * Attempting to make the TileMap separate completely from the geometry
   *   of the world.
   */
  class STileMap
  {
  private:
    // Scene members. Careful with unbounded containers.
    //   Possibly move to objects in the future.
    scene::ISceneNode* root;
    scene::ISceneNode*** tiles;
    scene::vector2d<float>** vectorField;
    
  public:
    // Contructors
    TileMap();
    TileMap(core::dimension2d<u32> worldSize, core::vector2d<int> tileCount);
    
    // Destructors
    virtual ~TileMap();
  }
}

#endif
