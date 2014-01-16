/*
Height Map Editor is (C) Radu Privantu(chaos_rift@yahoo.com).

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include "global.h"

struct tool_bar_struct main_tool_bar[no_of_main_tool_bar_icons];
struct tool_bar_struct small_tool_bar[no_of_small_tool_bar_icons];
struct numeric_dialog_box_struct numeric_dialog_boxes[no_of_numeric_dialog_boxes];
struct settings_struct settings[1];
struct cursors_struct cursors_array[20];

#ifndef WINDOWS
struct file_names_struct file_names[1000];

bool view_file_menu=0;
int no_of_files;
int start_file_offset=0;
int x_file_menu=100;
int y_file_menu=50;
int x_file_menu_lenght=420;
int y_file_menu_lenght=270;
bool save_file;
char cur_dir[200];
char cur_file_name[120];

#endif

int current_tool = t_place;
int brush_size = 1;
Uint8 color_1 = 20;
Uint8 color_2 = 0;

int terrain_ratio = 1;

int tolerance_mode = greater_or_leaser;
int tolerance_value = 3;
int tolerance_replace_mode = tolerance_replace_equal;
int tolerance_replace_mode_2 = replace_mode_solid;
char pattern_file_name[120];
Uint8 curent_height;

int global_tolerance_mode;
int global_tolerance_value;
int global_tolerance_replace_mode;
int global_tolerance_replace_mode_2;
int global_temp_tolerance_replace_mode_2;


int last_drawn_x = -1;
int last_drawn_y = -1;

int selection_x_1=-1;
int selection_y_1=-1;
int selection_x_2=-1;
int selection_y_2=-1;

terrain_object current_object;
terrain_object current_pattern;
int object_mode=put_object;

int WIDTH = 1024;
int HEIGHT = 1024;
int seed;
bool size_changed = 0;
int window_width = 700;
int window_height = 480;
int xoffset = 0, yoffset = 0;
int x_screen_offset = 0, y_screen_offset = 0;

int x_mouse_pos, y_mouse_pos;
Sint32 mouse_delta_x, mouse_delta_y;
bool button_l = 0;
bool button_r = 0;
int long_pressed_button_l = 0;
int long_pressed_button_r = 0;

int min_map_x = 300, min_map_y = 200;
int cur_x, cur_y;		//the pixel pointed by the mouse

//for fonts
char *font_mem;
char *handle_font_mem;
int x_font_bmp, y_font_bmp, font_colors_no;
int char_lenght = 7;		//the width, in pixels, of a char

//cursors
Uint8 *cursors_mem;
int cursors_x_lenght;
int cursors_y_lenght;
int last_cursor;
int current_cursor;


//for tool bar
char *tool_bar_mem;
char *handle_tool_bar_mem;
int x_tool_bar_bmp, y_tool_bar_bmp, tool_bar_colors_no;
int tool_bar_x = 1, tool_bar_y = 10;
int tool_bar_x_lenght = 650, tool_bar_y_lenght = 60;

//for status bar
int status_bar_x = 1;
int status_bar_y = 300;
int status_bar_x_lenght = 500;
int status_bar_y_lenght = 17;

//for the new terrain menu
int x_new_terrain_menu = 200;
int y_new_terrain_menu = 100;
int x_new_terrain_menu_lenght = 150;
int y_new_terrain_menu_lenght = 100;

//for the generate terrain menu
int x_generate_terrain_menu = 200;
int y_generate_terrain_menu = 50;
int x_generate_terrain_menu_lenght = 220;
int y_generate_terrain_menu_lenght = 100;

//for the object menu
int x_object_menu=200;
int y_object_menu=50;
int x_object_menu_lenght=200;
int y_object_menu_lenght=120;

//for the view menu
int x_view_menu = 200;
int y_view_menu = 50;
int x_view_menu_lenght = 120;
int y_view_menu_lenght = 240;

//for the replace menu (the magic wand)
int x_replace_menu = 200;
int y_replace_menu = 50;
int x_replace_menu_lenght = 240;
int y_replace_menu_lenght = 300;
int temp_tolerance_mode = 0;
int temp_tolerance_replace_mode = 0;
int temp_tolerance_replace_mode_2;

//for the global replace menu (the magic wand)
int x_global_replace_menu = 200;
int y_global_replace_menu = 50;
int x_global_replace_menu_lenght = 240;
int y_global_replace_menu_lenght = 300;
int temp_global_tolerance_mode;
int temp_global_tolerance_replace_mode;
int temp_global_tolerance_replace_mode_2;


int x_rotation_menu=200;
int y_rotation_menu=50;
int x_rotation_menu_lenght=160;
int y_rotation_menu_lenght=160;
int rotation_type=rotation_none;

//for the tip
int tip_x=0;
int tip_y=0;
int tip_x_lenght=0;
int tip_y_lenght=16;
char tip_text[30];

//for the error dialog box
int x_error_menu=200;
int y_error_menu=200;
int x_error_menu_lenght=400;
int y_error_menu_lenght=70;
char error_msg_1[80];
char error_msg_2[80];

int grid = 0;
int last_click_on = click_terrain;
bool status_bar = 1;
bool mini_map = 1;
bool main_menu = 1;
bool tool_bar = 1;
bool show_new_terrain_menu = 0;
bool show_generate_terrain_menu = 0;
bool show_view_menu = 0;
bool show_replace_menu = 0;
bool show_global_replace_menu = 0;
bool show_rotate_menu = 0;
bool show_object_menu = 0;
bool view_error_menu=0;
bool show_tip=0;
bool load_object=0;
bool isometric_terrain=0;
Uint8 *isometric_window_buffer;

bool overwrite_terrain = 0;
bool clear_temp_buffer = 0;
bool external_menu = 0;

bool drag_minimap = 0;
bool drag_toolbar = 0;
bool drag_statusbar = 0;
bool no_update_now=0;
bool gray_shades=0;
bool undo=0;
bool caps_look_on=0;
bool kill_isometric_buffer_semaphore=0;

Uint8 *terrain_height;		//here is where we store the elevation map
Uint8 *temp_buffer;		//here is where we store places where the brush was drawn before
Uint8 *undo_buffer;		//here is where we store the undo buffer

//for the temp buffer
int min_drawn_x = 0xffff;
int min_drawn_y = 0xffff;
int max_drawn_x = 0;
int max_drawn_y = 0;

char conf_file_path[200];

SDL_Surface *screen;
SDL_Color colors[256];
