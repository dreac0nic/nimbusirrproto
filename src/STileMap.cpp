#include "STileMap.h"

namespace nimbus
{
  /* FUNCTION: TileMap constructor
   * Top-level constructor for TileMap
   * SHOULD DELEGATE LOWER FUNCTIONS
   */
  STileMap::STileMap(): TileMap(core::dimension2d<float>(1024.0f, 1024.0f), core::vector2d<int>(10, 10)) {}
  
  /* FUNCTION: TileMap constructor
   * Lowest delegate.
   * 
   * dimension2d<float> worldSize: Size of the world in map units, used for tile size generation.
   * vector2d<int> tileCount: Number of tiles in this system. Defaults to 10, 10.
   */
  STileMap::STileMap(core::dimension2d<float> worldSize, core::vector2d<int> tileCount): worldSize(worldSize), tileCount(tileCount)
  {
    this->tiles = new Tile**[tileCount.Y]; // Rows
    this->vectorField = new core::vector2d<float>**[tileCount.Y];
    
    for(int row = 0; row < tileCount.Y; ++row) {
      this->tiles[row] = new Tile*[tileCount.X];
      this->vectorField[row] = new core::vector2d<float>*[tileCount.X];
      
      for(int col = 0; col < tileCount.X; ++col) {
	this->tiles[row][col] = new Tile();
	this->vectorField[row][col] = new core::vector2d<float>(rand() % 10, rand() % 10);
	
	this->vectorField[row][col]->normalize();
      }
    }
  }
  
  virtual STileMap::~STileMap()
  {
    std::cerr << "!!!WARNING!!!" << std::endl << "MAKE SURE TILES ARE GETTING DEALLOCATED. THIS MESSAGE IS NTO TO BE REMOVED UNTIL THIS CHECK IS DONE AND CONFIRMED BY AT LEAST TWO DEVELOPERS." << std::endl << "!!!WARNING!!!" << std::endl;
    
    for(int row = 0; row < this->tileCount.Y; ++row) {
      for(int col = 0; col < this->tileCount.X; ++col) {
	delete this->vectorField[row][col];
	
	// MAKE SURE TILES ARE GETTING DEALLOCATED PROPERLY
      }
      
      delete[] this->tiles[row];
      delete[] this->vectorField[row];
    }
    
    delete[] this->tiles;
    delete[] this->vectorField;
  }
}
