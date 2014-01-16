#ifndef __ACTIONS_H__
#define __ACTIONS_H__

#include "global.h"

void move_on_minimap ();

void move_minimap ();

void move_toolbar ();

void move_statusbar ();

bool status_bar_press ();

//check if the mouse is on the minimap
bool check_mouse_minimap ();

//check the tool bar buttons for being pointed by the mouse
void check_toolbar_mouse_over ();

//check the tool bar buttons for being pressed (left down button)
bool check_toolbar_press ();

//check the tool bar buttons for being released (left button)
bool check_toolbar_release ();

//process menu commands
void process_menu_commands (int custom_message);

#endif
