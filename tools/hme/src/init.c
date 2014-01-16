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

#include "init.h"

void make_color_pallete()
{
  int i;
  for (i = 0; i < 16; i++)
  {
    colors[i].r = 0;
    colors[i].g = i * 16;
    colors[i].b = 200;
  }

  for (; i < 32; i++)
  {
    colors[i].r = i * 8;
    colors[i].g = 255;
    colors[i].b = 0;
  }
  for (; i < 48; i++)
  {
    colors[i].r = 200;
    colors[i].g = 250 - (8 * i);
    colors[i].b = 0;
  }
  for (; i < 64; i++)
  {
    colors[i].r = 230 - ((i - 48) * 4);
    colors[i].g = 149 - ((i - 48) * 4);
    colors[i].b = 0;
  }
SDL_SetPalette (screen, SDL_LOGPAL | SDL_PHYSPAL, colors, 0, 256);
}

void make_gray_pallete()
{
	int i;
  for (i = 0; i < 64; i++)
  {
    colors[i].r = i*4;
    colors[i].g = i*4;
    colors[i].b = i*4;
  }
SDL_SetPalette (screen, SDL_LOGPAL | SDL_PHYSPAL, colors, 0, 256);
}


void build_tool_bar ()
{
  int i = 0;
  //build the main tool bar
  main_tool_bar[i].icon_id = icon_place;
  main_tool_bar[i].associated_window_message = change_tool_place;
  main_tool_bar[i].icon_active = 1;
  main_tool_bar[i].icon_pressed = 0;
  main_tool_bar[i].icon_dont_stay_pressed = 0;
  main_tool_bar[i].right_click_message = do_nothing;
  sprintf(main_tool_bar[i].tool_tip, "Place");
  main_tool_bar[i].mouse_over_timer=0;
  i++;

  main_tool_bar[i].icon_id = icon_escavate;
  main_tool_bar[i].associated_window_message = change_tool_escavate;
  main_tool_bar[i].icon_active = 0;
  main_tool_bar[i].icon_pressed = 0;
  main_tool_bar[i].icon_dont_stay_pressed = 0;
  main_tool_bar[i].right_click_message = do_nothing;
  sprintf(main_tool_bar[i].tool_tip, "Escavate");
  main_tool_bar[i].mouse_over_timer=0;
  i++;

  main_tool_bar[i].icon_id = icon_elevate;
  main_tool_bar[i].associated_window_message = change_tool_elevate;
  main_tool_bar[i].icon_active = 0;
  main_tool_bar[i].icon_pressed = 0;
  main_tool_bar[i].icon_dont_stay_pressed = 0;
  main_tool_bar[i].right_click_message = do_nothing;
  sprintf(main_tool_bar[i].tool_tip, "Elevate");
  main_tool_bar[i].mouse_over_timer=0;
  i++;

  main_tool_bar[i].icon_id = icon_peek;
  main_tool_bar[i].associated_window_message = change_tool_peek;
  main_tool_bar[i].icon_active = 0;
  main_tool_bar[i].icon_pressed = 0;
  main_tool_bar[i].icon_dont_stay_pressed = 0;
  main_tool_bar[i].right_click_message = do_nothing;
  sprintf(main_tool_bar[i].tool_tip, "Pick height");
  main_tool_bar[i].mouse_over_timer=0;
  i++;

  main_tool_bar[i].icon_id = icon_selection;
  main_tool_bar[i].associated_window_message = change_tool_select;
  main_tool_bar[i].icon_active = 0;
  main_tool_bar[i].icon_pressed = 0;
  main_tool_bar[i].icon_dont_stay_pressed = 0;
  main_tool_bar[i].right_click_message = do_nothing;
  sprintf(main_tool_bar[i].tool_tip, "Select");
  main_tool_bar[i].mouse_over_timer=0;
  i++;

  main_tool_bar[i].icon_id = icon_replace;
  main_tool_bar[i].associated_window_message = change_tool_replace;
  main_tool_bar[i].icon_active = 0;
  main_tool_bar[i].icon_pressed = 0;
  main_tool_bar[i].icon_dont_stay_pressed = 0;
  main_tool_bar[i].right_click_message = do_display_replace_menu;
  sprintf(main_tool_bar[i].tool_tip, "Replace");
  main_tool_bar[i].mouse_over_timer=0;
  i++;

  main_tool_bar[i].icon_id = icon_global_replace;
  main_tool_bar[i].associated_window_message = change_tool_global_replace;
  main_tool_bar[i].icon_active = 0;
  main_tool_bar[i].icon_pressed = 0;
  main_tool_bar[i].icon_dont_stay_pressed = 0;
  main_tool_bar[i].right_click_message = do_display_global_replace_menu;
  sprintf(main_tool_bar[i].tool_tip, "Global Replace");
  main_tool_bar[i].mouse_over_timer=0;
  i++;

  main_tool_bar[i].icon_id = icon_flood;
  main_tool_bar[i].associated_window_message = change_tool_flood;
  main_tool_bar[i].icon_active = 0;
  main_tool_bar[i].icon_pressed = 0;
  main_tool_bar[i].icon_dont_stay_pressed = 0;
  main_tool_bar[i].right_click_message = do_nothing;
  sprintf(main_tool_bar[i].tool_tip, "Fill");
  main_tool_bar[i].mouse_over_timer=0;
  i++;

  main_tool_bar[i].icon_id = icon_increase_zoom;
  main_tool_bar[i].associated_window_message = change_tool_zoom_in;
  main_tool_bar[i].icon_active = 0;
  main_tool_bar[i].icon_pressed = 0;
  main_tool_bar[i].icon_dont_stay_pressed = 0;
  main_tool_bar[i].right_click_message = do_decrease_zoom;
  sprintf(main_tool_bar[i].tool_tip, "Zoom in");
  main_tool_bar[i].mouse_over_timer=0;
  i++;

  main_tool_bar[i].icon_id = icon_object;
  main_tool_bar[i].associated_window_message = change_tool_object;
  main_tool_bar[i].icon_active = 0;
  main_tool_bar[i].icon_pressed = 0;
  main_tool_bar[i].icon_dont_stay_pressed = 0;
  main_tool_bar[i].right_click_message = do_display_object_menu;
  sprintf(main_tool_bar[i].tool_tip, "Place object");
  main_tool_bar[i].mouse_over_timer=0;
  i++;

  main_tool_bar[i].icon_id = icon_smooth;
  main_tool_bar[i].associated_window_message = do_smooth_terrain;
  main_tool_bar[i].icon_active = 0;
  main_tool_bar[i].icon_pressed = 0;
  main_tool_bar[i].icon_dont_stay_pressed = 1;
  main_tool_bar[i].right_click_message = do_nothing;
  sprintf(main_tool_bar[i].tool_tip, "Smooth terrain");
  main_tool_bar[i].mouse_over_timer=0;
  i++;

  main_tool_bar[i].icon_id = icon_rise;
  main_tool_bar[i].associated_window_message = do_rise_terrain;
  main_tool_bar[i].icon_active = 0;
  main_tool_bar[i].icon_pressed = 0;
  main_tool_bar[i].icon_dont_stay_pressed = 1;
  main_tool_bar[i].right_click_message = do_nothing;
  sprintf(main_tool_bar[i].tool_tip, "Rise terrain");
  main_tool_bar[i].mouse_over_timer=0;
  i++;

  main_tool_bar[i].icon_id = icon_sink;
  main_tool_bar[i].associated_window_message = do_sink_terrain;
  main_tool_bar[i].icon_active = 0;
  main_tool_bar[i].icon_pressed = 0;
  main_tool_bar[i].icon_dont_stay_pressed = 1;
  main_tool_bar[i].right_click_message = do_nothing;
  sprintf(main_tool_bar[i].tool_tip, "Sink terrain");
  main_tool_bar[i].mouse_over_timer=0;
  i++;

  main_tool_bar[i].icon_id = icon_rotate;
  main_tool_bar[i].associated_window_message = do_display_rotate_menu;
  main_tool_bar[i].icon_active = 0;
  main_tool_bar[i].icon_pressed = 0;
  main_tool_bar[i].icon_dont_stay_pressed = 1;
  main_tool_bar[i].right_click_message = do_nothing;
  sprintf(main_tool_bar[i].tool_tip, "Rotate/Flip terrain");
  main_tool_bar[i].mouse_over_timer=0;
  i++;

  main_tool_bar[i].icon_id = icon_new;
  main_tool_bar[i].associated_window_message = do_new_terrain;
  main_tool_bar[i].icon_active = 0;
  main_tool_bar[i].icon_pressed = 0;
  main_tool_bar[i].icon_dont_stay_pressed = 1;
  main_tool_bar[i].right_click_message = do_nothing;
  sprintf(main_tool_bar[i].tool_tip, "New terrain");
  main_tool_bar[i].mouse_over_timer=0;
  i++;

  main_tool_bar[i].icon_id = icon_generate;
  main_tool_bar[i].associated_window_message = do_generate;
  main_tool_bar[i].icon_active = 0;
  main_tool_bar[i].icon_pressed = 0;
  main_tool_bar[i].icon_dont_stay_pressed = 1;
  main_tool_bar[i].right_click_message = do_nothing;
  sprintf(main_tool_bar[i].tool_tip, "Generate terrain");
  main_tool_bar[i].mouse_over_timer=0;
  i++;

  main_tool_bar[i].icon_id = icon_open;
  main_tool_bar[i].associated_window_message = do_load;
  main_tool_bar[i].icon_active = 0;
  main_tool_bar[i].icon_pressed = 0;
  main_tool_bar[i].icon_dont_stay_pressed = 1;
  main_tool_bar[i].right_click_message = do_nothing;
  sprintf(main_tool_bar[i].tool_tip, "Load terrain");
  main_tool_bar[i].mouse_over_timer=0;
  i++;

  main_tool_bar[i].icon_id = icon_save;
  main_tool_bar[i].associated_window_message = do_save;
  main_tool_bar[i].icon_active = 0;
  main_tool_bar[i].icon_pressed = 0;
  main_tool_bar[i].icon_dont_stay_pressed = 1;
  main_tool_bar[i].right_click_message = do_nothing;
  sprintf(main_tool_bar[i].tool_tip, "Save terrain");
  main_tool_bar[i].mouse_over_timer=0;
  i++;

//////////////////////////
//build the small tool bar
  //build the main tool bar
  i = 0;
  small_tool_bar[i].icon_id = icon_brush_1;
  small_tool_bar[i].associated_window_message = change_brush_1;
  small_tool_bar[i].icon_active = 1;
  small_tool_bar[i].icon_pressed = 0;
  small_tool_bar[i].icon_dont_stay_pressed = 0;
  sprintf(small_tool_bar[i].tool_tip, "Brush size 1x1");
  small_tool_bar[i].mouse_over_timer=0;
  i++;

  small_tool_bar[i].icon_id = icon_brush_2;
  small_tool_bar[i].associated_window_message = change_brush_2;
  small_tool_bar[i].icon_active = 0;
  small_tool_bar[i].icon_pressed = 0;
  small_tool_bar[i].icon_dont_stay_pressed = 0;
  sprintf(small_tool_bar[i].tool_tip, "Brush size 3x3");
  small_tool_bar[i].mouse_over_timer=0;
  i++;

  small_tool_bar[i].icon_id = icon_brush_3;
  small_tool_bar[i].associated_window_message = change_brush_3;
  small_tool_bar[i].icon_active = 0;
  small_tool_bar[i].icon_pressed = 0;
  small_tool_bar[i].icon_dont_stay_pressed = 0;
  sprintf(small_tool_bar[i].tool_tip, "Brush size 5x5");
  small_tool_bar[i].mouse_over_timer=0;
  i++;

  small_tool_bar[i].icon_id = icon_brush_4;
  small_tool_bar[i].associated_window_message = change_brush_4;
  small_tool_bar[i].icon_active = 0;
  small_tool_bar[i].icon_pressed = 0;
  small_tool_bar[i].icon_dont_stay_pressed = 0;
  sprintf(small_tool_bar[i].tool_tip, "Brush size 7x7");
  small_tool_bar[i].mouse_over_timer=0;
  i++;

  small_tool_bar[i].icon_id = icon_brush_5;
  small_tool_bar[i].associated_window_message = change_brush_5;
  small_tool_bar[i].icon_active = 0;
  small_tool_bar[i].icon_pressed = 0;
  small_tool_bar[i].icon_dont_stay_pressed = 0;
  sprintf(small_tool_bar[i].tool_tip, "Brush size 9x9");
  small_tool_bar[i].mouse_over_timer=0;
  i++;

  small_tool_bar[i].icon_id = icon_left_arrow;
  small_tool_bar[i].associated_window_message = do_decrease_tools_height;
  small_tool_bar[i].icon_active = 0;
  small_tool_bar[i].icon_pressed = 0;
  small_tool_bar[i].icon_dont_stay_pressed = 1;
  sprintf(small_tool_bar[i].tool_tip, "Prev. height");
  small_tool_bar[i].mouse_over_timer=0;
  i++;

  small_tool_bar[i].icon_id = icon_right_arrow;
  small_tool_bar[i].associated_window_message = do_increase_tools_height;
  small_tool_bar[i].icon_active = 0;
  small_tool_bar[i].icon_pressed = 0;
  small_tool_bar[i].icon_dont_stay_pressed = 1;
  sprintf(small_tool_bar[i].tool_tip, "Next height");
  small_tool_bar[i].mouse_over_timer=0;
  i++;
}

void
build_numeric_dialog_boxes ()
{

  numeric_dialog_boxes[x_map_size_dialog].max_number = 9999;
  numeric_dialog_boxes[x_map_size_dialog].min_number = 64;
  numeric_dialog_boxes[x_map_size_dialog].current_number = 256;
  numeric_dialog_boxes[x_map_size_dialog].text_offset = 0;
  numeric_dialog_boxes[x_map_size_dialog].dialog_lenght = 4;
  numeric_dialog_boxes[x_map_size_dialog].has_focus = 1;
  numeric_dialog_boxes[x_map_size_dialog].is_pressed = 0;

  numeric_dialog_boxes[y_map_size_dialog].max_number = 9999;
  numeric_dialog_boxes[y_map_size_dialog].min_number = 64;
  numeric_dialog_boxes[y_map_size_dialog].current_number = 256;
  numeric_dialog_boxes[y_map_size_dialog].text_offset = 0;
  numeric_dialog_boxes[y_map_size_dialog].dialog_lenght = 4;
  numeric_dialog_boxes[y_map_size_dialog].has_focus = 0;
  numeric_dialog_boxes[y_map_size_dialog].is_pressed = 0;

  numeric_dialog_boxes[base_height_dialog].max_number = 255;
  numeric_dialog_boxes[base_height_dialog].min_number = 0;
  numeric_dialog_boxes[base_height_dialog].current_number = 0;
  numeric_dialog_boxes[base_height_dialog].text_offset = 0;
  numeric_dialog_boxes[base_height_dialog].dialog_lenght = 3;
  numeric_dialog_boxes[base_height_dialog].has_focus = 0;
  numeric_dialog_boxes[base_height_dialog].is_pressed = 0;

  numeric_dialog_boxes[seed_dialog].max_number = 0xffffffff;
  numeric_dialog_boxes[seed_dialog].min_number = 0;
  numeric_dialog_boxes[seed_dialog].current_number = 0;
  numeric_dialog_boxes[seed_dialog].text_offset = 0;
  numeric_dialog_boxes[seed_dialog].dialog_lenght = 10;
  numeric_dialog_boxes[seed_dialog].has_focus = 1;
  numeric_dialog_boxes[seed_dialog].is_pressed = 0;

  numeric_dialog_boxes[tolerance].max_number = 0xff;
  numeric_dialog_boxes[tolerance].min_number = 0;
  numeric_dialog_boxes[tolerance].current_number = 0;
  numeric_dialog_boxes[tolerance].text_offset = 0;
  numeric_dialog_boxes[tolerance].dialog_lenght = 3;
  numeric_dialog_boxes[tolerance].has_focus = 1;
  numeric_dialog_boxes[tolerance].is_pressed = 0;

  numeric_dialog_boxes[global_tolerance].max_number = 0xff;
  numeric_dialog_boxes[global_tolerance].min_number = 0;
  numeric_dialog_boxes[global_tolerance].current_number = 0;
  numeric_dialog_boxes[global_tolerance].text_offset = 0;
  numeric_dialog_boxes[global_tolerance].dialog_lenght = 3;
  numeric_dialog_boxes[global_tolerance].has_focus = 1;
  numeric_dialog_boxes[global_tolerance].is_pressed = 0;

}

build_cursors()
{
	cursors_array[cursor_put].hot_x=0;
	cursors_array[cursor_put].hot_y=15;
	assign_cursor(cursor_put);

	cursors_array[cursor_dig].hot_x=0;
	cursors_array[cursor_dig].hot_y=15;
	assign_cursor(cursor_dig);

	cursors_array[cursor_elevate].hot_x=3;
	cursors_array[cursor_elevate].hot_y=15;
	assign_cursor(cursor_elevate);

	cursors_array[cursor_peek].hot_x=0;
	cursors_array[cursor_peek].hot_y=15;
	assign_cursor(cursor_peek);

	cursors_array[cursor_replace].hot_x=0;
	cursors_array[cursor_replace].hot_y=15;
	assign_cursor(cursor_replace);

	cursors_array[cursor_global_replace].hot_x=0;
	cursors_array[cursor_global_replace].hot_y=15;
	assign_cursor(cursor_global_replace);

	cursors_array[cursor_flood].hot_x=0;
	cursors_array[cursor_flood].hot_y=14;
	assign_cursor(cursor_flood);

	cursors_array[cursor_wait].hot_x=0;
	cursors_array[cursor_wait].hot_y=0;
	assign_cursor(cursor_wait);

	cursors_array[cursor_arrow].hot_x=3;
	cursors_array[cursor_arrow].hot_y=0;
	assign_cursor(cursor_arrow);

	cursors_array[cursor_target].hot_x=8;
	cursors_array[cursor_target].hot_y=8;
	assign_cursor(cursor_target);

	cursors_array[cursor_zoom].hot_x=4;
	cursors_array[cursor_zoom].hot_y=11;
	assign_cursor(cursor_zoom);

	cursors_array[cursor_select].hot_x=8;
	cursors_array[cursor_select].hot_y=8;
	assign_cursor(cursor_select);
}

