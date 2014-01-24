#ifndef __NIMBUS_STYLE
#define __NIMBUS_STYLE

#include <iostream>
#include <sstream>
#include <irrlicht.h>

namespace nimbus
{
  // Commonly used namespaces.
  using namespace irr;
  
  /* CLASS: Tile
   * Tile mostly just holds information about itself.
   * This includes a SceneNode and information like:
   *   - Humidity
   *   - Temperature
   *   - Saturation (Water)
   *   - Elevation (Maybe, could be retrieved from HM)
   *   - Type (Biome)
   *   - Flooded (Water density?)
   *   - Soil Nutrition
   */
  class Tile
  {
  public:
    static unsigned int count; // STATIC COUNT USED FOR MEMORY DEBUGGING PURPOSES
    static unsigned long long int nextId;
    
  private:
    // Scene member.
    scene::ISceneNode* root;
    
    // Factors
    unsigned int type;
    float humidity;
    float temperature;
    float saturation;
    
    // Physical Tile Stuff
    std::string name;
    core::dimension2d<u32> size;
    video::ITexture* texture;
    
  public:
    // Constructors
    Tile(IrrlichtDevice* device);
    Tile(IrrlichtDevice* device, core::dimension2d<u32> size, unsigned int type, float humidity, float temperature, float saturation);
    
    // Destructors
    virtual ~Tile();
    
    // Acessor Methods
    core::dimension2d<u32> getSize(void) { return this->size; }
    
    // Object Methods
    void update(void);
    video::ITexture* getTexture(void);
  };
}

#endif
