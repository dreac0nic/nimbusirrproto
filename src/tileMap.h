#ifndef TILEMAP_H
#define	TILEMAP_H

#include "irrlicht.h"

using namespace irr;

class TileMap
{
public:
    TileMap();
    TileMap(int tileDim, double mapDim);
    virtual ~TileMap() {}
    
    void addToSceneGraph(
        scene::ISceneNode* parent,
        core::vector3df position,
        scene::ISceneManager* smgr,
        video::IVideoDriver* driver,
        gui::IGUIEnvironment* guienv);
    
    void update(gui::IGUIEnvironment* guienv);
private:
    int tileDim, mapDim;
    
    scene::ISceneNode* root;
};

#endif	/* TILEMAP_H */

