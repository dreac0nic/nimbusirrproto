#ifndef TILEMAP_H
#define	TILEMAP_H

#include "irrlicht.h"
#include <vector>

using namespace irr;

class TileMap
{
public:
    TileMap();
    TileMap(int tileDim, double mapDim);
    virtual ~TileMap();

    void addToSceneGraph(
        scene::ISceneNode* parent,
        core::vector3df position,
        scene::ISceneManager* smgr,
        video::IVideoDriver* driver,
        gui::IGUIEnvironment* guienv);

    void init(int tileDim, double mapDim);
    void update(gui::IGUIEnvironment* guienv, video::IVideoDriver* driver);
private:
    int tileDim, mapDim;

    scene::ISceneNode* root;

    scene::ISceneNode*** tileGrid;

    core::vector2df** vectorField;

    std::vector<scene::ISceneNode*> clouds;
};

#endif	/* TILEMAP_H */

