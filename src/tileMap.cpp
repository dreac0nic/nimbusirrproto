#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <vector>
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
    this->tileGrid = new ISceneNode**[tileDim];

    for(int i = 0; i < tileDim; i++)
    {
        this->vectorField[i] = new core::vector2df[tileDim];
        this->tileGrid[i] = new ISceneNode*[tileDim];
    }

    for(int y = 0; y < tileDim; y++)
    {
        for(int x = 0; x < tileDim; x++)
        {
        	// Calculate a random field vector
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
        	ITexture* tempTexture;
        	// Special case for first tile
			if(i == 0 && j == 0)
			{
				tempTexture = gridTexture;
				gridTexture = driver->getTexture("assets/textures/gridRed.png");
			}
        	stringstream position;

        	position << "Generating (" << j << ", " << i << ")\n";

		///* Uncomment/comment this block comment to toggle the test grid off/on
            this->tileGrid[j][i] = smgr->addMeshSceneNode(
                    mesh,
                    this->root,
                    j*100 + i, // id = x*100 + y
                    core::vector3df(
                            mapDim/tileDim*j + mapDim/tileDim/2 - mapDim/2,
                            -0,
                            mapDim/tileDim*i + mapDim/tileDim/2 - mapDim/2));
            this->tileGrid[j][i]->setMaterialTexture(0, gridTexture);//*/

            if(i ==0 && j == 0)
            {
            	gridTexture = tempTexture;
            }
            tileGrid[j][i]->setMaterialFlag(EMF_LIGHTING, false);

			// Attempt to create coordinate text on the play field... failure due to font maligning and small size
//            ISceneNode* coordinateText = smgr->addBillboardTextSceneNode(
//					0,
//					(wchar_t*)position.str().c_str(),
//					this->root,
//					core::dimension2d<f32>(10.0f, 10.0f),
//					core::vector3df(
//							mapDim/tileDim*j + mapDim/tileDim/2 - mapDim/2,
//							5,
//							mapDim/tileDim*j + mapDim/tileDim/2 - mapDim/2),
//					-1,
//					SColor(255, 0, 255, 0),
//					SColor(255, 0, 255, 0));
//			coordinateText->setScale(core::vector3df(50.0f, 50.0f, 50.0f));
        }
    }

	// Create a cloud for testing purposes
    IMesh* cloudMesh = smgr->getMesh("assets/models/cloud.obj");

    this->clouds.push_back(smgr->addMeshSceneNode(
			cloudMesh,
			this->root,
			-1,
			core::vector3df(rand() % mapDim - mapDim/2, this->root->getPosition().Y + 50, rand() % mapDim - mapDim/2),
			core::vector3df(0,0,0),
			core::vector3df(20.0f,20.0f,20.0f)));
	this->clouds[clouds.size()-1]->setMaterialFlag(EMF_LIGHTING, false);
}

void TileMap::update(gui::IGUIEnvironment* guienv, IVideoDriver* driver)
{
    stringstream buffer;

    buffer << "TileMap --\n"
            << "mapDim: " << this->mapDim << "\n"
            << "tileDim: " << this->tileDim << "\n";

    core::vector3df position = this->root->getPosition();

	// Update the cloud position according to the vector map
    for(int i = 0; i < this->clouds.size(); i++)
    {
    	buffer << "Cloud " << i+1 << ": (" << this->clouds[i]->getAbsolutePosition().X
				<< ", " << this->clouds[i]->getAbsolutePosition().Y
				<< ", " << this->clouds[i]->getAbsolutePosition().Z << ")\n";

    	core::vector3df cloudPosition = this->clouds[i]->getPosition();

    	int x = (int)((cloudPosition.X + mapDim/2) * tileDim)/mapDim;
    	int y = (int)((cloudPosition.Z + mapDim/2) * tileDim)/mapDim;

    	buffer << "Cloud " << i+1 << " Tile: (" << x << ", " << y <<")\n";

    }
    
    /*
    guienv->getBuiltInFont()->draw(
        buffer.str().c_str(),
        irr::core::rect<irr::s32>(10,130,250,20),
        irr::video::SColor(255,255,255,255));
    */

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
