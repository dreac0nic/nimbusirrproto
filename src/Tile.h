#ifndef __NIMBUS_STILE
#define __NIMBUS_STYLE

#include <irrlicht.h>

using namespace irr;

namespace nimbus
{
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
  class Tile: public irr::scene::ISceneNode
  {
  private:
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
  }
}

#endif
