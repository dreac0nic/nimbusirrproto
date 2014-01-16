#ifndef __MENUS_H__
#define __MENUS_H__

#include "global.h"

void load_tool_bar ();

/////////////////////////////////////////////////
//draw the new terrain menu
void draw_new_terrain_menu (SDL_Surface * this_screen);

void check_new_terrain_menu (char text_input_char);

/////////////////////////////////////////////////
//draw the generate terrain menu
void draw_generate_menu (SDL_Surface * this_screen);

void check_generate_terrain_menu (char text_input_char);


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/////Draw the "view menu"
void draw_view_menu (SDL_Surface * this_screen);

void check_view_menu (char text_input_char);


/////////////////////////////////////////////////
//draw the generate terrain menu
void draw_replace_menu (SDL_Surface * this_screen);

void check_replace_menu (char text_input_char);

#endif
