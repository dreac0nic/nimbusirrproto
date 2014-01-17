#include <iostream>
#include <sstream>
#include "irrlicht.h"
#include "tileMap.h"

using namespace std;
using namespace irr;
using namespace scene;
using namespace video;
using namespace gui;

TileMap::TileMap()
{
    this->mapDim = 1024;
    this->tileDim = 100;
}

TileMap::TileMap(int tileDim, double mapDim)
{
    this->mapDim = mapDim;
    this->tileDim = tileDim;
}

void TileMap::addToSceneGraph(
        scene::ISceneNode* parent,
        core::vector3df position,
        scene::ISceneManager* smgr,
        video::IVideoDriver* driver,
        gui::IGUIEnvironment* guienv)
{
    // Create the root for the tile map
    this->root = smgr->addEmptySceneNode(parent);
    
    // Create a grid plane
    ITexture* gridTexture = driver->getTexture("assets/textures/grid.png");
    IMesh* mesh = smgr->getGeometryCreator()->createPlaneMesh(
            core::dimension2d<float>(mapDim/tileDim, mapDim/tileDim),
            core::dimension2du(1,1));
    
    for(int i = 0; i < this->tileDim; i++)
    {
        for(int j = 0; j < this->tileDim; j++)
        {
            ISceneNode* grid = smgr->addMeshSceneNode(
                    mesh,
                    this->root,
                    -1,
                    position + core::vector3df(
                                mapDim/tileDim*j + mapDim/tileDim/2 - mapDim/2,
                                0,
                                mapDim/tileDim*i + mapDim/tileDim/2 - mapDim/2));
            grid->setMaterialTexture(0, gridTexture);
            grid->setMaterialFlag(EMF_LIGHTING, false);
        }
    }
}

void TileMap::update(gui::IGUIEnvironment* guienv)
{
    stringstream buffer;
    
    buffer << "TileMap Section\n"
            << "mapDim: " << this->mapDim << "\n"
            << "tileDim: " << this->tileDim << "\n";
    
    guienv->getBuiltInFont()->draw(
        buffer.str().c_str(),
        irr::core::rect<irr::s32>(10,70,250,20),
        irr::video::SColor(255,255,255,255));
}
