#ifndef __NIMBUS_STYLE
#define __NIMBUS_STYLE

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
  private:
    // Scene member.
    scene::ISceneNode root*;
    
    // Factors
    unsigned int type;
    float humidity;
    float temperature;
    float saturation;
    
  public:
    // Constructors
    Tile();
    Tile(unsigned int type, float humidity, float temperature, float saturation);
    
    // Destructors
    virtual ~Tile();
  };
}

#endif
