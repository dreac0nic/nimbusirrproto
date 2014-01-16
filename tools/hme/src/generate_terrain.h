/*******************************************************
 * sdlplasma
 * Author: Stefan Hellkvist, stefan@hellkvist.org
 * Copyright: see GPL
 *******************************************************/

#ifndef __GENERATE_TERRAIN_H__
#define __GENERATE_TERRAIN_H__

#include <stdlib.h>
#include "global.h"

void drawSeed (int width, int height);

void drawMap (int x1, int y1, int x2, int y2);

int overdraw_terrain ();

int make_terrain ();

void allocate_mem();

#endif
