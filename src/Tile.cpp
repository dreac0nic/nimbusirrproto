#include "Tile.h"

// VARIABLE INSTANTIATION
unsigned int nimbus::Tile::count = 0;

/* FUNCTION: Tile constructor
 * Top-level constructor.
 * Delegates all resources to lower-tier.
 */
nimbus::Tile::Tile(IrrlichtDevice* device): Tile(device, core::dimension2d<u32>(512.0f, 512.0f), 0, 0.0f, 0.0f, 0.0f) {}

/* FUNCTION: Tile constructor
 * Lowest-level delegate.
 * 
 * uint type: The biome type of the tile.
 * float humidity: The humidity of the tile.
 * float temperature: The temperature of the tile.
 * float saturation: The liquid saturation of this tile.
 */
nimbus::Tile::Tile(IrrlichtDevice* device, core::dimension2d<u32> size, unsigned int type, float humidity, float temperature, float saturation): size(size), type(type), humidity(humidity), temperature(temperature), saturation(saturation)
{
  std::stringstream nameBuffer;
  
  nameBuffer << "tile" << nextId++;
  
  this->count++;
  this->name = nameBuffer.str();
  
  this->texture = device->getVideoDriver()->addTexture(this->size, this->name, ECF_A8R8G8B8);
}

/* FUNCTION: Tile deconstructor
 * Does deconstructing for basically nothing at the moment.
 */
nimbus::Tile::~Tile()
{
  this->texture->drop();
  
  this->count--;
  
  std::cerr << "Lolz, I'm waisting cycles. kthxbye" << std::endl;
}

/* FUNCTION: update
 * Makes sure the weather responds and what not,
 *   giving the tile the oppurtunity to update itself
 *   before a draw.
 */
nimbus::Tile::update(void)
{
  // UPDATE STUFF
}

/* FUNCITON: generateTexture
 * Generates a texture for this tile, allowing it
 *   to use its weather and tile information
 *   to create a texture for itself.
 */
ITexture* nimbus::Tile::getTexture(void)
{
  // CHECK INTEGRITY OF ENVIRONMENT
  if(!texture && texture->getColorFormat() != ECF_A8R8G8B8) {
    cerr << "CATASTROPIC FAILURE OF ASSET '" << this->name << "'." << endl;
    
    return null;
  }
  
  u32 data = static_cast<u32*>(texture->lock());
  u32 color = 0xffaa00aa;
  
  // PICK TEXTURE DATA
  switch(this->type) {
  case 0:
    // GRASS
    color = 0xff00ff00;
    break;
    
  case 1:
    // DESERT I GUESS
    color = 0xffdfe282;
    break;
    
  default:
    // RAINBOWS
    cerr << "PABLO LIES" << endl;
    break;
  }
  
  // GENERATE TEXTURE DATA
  for(u32 x = 0; x < this->size.getWidth(); ++x) {
    for(u32 y = 0; y < this->size.getHeight(); ++y) {
      data[x + this->size.getHeight()*y] = color;
    }
  }
  
  // UNLOCK TEXTURE AND RETURN
  this->texture->unlock();
  
  return this->texture();
}
