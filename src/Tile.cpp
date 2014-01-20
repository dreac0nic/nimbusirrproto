#include "Tile.h"

/* FUNCTION: Tile constructor
 * Top-level constructor.
 * Delegates all resources to lower-tier.
 */
nimbus::Tile::Tile(): Tile(0, 0.0f, 0.0f, 0.0f) {}

/* FUNCTION: Tile constructor
 * Lowest-level delegate.
 * 
 * uint type: The biome type of the tile.
 * float humidity: The humidity of the tile.
 * float temperature: The temperature of the tile.
 * float saturation: The liquid saturation of this tile.
 */
nimbus::Tile::Tile(unsigned int type, float humidity, float temperature, float saturation): type(type), humidity(humidity), temperature(temperature), saturation(saturation) {}

/* FUNCTION: Tile deconstructor
 * Does deconstructing for basically nothing at the moment.
 */
nimbus::Tile::~Tile()
{
  cerr << "Lolz, I'm waisting cycles. kthxbye" << endl.
}
