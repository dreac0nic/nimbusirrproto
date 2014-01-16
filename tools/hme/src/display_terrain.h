#ifndef __DISPLAY_TERRAIN_H__
#define __DISPLAY_TERRAIN_H__

#include "global.h"

void terrain_on_screen (SDL_Surface * this_screen);

void cls (SDL_Surface * this_screen);

void draw_grid (SDL_Surface * this_screen);	//draw the grid

void debug_info ();

void draw_selection(SDL_Surface * this_screen);

Uint32 on_screen (unsigned int some_int);	//build the 'scene'

#endif
