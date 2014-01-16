#ifndef __GLOBAL_H__
#define __GLOBAL_H__

// ANSI C has no "bool", so typedef it here.
// It also has no true/false, and because Entropy Serpent is a nit and used 1
// not -1 I have to define it as 1.
typedef unsigned char bool;
#define true 1
#define false 0

// Uncomment following if compiling on Windows
 #define WINDOWS
#ifndef WINDOWS
//add the POSIX stuff...
  struct file_names_struct
  {
    char file_name[100];
    char is_directory; //1 for directory, 0 for normal file
  };
extern int no_of_files;
extern int start_file_offset;
extern bool view_file_menu;
extern int x_file_menu;
extern int y_file_menu;
extern int x_file_menu_lenght;
extern int y_file_menu_lenght;
extern bool save_file;
extern char cur_dir[200];
extern char cur_file_name[120];

extern struct file_names_struct file_names[1000];

#endif

#include <SDL/SDL_video.h>

#define dark_steel_blue 245
#define very_light_steel_blue 246
#define light_steel_blue 247
#define steel_blue 248
#define gray 249
#define red 250
#define green 251
#define blue 252
#define darkblue 253
#define white 254
#define black 255

//now, define the tools
#define t_none 0
#define t_place 1
#define t_escavate 2
#define t_elevate 3
#define t_replace 4
#define t_flood 5
#define t_smooth 6
#define t_peek 7
#define t_level 8
#define t_select 9
#define t_zoom_in 10
#define t_object 11
#define t_global_replace 12

//icons offset
#define icon_place 0
#define icon_escavate 1
#define icon_elevate 2
#define icon_peek 3
#define icon_replace 4
#define icon_flood 5
#define icon_selection 6
#define icon_object 7
#define icon_smooth 8
#define icon_generate 9
#define icon_rise 10
#define icon_sink 11
#define icon_new 12
#define icon_increase_zoom 14
#define icon_decrease_zoom 15
#define icon_open 16
#define icon_save 17
#define icon_generate 9
#define icon_rotate 18
#define icon_global_replace 19


//small icons
#define icon_brush_1 0
#define icon_brush_2 1
#define icon_brush_3 2
#define icon_brush_4 3
#define icon_brush_5 4
#define icon_left_arrow 5
#define icon_right_arrow 6

//custom window messages
#define change_tool_place 0
#define change_tool_escavate 1
#define change_tool_elevate 2
#define change_tool_peek 3
#define change_tool_replace 4
#define change_tool_flood 5
#define change_tool_select 6
#define change_tool_object 20
#define do_smooth_terrain 7
#define do_rise_terrain 8
#define do_sink_terrain 9
#define do_new_terrain 10
#define do_decrease_zoom 11
#define change_tool_zoom_in 12
#define do_save 13
#define do_load 14
#define do_generate 15
#define change_tool_global_replace 16
#define do_nothing 30
#define do_display_replace_menu 31
#define do_display_rotate_menu 32
#define do_display_object_menu 33
#define do_display_global_replace_menu 34

//small icons messages
#define change_brush_1 60
#define change_brush_2 61
#define change_brush_3 62
#define change_brush_4 63
#define change_brush_5 64
#define do_decrease_tools_height 65
#define do_increase_tools_height 66

//numeric dialog boxes
#define x_map_size_dialog 0
#define y_map_size_dialog 1
#define base_height_dialog 2
#define seed_dialog 3
#define tolerance 4
#define global_tolerance 5

//the cursors stuff
#define cursor_put 0
#define cursor_dig 1
#define cursor_elevate 2
#define cursor_peek 3
#define cursor_replace 4
#define cursor_flood 5
#define cursor_wait 6
#define cursor_arrow 7
#define cursor_target 8
#define cursor_zoom 9
#define cursor_select 10
#define cursor_null 10
#define cursor_global_replace 11

  struct cursors_struct
  {
    int hot_x;
    int hot_y;
    Uint8 *cursor_pointer;
  };

extern struct cursors_struct cursors_array[20];

struct tool_bar_struct
{
  int icon_id;
  int associated_window_message;
  int right_click_message;
  bool icon_active;		//when the left button is pressed AND released
  bool icon_pressed;		//when the left button is pressed
  bool icon_dont_stay_pressed;	//it goes back to the original form when mouse unpressed
  bool icon_mouse_over;
  char tool_tip[30];
  int mouse_over_timer;
};

#define no_of_main_tool_bar_icons 18
#define no_of_small_tool_bar_icons 7
extern struct tool_bar_struct main_tool_bar[no_of_main_tool_bar_icons];
extern struct tool_bar_struct small_tool_bar[no_of_small_tool_bar_icons];

struct numeric_dialog_box_struct
{
  int dialog_id;
  int max_number;
  int min_number;
  int current_number;
  int text_offset;
  char dialog_text[14];
  int dialog_lenght;
  bool has_focus;
  bool is_pressed;
};

#define no_of_numeric_dialog_boxes 15
extern struct numeric_dialog_box_struct numeric_dialog_boxes[no_of_numeric_dialog_boxes];


//here, we save/load the settings, at startup and exit
struct settings_struct
{
  short window_x;
  short window_y;
  short minmap_x;
  short minmap_y;
  bool minmap_active;
  short toolbar_x;
  short toolbar_y;
  bool toolbar_active;
  short statusbar_x;
  short statusbar_y;
  bool statusbar_active;
  short grid_size;
  char last_height_used;
  Uint8 replace_tolerance;
  char tolerance_mode;
  bool overwrite_terrain;
  bool gray_shades;
};

extern struct settings_struct settings[1];

extern int current_tool;
extern int brush_size;
extern Uint8 color_1;
extern Uint8 color_2;

extern int terrain_ratio;

#define no_undo 0
#define partial_undo 1
#define total_undo 2
#define total_undo_swap_x_y 3

//replace (magic wand) settings

#define greater 0
#define leaser 1
#define greater_or_leaser 2

#define tolerance_replace_plus 0
#define tolerance_replace_minus 1
#define tolerance_replace_equal 2

#define replace_mode_solid 0
#define replace_mode_pattern 2

extern int tolerance_mode;
extern int tolerance_value;
extern int tolerance_replace_mode;
extern int tolerance_replace_mode_2;
extern char pattern_file_name[120];
extern Uint8 curent_height;

extern int global_tolerance_mode;
extern int global_tolerance_value;
extern int global_tolerance_replace_mode;
extern int global_tolerance_replace_mode_2;

extern int last_drawn_x;
extern int last_drawn_y;

extern int selection_x_1;
extern int selection_y_1;
extern int selection_x_2;
extern int selection_y_2;

typedef struct
  {
    int object_x_len;
    int object_y_len;
    Uint8 * object_mem;
  } terrain_object;

#define add_object 0
#define sub_object 1
#define put_object 2

extern terrain_object current_object;
extern terrain_object current_pattern;
extern int object_mode;
extern bool load_object;

extern int WIDTH;
extern int HEIGHT;
extern int seed;
extern bool size_changed;
extern int window_width;
extern int window_height;
extern int xoffset, yoffset;
extern int x_screen_offset, y_screen_offset;

//mouse stuff
extern int x_mouse_pos, y_mouse_pos;
extern Sint32 mouse_delta_x, mouse_delta_y;
extern bool button_l;
extern bool button_r;
extern int long_pressed_button_l;
extern int long_pressed_button_r;

extern int min_map_x, min_map_y;
extern int cur_x, cur_y;	//the pixel pointed by the mouse

//for fonts
extern char *font_mem;
extern char *handle_font_mem;
extern int x_font_bmp, y_font_bmp, font_colors_no;
extern int char_lenght;		//the width, in pixels, of a char

//for cursors
extern Uint8 *cursors_mem;
extern int last_cursor;
extern int current_cursor;
extern int cursors_x_lenght;
extern int cursors_y_lenght;

//for tool bar
extern char *tool_bar_mem;
extern char *handle_tool_bar_mem;
extern int x_tool_bar_bmp, y_tool_bar_bmp, tool_bar_colors_no;
extern int tool_bar_x, tool_bar_y;
extern int tool_bar_x_lenght, tool_bar_y_lenght;

//for status bar
extern int status_bar_x;
extern int status_bar_y;
extern int status_bar_x_lenght;
extern int status_bar_y_lenght;

//for the new terrain menu
extern int x_new_terrain_menu;
extern int y_new_terrain_menu;
extern int x_new_terrain_menu_lenght;
extern int y_new_terrain_menu_lenght;

//for the generate terrain menu
extern int x_generate_terrain_menu;
extern int y_generate_terrain_menu;
extern int x_generate_terrain_menu_lenght;
extern int y_generate_terrain_menu_lenght;

//for the object menu
extern int x_object_menu;
extern int y_object_menu;
extern int x_object_menu_lenght;
extern int y_object_menu_lenght;

//for the view menu
extern int x_view_menu;
extern int y_view_menu;
extern int x_view_menu_lenght;
extern int y_view_menu_lenght;

//for the replace menu (the magic wand)
extern int x_replace_menu;
extern int y_replace_menu;
extern int x_replace_menu_lenght;
extern int y_replace_menu_lenght;
extern int temp_tolerance_mode;
extern int temp_tolerance_replace_mode;
extern int temp_tolerance_replace_mode_2;

//for the global replace menu (the magic wand)
extern int x_global_replace_menu;
extern int y_global_replace_menu;
extern int x_global_replace_menu_lenght;
extern int y_global_replace_menu_lenght;
extern int temp_global_tolerance_mode;
extern int temp_global_tolerance_replace_mode;
extern int temp_global_tolerance_replace_mode_2;

#define rotation_none 0
#define rotation_flip_x 1
#define rotation_flip_y 2
#define rotation_flip_z 3
#define rotation_CW_90 4
#define rotation_CCW_90 5
#define rotation_180 6

//for the rotation menu
extern int x_rotation_menu;
extern int y_rotation_menu;
extern int x_rotation_menu_lenght;
extern int y_rotation_menu_lenght;
extern int rotation_type;

//for the tip
extern int tip_x;
extern int tip_y;
extern int tip_x_lenght;
extern int tip_y_lenght;
extern char tip_text[30];


//for the error dialog box
extern int x_error_menu;
extern int y_error_menu;
extern int x_error_menu_lenght;
extern int y_error_menu_lenght;
extern bool view_error_menu;
extern char error_msg_1[80];
extern char error_msg_2[80];

#define click_terrain 0
#define click_mini_map 1
#define click_tool_bar 2
#define click_status_bar 3

extern int grid;
extern int last_click_on;
extern bool status_bar;
extern bool mini_map;
extern bool main_menu;
extern bool tool_bar;
extern bool show_new_terrain_menu;
extern bool show_generate_terrain_menu;
extern bool show_view_menu;
extern bool show_replace_menu;
extern bool show_global_replace_menu;
extern bool show_rotate_menu;
extern bool show_tip;
extern bool show_object_menu;
extern bool isometric_terrain;
Uint8 *isometric_window_buffer;

extern bool overwrite_terrain;
extern bool clear_temp_buffer;
extern bool external_menu;

extern bool drag_minimap;
extern bool drag_toolbar;
extern bool drag_statusbar;
extern bool no_update_now;
extern bool gray_shades;
extern bool undo;
extern bool caps_look_on;
extern bool kill_isometric_buffer_semaphore;

extern Uint8 *terrain_height;	//here is where we store the elevation map
extern Uint8 *temp_buffer;	//here is where we store places where the brush was drawn before
extern Uint8 *undo_buffer;	//here is where we store the undo image

//for the temp buffer
extern int min_drawn_x;
extern int min_drawn_y;
extern int max_drawn_x;
extern int max_drawn_y;

extern char conf_file_path[200];

extern SDL_Color colors[256];

extern SDL_Surface *screen;

#endif
