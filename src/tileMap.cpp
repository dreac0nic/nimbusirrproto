#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "irrlicht.h"
#include "tileMap.h"

using namespace std;
using namespace irr;
using namespace scene;
using namespace video;
using namespace gui;

TileMap::TileMap()
{
    this->init(32, 1024*40);
}

TileMap::TileMap(int tileDim, double mapDim)
{
    this->init(tileDim, mapDim);
}

void TileMap::init(int tileDim, double mapDim)
{
    this->mapDim = mapDim;
    this->tileDim = tileDim;
    
    this->vectorField = new core::vector2df*[tileDim];
    
    for(int i = 0; i < tileDim; i++)
    {
        this->vectorField[i] = new core::vector2df[tileDim];
    }
    
    for(int y = 0; y < tileDim; y++)
    {
        for(int x = 0; x < tileDim; x++)
        {
            float deltax = rand() % 10;
            float deltay = rand() % 10;
            this->vectorField[x][y] = core::vector2df(deltax, deltay);
            this->vectorField[x][y].normalize();
        }
    }
}

TileMap::~TileMap()
{
    for(int i = 0; i < tileDim; i++)
    {
        delete[] this->vectorField[i];
    }
    delete[] this->vectorField;
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
    this->root->setPosition(position);
    
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
                    core::vector3df(
                            mapDim/tileDim*j + mapDim/tileDim/2 - mapDim/2,
                            -0,
                            mapDim/tileDim*i + mapDim/tileDim/2 - mapDim/2));
            grid->setMaterialTexture(0, gridTexture);
            grid->setMaterialFlag(EMF_LIGHTING, false);
        }
    }
}

void TileMap::update(gui::IGUIEnvironment* guienv, IVideoDriver* driver)
{
    stringstream buffer;
    
    buffer << "TileMap Section\n"
            << "mapDim: " << this->mapDim << "\n"
            << "tileDim: " << this->tileDim << "\n";
    
    guienv->getBuiltInFont()->draw(
        buffer.str().c_str(),
        irr::core::rect<irr::s32>(10,70,250,20),
        irr::video::SColor(255,255,255,255));
    
    core::vector3df position = this->root->getPosition();
    
    for(int i = 0; i < tileDim; i++)
    {
        for(int j = 0; j < tileDim; j++)
        {
            // Hijacking to make unrelated lines
            core::vector3df vectorPosition(
                    mapDim/tileDim*j + mapDim/tileDim/2 - mapDim/2,
                    position.Y,
                    mapDim/tileDim*i + mapDim/tileDim/2 - mapDim/2);
            driver->draw3DLine(
                    vectorPosition,
                    vectorPosition + core::vector3df(
                            vectorField[j][i].X*400,
                            0.1,
                            vectorField[j][i].Y*400),
                    video::SColor(255,255,0,0));
        }
    }
}
