#include "Tile.h"
#include <stdlib.h>

namespace nimbus {
  // VARIABLE INSTANTIATION
  unsigned int nimbus::Tile::count = 0;
  unsigned long long int nimbus::Tile::nextId = 0;

  /* FUNCTION: Tile constructor
   * Top-level constructor.
   * Delegates all resources to lower-tier.
   */
  Tile::Tile(IrrlichtDevice* device): Tile(device, core::dimension2d<u32>(256.0f, 256.0f), 0, 0.0f, 0.0f, 0.0f) {}

  /* FUNCTION: Tile constructor
   * Lowest-level delegate.
   * 
   * uint type: The biome type of the tile.
   * float humidity: The humidity of the tile.
   * float temperature: The temperature of the tile.
   * float saturation: The liquid saturation of this tile.
   */
  Tile::Tile(IrrlichtDevice* device, core::dimension2d<u32> size, unsigned int type, float humidity, float temperature, float saturation): size(size), type(type), humidity(humidity), temperature(temperature), saturation(saturation)
  {
    std::stringstream nameBuffer;
  
    nameBuffer << "tile" << nextId++;
  
    this->count++;
    this->name = nameBuffer.str();
  
    this->texture = device->getVideoDriver()->addTexture(this->size, this->name.c_str(), video::ECF_A8R8G8B8);
  }

  /* FUNCTION: Tile deconstructor
   * Does deconstructing for basically nothing at the moment.
   */
  Tile::~Tile()
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
  void Tile::update(void)
  {
    // UPDATE STUFF
  }

  /* FUNCTION: generateTexture
   * Generates a texture for this tile, allowing it
   *   to use its weather and tile information
   *   to create a texture for itself.
   */
  irr::video::ITexture* Tile::getTexture(void)
  {
    // CHECK INTEGRITY OF ENVIRONMENT
    if(texture == NULL || texture->getColorFormat() != video::ECF_A8R8G8B8) {
      std::cerr << "CATASTROPIC FAILURE OF ASSET '" << this->name << "'." << std::endl;
      
      return NULL;
    }

    // LOOK INTO CHANGING TO u8, POSSIBLY FIXES THE ISSUES WITH MEMORY OVERFLOW
    u32* data = static_cast<u32*>(texture->lock());
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
      std::cerr << "PABLO LIES" << std::endl;
      break;
    }
    
    std::cerr << "Generating texture data ... [" << this->size.Width << "x" << this->size.Height << "]" << std::endl;
    
    // GENERATE TEXTURE DATA
    for(u32 x = 0; x < this->size.Width*this->size.Height; ++x) {
      //for(u32 y = 0; y < this->size.Height; ++y) {
	u8 red, green, blue;
	
	red = color >> 16;
	green = color >> 8;
	blue = color;
	
	u8 offset = rand()%100 - 50;
	
	red += offset;
	green += offset;
	blue += 0;
	
	color = 0xff000000 | (red << 16) | (blue << 8) | green;
	
	char buffer[24];
	sprintf(buffer, "[%x] %02x %02x %02x\0", color, red, green, blue);
	
	std::cerr << buffer << std::endl;
	
	data[x] = color;
	
	if(this->type == 1) data[x] = 0xff80aa80;
	//}
    }
  
    // UNLOCK TEXTURE AND RETURN
    this->texture->unlock();
  
    return this->texture;
  }
}
