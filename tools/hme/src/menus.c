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

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_keysym.h>
#include <SDL/SDL_events.h>
#include "menus.h"

void
load_tool_bar ()
{
  FILE *f = NULL;
  char *temp_pointer = tool_bar_mem;
  int f_size, i;
  f = fopen ("toolbar.bmp", "rb");
  fseek (f, 0, SEEK_END);
  f_size = ftell (f);
//ok, allocate memory for it
  tool_bar_mem = calloc ( f_size, sizeof(char) );
  handle_tool_bar_mem=tool_bar_mem;
  fseek (f, 0, SEEK_SET);
  fread (tool_bar_mem, 1, f_size, f);
  fclose (f);

  tool_bar_mem += 18;		//x lenght is at offset+18
  x_tool_bar_bmp = *((int *) tool_bar_mem);
  tool_bar_mem += 4;		//y lenght is at offset+22
  y_tool_bar_bmp = *((int *) tool_bar_mem);
  tool_bar_mem += 46 - 22;	//y lenght is at offset+22
  tool_bar_colors_no = *((int *) tool_bar_mem);
  tool_bar_mem += 54 - 46;	//ok, now, we are at the color pallete
  //get the color pallete

  for (i = 0; i < tool_bar_colors_no; i++)
  {
    colors[i + 128].b = *(tool_bar_mem++);
    colors[i + 128].g = *(tool_bar_mem++);
    colors[i + 128].r = *(tool_bar_mem++);
    tool_bar_mem++;
  }
	temp_pointer=tool_bar_mem;
  for (i = 0; i < x_tool_bar_bmp * y_tool_bar_bmp; i++)
    *(tool_bar_mem) = *(++tool_bar_mem) + 128;
  tool_bar_mem = temp_pointer;


}


/////////////////////////////////////////////////
//draw the new terrain menu
void
draw_new_terrain_menu (SDL_Surface * this_screen)
{
  int x, y, my_pitch;
  char cur_pixel;
  char str[20];
  Uint8 *screen_buffer;
  screen_buffer = (Uint8 *) this_screen->pixels;
  my_pitch = this_screen->pitch;

  draw_empty_menu (screen, white, x_new_terrain_menu, y_new_terrain_menu,
		   x_new_terrain_menu_lenght, y_new_terrain_menu_lenght);
  //draw the window title
  for (y = y_new_terrain_menu; y < y_new_terrain_menu + 15; y++)
    for (x = x_new_terrain_menu;
	 x < x_new_terrain_menu + x_new_terrain_menu_lenght; x++)
      *(screen_buffer + y * my_pitch + x) = darkblue;
  print_string ("New terrain", white, darkblue, x_new_terrain_menu + 2,
		y_new_terrain_menu + 2);
  //draw the x size string and box
  print_string ("X Size:", black, white, x_new_terrain_menu + 2,
		y_new_terrain_menu + 20);
  if (numeric_dialog_boxes[x_map_size_dialog].has_focus)
    draw_down_button (screen, x_new_terrain_menu + 52,
		      y_new_terrain_menu + 18, 42, 14);
  else
    draw_up_button (screen, x_new_terrain_menu + 52, y_new_terrain_menu + 18,
		    42, 14);
  print_string (numeric_dialog_boxes[x_map_size_dialog].dialog_text, black,
		white, x_new_terrain_menu + 54, y_new_terrain_menu + 20);


  //draw the y size string and box
  print_string ("Y Size:", black, white, x_new_terrain_menu + 2,
		y_new_terrain_menu + 38);
  if (numeric_dialog_boxes[y_map_size_dialog].has_focus)
    draw_down_button (screen, x_new_terrain_menu + 52,
		      y_new_terrain_menu + 36, 42, 14);
  else
    draw_up_button (screen, x_new_terrain_menu + 52, y_new_terrain_menu + 36,
		    42, 14);
  print_string (numeric_dialog_boxes[y_map_size_dialog].dialog_text, black,
		white, x_new_terrain_menu + 54, y_new_terrain_menu + 38);


  //draw the start height box
  print_string ("Base Height:", black, white, x_new_terrain_menu + 2,
		y_new_terrain_menu + 56);
  if (numeric_dialog_boxes[base_height_dialog].has_focus)
    draw_down_button (screen, x_new_terrain_menu + 90,
		      y_new_terrain_menu + 54, 24, 14);
  else
    draw_up_button (screen, x_new_terrain_menu + 90, y_new_terrain_menu + 54,
		    24, 14);
  print_string (numeric_dialog_boxes[base_height_dialog].dialog_text, black,
		white, x_new_terrain_menu + 92, y_new_terrain_menu + 56);

  //draw the OK and Cancel buttons
  draw_empty_menu (screen, white, x_new_terrain_menu + 40,
		   y_new_terrain_menu + 80, 20, 14);
  print_string ("Ok", black, white, x_new_terrain_menu + 42,
		y_new_terrain_menu + 82);
  draw_empty_menu (screen, white, x_new_terrain_menu + 70,
		   y_new_terrain_menu + 80, 50, 14);
  print_string ("Cancel", black, white, x_new_terrain_menu + 72,
		y_new_terrain_menu + 82);


}

void
check_new_terrain_menu (char text_input_char)
{
  //right mouse button kills the menu (cancel)
  if (long_pressed_button_r == 1)
    show_new_terrain_menu = 0;
  else
    //check the cancel button
  if ((long_pressed_button_l == 1 && x_mouse_pos >= x_new_terrain_menu + 70
	 && x_mouse_pos < x_new_terrain_menu + 70 + 50
	 && y_mouse_pos >= y_new_terrain_menu + 80
	 && y_mouse_pos < y_new_terrain_menu + 80 + 14)
	|| text_input_char == SDLK_ESCAPE)
    show_new_terrain_menu = 0;
  else
    //check the OK button
  if ((long_pressed_button_l == 1 && x_mouse_pos >= x_new_terrain_menu + 40
	 && x_mouse_pos < x_new_terrain_menu + 40 + 20
	 && y_mouse_pos >= y_new_terrain_menu + 80
	 && y_mouse_pos < y_new_terrain_menu + 80 + 14)
	|| text_input_char == SDLK_RETURN)
  {
    int color_to_fill;
    int i = 0;
    color_to_fill = atoi(numeric_dialog_boxes[base_height_dialog].dialog_text);
    show_new_terrain_menu = 0;
    WIDTH = atoi (numeric_dialog_boxes[x_map_size_dialog].dialog_text);
    HEIGHT = atoi (numeric_dialog_boxes[y_map_size_dialog].dialog_text);
    //do a bounds check
    if (WIDTH > numeric_dialog_boxes[x_map_size_dialog].max_number)
      WIDTH = numeric_dialog_boxes[x_map_size_dialog].max_number;
    if (WIDTH < numeric_dialog_boxes[x_map_size_dialog].min_number)
      WIDTH = numeric_dialog_boxes[x_map_size_dialog].min_number;
    if (HEIGHT > numeric_dialog_boxes[y_map_size_dialog].max_number)
      HEIGHT = numeric_dialog_boxes[y_map_size_dialog].max_number;
    if (HEIGHT < numeric_dialog_boxes[y_map_size_dialog].min_number)
      HEIGHT = numeric_dialog_boxes[y_map_size_dialog].min_number;
    if (color_to_fill > 255 || color_to_fill < 0)
      color_to_fill = 0;

    //everything is OK now
    allocate_mem();
    if(!terrain_height)return;
    for (i = 0; i < HEIGHT * WIDTH; i++)
      *(terrain_height + i) = color_to_fill;
  }
  else
    //check to see if the x_map_size_dialog got the focus
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_new_terrain_menu + 52
	&& x_mouse_pos < x_new_terrain_menu + 52 + 42
	&& y_mouse_pos >= y_new_terrain_menu + 18
	&& y_mouse_pos < y_new_terrain_menu + 18 + 14)
  {
    numeric_dialog_boxes[base_height_dialog].has_focus = 0;
    numeric_dialog_boxes[y_map_size_dialog].has_focus = 0;
    numeric_dialog_boxes[x_map_size_dialog].has_focus = 1;
    numeric_dialog_boxes[x_map_size_dialog].text_offset = 0;
  }
  else
    //check to see if the y_map_size_dialog got the focus
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_new_terrain_menu + 52
	&& x_mouse_pos < x_new_terrain_menu + 52 + 42
	&& y_mouse_pos >= y_new_terrain_menu + 36
	&& y_mouse_pos < y_new_terrain_menu + 36 + 14)
  {
    numeric_dialog_boxes[base_height_dialog].has_focus = 0;
    numeric_dialog_boxes[y_map_size_dialog].has_focus = 1;
    numeric_dialog_boxes[y_map_size_dialog].text_offset = 0;
    numeric_dialog_boxes[x_map_size_dialog].has_focus = 0;
  }
  else
    if (long_pressed_button_l == 1 && x_mouse_pos >= x_new_terrain_menu + 90
	&& x_mouse_pos < x_new_terrain_menu + 90 + 24
	&& y_mouse_pos >= y_new_terrain_menu + 54
	&& y_mouse_pos < y_new_terrain_menu + 54 + 14)
  {
    numeric_dialog_boxes[base_height_dialog].has_focus = 1;
    numeric_dialog_boxes[base_height_dialog].text_offset = 0;
    numeric_dialog_boxes[y_map_size_dialog].has_focus = 0;
    numeric_dialog_boxes[x_map_size_dialog].has_focus = 0;
  }

  //check to see for the tab
  if (text_input_char == SDLK_TAB)
  {
    if (numeric_dialog_boxes[base_height_dialog].has_focus)
    {
      numeric_dialog_boxes[x_map_size_dialog].has_focus = 1;
      numeric_dialog_boxes[x_map_size_dialog].text_offset = 0;
      numeric_dialog_boxes[y_map_size_dialog].has_focus = 0;
      numeric_dialog_boxes[base_height_dialog].has_focus = 0;
    }
    else if (numeric_dialog_boxes[x_map_size_dialog].has_focus)
    {
      numeric_dialog_boxes[x_map_size_dialog].has_focus = 0;
      numeric_dialog_boxes[y_map_size_dialog].has_focus = 1;
      numeric_dialog_boxes[y_map_size_dialog].text_offset = 0;
      numeric_dialog_boxes[base_height_dialog].has_focus = 0;
    }
    else if (numeric_dialog_boxes[y_map_size_dialog].has_focus)
    {
      numeric_dialog_boxes[x_map_size_dialog].has_focus = 0;
      numeric_dialog_boxes[y_map_size_dialog].has_focus = 0;
      numeric_dialog_boxes[base_height_dialog].has_focus = 1;
      numeric_dialog_boxes[base_height_dialog].text_offset = 0;
    }


  }

  //now, check to see if we get any character
  if (text_input_char)
  {
    int dialog_text_offset;
    if (numeric_dialog_boxes[base_height_dialog].has_focus == 1)
    {
      //check to see if it is a numeric char, and if we didn't exceede the max lenght limit
      if (text_input_char >= '0' && text_input_char <= '9' &&
	  numeric_dialog_boxes[base_height_dialog].text_offset <
	  numeric_dialog_boxes[base_height_dialog].dialog_lenght)
      {
	dialog_text_offset =
	  numeric_dialog_boxes[base_height_dialog].text_offset;
	numeric_dialog_boxes[base_height_dialog].
	  dialog_text[dialog_text_offset] = text_input_char;
	numeric_dialog_boxes[base_height_dialog].
	  dialog_text[dialog_text_offset + 1] = 0;
	numeric_dialog_boxes[base_height_dialog].text_offset++;

      }
      else
	if (text_input_char == SDLK_BACKSPACE
	    && numeric_dialog_boxes[base_height_dialog].text_offset > 0)
      {
	numeric_dialog_boxes[base_height_dialog].text_offset--;
	numeric_dialog_boxes[base_height_dialog].
	  dialog_text[numeric_dialog_boxes[base_height_dialog].text_offset] =
	  0;
      }
    }
    //check the x_map_size_dialog
    if (numeric_dialog_boxes[x_map_size_dialog].has_focus == 1)
    {
      //check to see if it is a numeric char, and if we didn't exceede the max lenght limit
      if (text_input_char >= '0' && text_input_char <= '9' &&
	  numeric_dialog_boxes[x_map_size_dialog].text_offset <
	  numeric_dialog_boxes[x_map_size_dialog].dialog_lenght)
      {
	dialog_text_offset =
	  numeric_dialog_boxes[x_map_size_dialog].text_offset;
	numeric_dialog_boxes[x_map_size_dialog].
	  dialog_text[dialog_text_offset] = text_input_char;
	numeric_dialog_boxes[x_map_size_dialog].
	  dialog_text[dialog_text_offset + 1] = 0;
	numeric_dialog_boxes[x_map_size_dialog].text_offset++;

      }
      else
	if (text_input_char == SDLK_BACKSPACE
	    && numeric_dialog_boxes[x_map_size_dialog].text_offset > 0)
      {
	numeric_dialog_boxes[x_map_size_dialog].text_offset--;
	numeric_dialog_boxes[x_map_size_dialog].
	  dialog_text[numeric_dialog_boxes[x_map_size_dialog].text_offset] =
	  0;
      }
    }
    //check the y_map_size_dialog
    if (numeric_dialog_boxes[y_map_size_dialog].has_focus == 1)
    {
      //check to see if it is a numeric char, and if we didn't exceede the max lenght limit
      if (text_input_char >= '0' && text_input_char <= '9' &&
	  numeric_dialog_boxes[y_map_size_dialog].text_offset <
	  numeric_dialog_boxes[y_map_size_dialog].dialog_lenght)
      {
	dialog_text_offset =
	  numeric_dialog_boxes[y_map_size_dialog].text_offset;
	numeric_dialog_boxes[y_map_size_dialog].
	  dialog_text[dialog_text_offset] = text_input_char;
	numeric_dialog_boxes[y_map_size_dialog].
	  dialog_text[dialog_text_offset + 1] = 0;
	numeric_dialog_boxes[y_map_size_dialog].text_offset++;

      }
      else
	if (text_input_char == SDLK_BACKSPACE
	    && numeric_dialog_boxes[y_map_size_dialog].text_offset > 0)
      {
	numeric_dialog_boxes[y_map_size_dialog].text_offset--;
	numeric_dialog_boxes[y_map_size_dialog].
	  dialog_text[numeric_dialog_boxes[y_map_size_dialog].text_offset] =
	  0;
      }
    }

  }





}


/////////////////////////////////////////////////
//draw the generate terrain menu
void
draw_generate_menu (SDL_Surface * this_screen)
{
  int x, y, my_pitch;
  char cur_pixel;
  char str[20];
  Uint8 *screen_buffer;
  screen_buffer = (Uint8 *) this_screen->pixels;
  my_pitch = this_screen->pitch;

  draw_empty_menu (screen, white, x_generate_terrain_menu,
		   y_generate_terrain_menu, x_generate_terrain_menu_lenght,
		   y_generate_terrain_menu_lenght);
  //draw the window title
  for (y = y_generate_terrain_menu; y < y_generate_terrain_menu + 15; y++)
    for (x = x_generate_terrain_menu;
	 x < x_generate_terrain_menu + x_generate_terrain_menu_lenght; x++)
      *(screen_buffer + y * my_pitch + x) = darkblue;
  print_string ("Generate terrain", white, darkblue,
		x_generate_terrain_menu + 2, y_generate_terrain_menu + 2);
  //draw the seed string and box
  print_string ("Seed:", black, white, x_generate_terrain_menu + 2,
		y_generate_terrain_menu + 20);
  if (numeric_dialog_boxes[seed_dialog].has_focus)
    draw_down_button (screen, x_generate_terrain_menu + 52,
		      y_generate_terrain_menu + 18, 76, 14);
  else
    draw_up_button (screen, x_generate_terrain_menu + 52,
		    y_generate_terrain_menu + 18, 62, 14);
  print_string (numeric_dialog_boxes[seed_dialog].dialog_text, black, white,
		x_generate_terrain_menu + 54, y_generate_terrain_menu + 20);
  //draw the random seed box
  draw_empty_menu (screen, white, x_generate_terrain_menu + 140,
		   y_generate_terrain_menu + 18, 50, 14);
  print_string ("Random", black, white, x_generate_terrain_menu + 142,
		y_generate_terrain_menu + 20);


  //draw the overwrite terrain check box
  draw_empty_menu (screen, white, x_generate_terrain_menu + 2,
		   y_generate_terrain_menu + 40, 14, 14);
  print_string ("Overwrite existing terrain", black, white,
		x_generate_terrain_menu + 4 + 14,
		y_generate_terrain_menu + 42);
  if (overwrite_terrain)
    print_string ("X", black, white, x_generate_terrain_menu + 4,
		  y_generate_terrain_menu + 42);



  //draw the OK and Cancel buttons
  draw_empty_menu (screen, white, x_generate_terrain_menu + 40,
		   y_generate_terrain_menu + 80, 20, 14);
  print_string ("Ok", black, white, x_generate_terrain_menu + 42,
		y_generate_terrain_menu + 82);
  draw_empty_menu (screen, white, x_generate_terrain_menu + 70,
		   y_generate_terrain_menu + 80, 50, 14);
  print_string ("Cancel", black, white, x_generate_terrain_menu + 72,
		y_generate_terrain_menu + 82);


}

///////////////////////////////////////////////

void check_generate_terrain_menu (char text_input_char)
{
  //right mouse button kills the menu (cancel)
  if (long_pressed_button_r == 1)
  show_generate_terrain_menu = 0;
  else
    //check the overwrite terrain button
  if (long_pressed_button_l == 1
	&& x_mouse_pos >= x_generate_terrain_menu + 2
	&& x_mouse_pos < x_generate_terrain_menu + 2 + 14
	&& y_mouse_pos >= y_generate_terrain_menu + 40
	&& y_mouse_pos < y_generate_terrain_menu + 40 + 14)
    overwrite_terrain = !overwrite_terrain;
  else
    //check the random seed button
  if (long_pressed_button_l == 1
	&& x_mouse_pos >= x_generate_terrain_menu + 140
	&& x_mouse_pos < x_generate_terrain_menu + 140 + 50
	&& y_mouse_pos >= y_generate_terrain_menu + 18
	&& y_mouse_pos < y_generate_terrain_menu + 18 + 14)
  {
    int this_seed;
    this_seed = rand ();
    this_seed = this_seed * rand ();
    sprintf (numeric_dialog_boxes[seed_dialog].dialog_text, "%d", this_seed);
    numeric_dialog_boxes[seed_dialog].text_offset = 0;

  }
  else
    //check the cancel button
  if ((long_pressed_button_l == 1
	 && x_mouse_pos >= x_generate_terrain_menu + 70
	 && x_mouse_pos < x_generate_terrain_menu + 70 + 50
	 && y_mouse_pos >= y_generate_terrain_menu + 80
	 && y_mouse_pos < y_generate_terrain_menu + 80 + 14)
	|| text_input_char == SDLK_ESCAPE)
    show_generate_terrain_menu = 0;
  else
    //check the OK button
  if ((long_pressed_button_l == 1
	 && x_mouse_pos >= x_generate_terrain_menu + 40
	 && x_mouse_pos < x_generate_terrain_menu + 40 + 20
	 && y_mouse_pos >= y_generate_terrain_menu + 80
	 && y_mouse_pos < y_generate_terrain_menu + 80 + 14)
	|| text_input_char == SDLK_RETURN)
  {
    seed = atoi (numeric_dialog_boxes[seed_dialog].dialog_text);
    srand (atoi (numeric_dialog_boxes[seed_dialog].dialog_text));
    copy_to_undo_buffer();
    if(overwrite_terrain)overdraw_terrain();
    else make_terrain ();
    show_generate_terrain_menu = 0;
  }
  else
    //now, check to see if we get any character
  if (text_input_char)
  {
    int dialog_text_offset;
    //check to see if it is a numeric char, and if we didn't exceede the max lenght limit
    if (text_input_char >= '0' && text_input_char <= '9' &&
	numeric_dialog_boxes[seed_dialog].text_offset <
	numeric_dialog_boxes[seed_dialog].dialog_lenght)
    {
      dialog_text_offset = numeric_dialog_boxes[seed_dialog].text_offset;
      numeric_dialog_boxes[seed_dialog].dialog_text[dialog_text_offset] =
	text_input_char;
      numeric_dialog_boxes[seed_dialog].dialog_text[dialog_text_offset + 1] =
	0;
      numeric_dialog_boxes[seed_dialog].text_offset++;

    }
    else
      if (text_input_char == SDLK_BACKSPACE
	  && numeric_dialog_boxes[seed_dialog].text_offset > 0)
    {
      numeric_dialog_boxes[seed_dialog].text_offset--;
      numeric_dialog_boxes[seed_dialog].
	dialog_text[numeric_dialog_boxes[seed_dialog].text_offset] = 0;
    }

  }



}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/////Draw the "view menu"

void
draw_view_menu (SDL_Surface * this_screen)
{
  int x, y, my_pitch;
  char cur_pixel;
  char str[20];
  Uint8 *screen_buffer;
  screen_buffer = (Uint8 *) this_screen->pixels;
  my_pitch = this_screen->pitch;

  draw_empty_menu (screen, white, x_view_menu, y_view_menu,
		   x_view_menu_lenght, y_view_menu_lenght);
  //draw the window title
  for (y = y_view_menu; y < y_view_menu + 15; y++)
    for (x = x_view_menu; x < x_view_menu + x_view_menu_lenght; x++)
      *(screen_buffer + y * my_pitch + x) = darkblue;
  print_string ("View...", white, darkblue, x_view_menu + 2, y_view_menu + 2);
  //draw the view toolbar box
  draw_empty_menu (screen, white, x_view_menu + 2, y_view_menu + 20, 14, 14);
  print_string ("Toolbar", black, white, x_view_menu + 4 + 14,
		y_view_menu + 22);
  if (tool_bar)
    print_string ("X", black, white, x_view_menu + 4, y_view_menu + 22);
  //draw the view minimap box
  draw_empty_menu (screen, white, x_view_menu + 2, y_view_menu + 40, 14, 14);
  print_string ("Minimap", black, white, x_view_menu + 4 + 14,y_view_menu + 42);
  if (mini_map)
    print_string ("X", black, white, x_view_menu + 4, y_view_menu + 42);
  //draw the view status_bar
  draw_empty_menu (screen, white, x_view_menu + 2, y_view_menu + 60, 14, 14);
  print_string ("Status bar", black, white, x_view_menu + 4 + 14,y_view_menu + 62);
  if (status_bar)
    print_string ("X", black, white, x_view_menu + 4, y_view_menu + 62);
  //draw the Grid none
  draw_empty_menu (screen, white, x_view_menu + 2, y_view_menu + 80, 14, 14);
  print_string ("Grid: Off", black, white, x_view_menu + 4 + 14,y_view_menu + 82);
  if (!grid)
    print_string ("X", black, white, x_view_menu + 4, y_view_menu + 82);
  //draw the Grid 16
  draw_empty_menu (screen, white, x_view_menu + 2, y_view_menu + 100, 14, 14);
  print_string ("Grid: 16x16", black, white, x_view_menu + 4 + 14,y_view_menu + 102);
  if (grid == 16)
    print_string ("X", black, white, x_view_menu + 4, y_view_menu + 102);
  //draw the Grid 32
  draw_empty_menu (screen, white, x_view_menu + 2, y_view_menu + 120, 14, 14);
  print_string ("Grid: 32x32", black, white, x_view_menu + 4 + 14,y_view_menu + 122);
  if (grid == 32)
    print_string ("X", black, white, x_view_menu + 4, y_view_menu + 122);
  //draw the Grid 64
  draw_empty_menu (screen, white, x_view_menu + 2, y_view_menu + 140, 14, 14);
  print_string ("Grid: 64x64", black, white, x_view_menu + 4 + 14,y_view_menu + 142);
  if (grid == 64)
    print_string ("X", black, white, x_view_menu + 4, y_view_menu + 142);
  //draw the Grid 128
  draw_empty_menu (screen, white, x_view_menu + 2, y_view_menu + 160, 14, 14);
  print_string ("Grid: 128x128", black, white, x_view_menu + 4 + 14,y_view_menu + 162);
  if (grid == 128)
    print_string ("X", black, white, x_view_menu + 4, y_view_menu + 162);
  //draw the Grid 256
  draw_empty_menu (screen, white, x_view_menu + 2, y_view_menu + 180, 14, 14);
  print_string ("Grid: 256x256", black, white, x_view_menu + 4 + 14,y_view_menu + 182);
  if (grid == 256)
    print_string ("X", black, white, x_view_menu + 4, y_view_menu + 182);

  //draw the color/gray menu
  draw_empty_menu (screen, white, x_view_menu + 2, y_view_menu + 200, 14, 14);
  print_string ("Gray Shades", black, white, x_view_menu + 4 + 14,y_view_menu + 202);
  if (gray_shades) print_string ("X", black, white, x_view_menu + 4, y_view_menu + 202);

  //draw the OK button
  draw_empty_menu (screen, white, x_view_menu + 50, y_view_menu + 220, 20,14);
  print_string ("Ok", black, white, x_view_menu + 52, y_view_menu + 222);
}


void check_view_menu (char text_input_char)
{
  //right mouse button kills the menu (cancel)
  if (long_pressed_button_r == 1)
    show_view_menu = 0;
  //check the toolbar button
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_view_menu + 2
      && x_mouse_pos < x_view_menu + 2 + 14 && y_mouse_pos >= y_view_menu + 20
      && y_mouse_pos < y_view_menu + 20 + 14)
    tool_bar = !tool_bar;
  else
    //check the minimap button
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_view_menu + 2
	&& x_mouse_pos < x_view_menu + 2 + 14
	&& y_mouse_pos >= y_view_menu + 40
	&& y_mouse_pos < y_view_menu + 40 + 14)
    mini_map = !mini_map;
  //check the statusbar button
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_view_menu + 2
      && x_mouse_pos < x_view_menu + 2 + 14 && y_mouse_pos >= y_view_menu + 60
      && y_mouse_pos < y_view_menu + 60 + 14)
    status_bar = !status_bar;
  else
    //check the grid off button
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_view_menu + 2
	&& x_mouse_pos < x_view_menu + 2 + 14
	&& y_mouse_pos >= y_view_menu + 80
	&& y_mouse_pos < y_view_menu + 80 + 14)
    grid = 0;
  else
    //check the grid 16 button
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_view_menu + 2
	&& x_mouse_pos < x_view_menu + 2 + 14
	&& y_mouse_pos >= y_view_menu + 100
	&& y_mouse_pos < y_view_menu + 100 + 14)
    grid = 16;
  else
    //check the grid 32 button
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_view_menu + 2
	&& x_mouse_pos < x_view_menu + 2 + 14
	&& y_mouse_pos >= y_view_menu + 120
	&& y_mouse_pos < y_view_menu + 120 + 14)
    grid = 32;
  else
    //check the grid 64 button
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_view_menu + 2
	&& x_mouse_pos < x_view_menu + 2 + 14
	&& y_mouse_pos >= y_view_menu + 140
	&& y_mouse_pos < y_view_menu + 140 + 14)
    grid = 64;
  else
    //check the grid 128 button
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_view_menu + 2
	&& x_mouse_pos < x_view_menu + 2 + 14
	&& y_mouse_pos >= y_view_menu + 160
	&& y_mouse_pos < y_view_menu + 160 + 14)
    grid = 128;
  else
    //check the grid 256 button
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_view_menu + 2
	&& x_mouse_pos < x_view_menu + 2 + 14
	&& y_mouse_pos >= y_view_menu + 180
	&& y_mouse_pos < y_view_menu + 180 + 14)
    grid = 256;
  else
  //check the gray shades button
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_view_menu + 2
	&& x_mouse_pos < x_view_menu + 2 + 14
	&& y_mouse_pos >= y_view_menu + 200
	&& y_mouse_pos < y_view_menu + 200 + 14)
    {
		gray_shades=!gray_shades;
  		if(gray_shades)make_gray_pallete();
  		else make_color_pallete();
	}
  else
    //check the OK button
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_view_menu + 50
	&& x_mouse_pos < x_view_menu + 50 + 20
	&& y_mouse_pos >= y_view_menu + 220
	&& y_mouse_pos < y_view_menu + 220 + 14)
    show_view_menu = 0;


}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/////Draw the "rotation menu"

void draw_rotate_menu (SDL_Surface * this_screen)
{
  int x, y, my_pitch;
  char cur_pixel;
  char str[20];
  Uint8 *screen_buffer;
  screen_buffer = (Uint8 *) this_screen->pixels;
  my_pitch = this_screen->pitch;

  draw_empty_menu (screen, white, x_rotation_menu, y_rotation_menu,
		   x_rotation_menu_lenght, y_rotation_menu_lenght);
  //draw the window title
  for (y = y_rotation_menu; y < y_rotation_menu + 15; y++)
    for (x = x_rotation_menu; x < x_rotation_menu + x_rotation_menu_lenght; x++)
      *(screen_buffer + y * my_pitch + x) = darkblue;
  print_string ("Flip and Rotation", white, darkblue, x_rotation_menu + 2, y_rotation_menu + 2);
  //draw the Horizontal Flip
  draw_empty_menu (screen, white, x_rotation_menu + 2, y_rotation_menu + 20, 14, 14);
  print_string ("Horizontal (x) flip", black, white, x_rotation_menu + 4 + 14,y_rotation_menu + 22);
  if (rotation_type==rotation_flip_x)
    print_string ("X", black, white, x_rotation_menu + 4, y_rotation_menu + 22);
  //draw the Vertical flip
  draw_empty_menu (screen, white, x_rotation_menu + 2, y_rotation_menu + 40, 14, 14);
  print_string ("Vertical   (y) flip", black, white, x_rotation_menu + 4 + 14,y_rotation_menu + 42);
  if (rotation_type==rotation_flip_y)print_string ("X", black, white, x_rotation_menu + 4, y_rotation_menu + 42);
  //draw the Height flip
  draw_empty_menu (screen, white, x_rotation_menu + 2, y_rotation_menu + 60, 14, 14);
  print_string ("Height     (z) flip", black, white, x_rotation_menu + 4 + 14,y_rotation_menu + 62);
  if (rotation_type==rotation_flip_z)print_string ("X", black, white, x_rotation_menu + 4, y_rotation_menu + 62);
  //draw the 90_CW rotation
  draw_empty_menu (screen, white, x_rotation_menu + 2, y_rotation_menu + 80, 14, 14);
  print_string ("Rotate 90 CW", black, white, x_rotation_menu + 4 + 14,y_rotation_menu + 82);
  if (rotation_type==rotation_CW_90)print_string ("X", black, white, x_rotation_menu + 4, y_rotation_menu + 82);
  //draw the 90_CCW rotation
  draw_empty_menu (screen, white, x_rotation_menu + 2, y_rotation_menu + 100, 14, 14);
  print_string ("Rotate 90 CCW", black, white, x_rotation_menu + 4 + 14,y_rotation_menu + 102);
  if (rotation_type==rotation_CCW_90)print_string ("X", black, white, x_rotation_menu + 4, y_rotation_menu + 102);
  //draw the 180 rotation
  draw_empty_menu (screen, white, x_rotation_menu + 2, y_rotation_menu + 120, 14, 14);
  print_string ("Rotate 180", black, white, x_rotation_menu + 4 + 14,y_rotation_menu + 122);
  if (rotation_type==rotation_180)print_string ("X", black, white, x_rotation_menu + 4, y_rotation_menu + 122);
  //draw the OK button
  draw_empty_menu (screen, white, x_rotation_menu + 70, y_rotation_menu + 140, 20,14);
  print_string ("Ok", black, white, x_rotation_menu + 72, y_rotation_menu + 142);
}


void check_rotate_menu (char text_input_char)
{
  //right mouse button kills the menu (cancel)
  if (long_pressed_button_r == 1)
    show_rotate_menu = 0;
  //check the Hor. flip
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_rotation_menu + 2
      && x_mouse_pos < x_rotation_menu + 2 + 14 && y_mouse_pos >= y_rotation_menu + 20
      && y_mouse_pos < y_rotation_menu + 20 + 14)
    rotation_type=rotation_flip_x;
  else
    //check Ver. flip
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_rotation_menu + 2
	&& x_mouse_pos < x_rotation_menu + 2 + 14
	&& y_mouse_pos >= y_rotation_menu + 40
	&& y_mouse_pos < y_rotation_menu + 40 + 14)
    rotation_type=rotation_flip_y;
  //check the Height flip
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_rotation_menu + 2
      && x_mouse_pos < x_rotation_menu + 2 + 14 && y_mouse_pos >= y_rotation_menu + 60
      && y_mouse_pos < y_rotation_menu + 60 + 14)
    rotation_type=rotation_flip_z;
  else
    //check 90 CW rotation
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_rotation_menu + 2
	&& x_mouse_pos < x_rotation_menu + 2 + 14
	&& y_mouse_pos >= y_rotation_menu + 80
	&& y_mouse_pos < y_rotation_menu + 80 + 14)
    rotation_type=rotation_CW_90;
  else
    //check the 90 CCW rotation
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_rotation_menu + 2
	&& x_mouse_pos < x_rotation_menu + 2 + 14
	&& y_mouse_pos >= y_rotation_menu + 100
	&& y_mouse_pos < y_rotation_menu + 100 + 14)
    rotation_type=rotation_CCW_90;
  else
    //check the 180 rotation
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_rotation_menu + 2
	&& x_mouse_pos < x_rotation_menu + 2 + 14
	&& y_mouse_pos >= y_rotation_menu + 120
	&& y_mouse_pos < y_rotation_menu + 120 + 14)
    rotation_type=rotation_180;
  else
    //check the OK button
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_rotation_menu + 70
	&& x_mouse_pos < x_rotation_menu + 70 + 20
	&& y_mouse_pos >= y_rotation_menu + 140
	&& y_mouse_pos < y_rotation_menu + 140 + 14)
		{
			if(rotation_type==rotation_flip_x)flip_x();
			else if(rotation_type==rotation_flip_y)flip_y();
			else if(rotation_type==rotation_flip_z)flip_z();
			else if(rotation_type==rotation_CW_90)rotate_90_CW();
			else if(rotation_type==rotation_CCW_90)rotate_90_CCW();
			else if(rotation_type==rotation_180)rotate_180();
		    show_rotate_menu = 0;
		}


}

/////////////////////////////////////////////////
//draw the replace menu
void draw_replace_menu (SDL_Surface * this_screen)
{
  int x, y, my_pitch;
  char cur_pixel;
  int i,j,k,l;
  char cur_char;
  char str[120];
  Uint8 *screen_buffer;
  screen_buffer = (Uint8 *) this_screen->pixels;
  my_pitch = this_screen->pitch;

  draw_empty_menu (screen, white,x_replace_menu,y_replace_menu,x_replace_menu_lenght,y_replace_menu_lenght);
  //draw the window title
  for (y = y_replace_menu; y < y_replace_menu + 15; y++)
    for (x = x_replace_menu; x < x_replace_menu + x_replace_menu_lenght; x++)
      *(screen_buffer + y * my_pitch + x) = darkblue;

  print_string ("Replace Settings", white, darkblue, x_replace_menu + 2,y_replace_menu + 2);
  //draw the tolerance string and box
  print_string ("Tolerance:", black, white, x_replace_menu + 2,y_replace_menu + 20);
  draw_down_button (screen, x_replace_menu + 80, y_replace_menu + 18, 25, 14);
  print_string (numeric_dialog_boxes[tolerance].dialog_text, black, white,x_replace_menu + 82, y_replace_menu + 20);

  print_string ("Tolerance Mode:", black, white, x_replace_menu + 4,y_replace_menu + 42);
  //draw the greater tolerance check box
  draw_empty_menu (screen, white, x_replace_menu + 40, y_replace_menu + 60,14, 14);
  print_string ("+", black, white, x_replace_menu + 42 + 14,y_replace_menu + 62);
  if(temp_tolerance_mode == greater)
  print_string ("X", black, white, x_replace_menu + 42,y_replace_menu + 62);

  //draw the leaser tolerance check box
  draw_empty_menu (screen, white, x_replace_menu + 40, y_replace_menu + 80,14, 14);
  print_string ("-", black, white, x_replace_menu + 42 + 14,y_replace_menu + 82);
  if(temp_tolerance_mode == leaser)
  print_string ("X", black, white, x_replace_menu + 42,y_replace_menu + 82);

  //draw the greater or leaser tolerance check box
  draw_empty_menu (screen, white, x_replace_menu + 40, y_replace_menu + 100,14, 14);
  print_string ("+/-", black, white, x_replace_menu + 42 + 14,y_replace_menu + 102);
  if(temp_tolerance_mode == greater_or_leaser)
  print_string ("X", black, white, x_replace_menu + 42,y_replace_menu + 102);

  print_string ("Replace Mode:", black, white, x_replace_menu + 4,y_replace_menu + 122);

  //draw the greater replace check box
  draw_empty_menu (screen, white, x_replace_menu + 40, y_replace_menu + 140,14, 14);
  print_string ("+", black, white, x_replace_menu + 42 + 14,y_replace_menu + 142);
  if(temp_tolerance_replace_mode == tolerance_replace_plus)
  print_string ("X", black, white, x_replace_menu + 42,y_replace_menu + 142);

  //draw the leaser replace check box
  draw_empty_menu (screen, white, x_replace_menu + 40, y_replace_menu + 160,14, 14);
  print_string ("-", black, white, x_replace_menu + 42 + 14,y_replace_menu + 162);
  if(temp_tolerance_replace_mode == tolerance_replace_minus)
  print_string ("X", black, white, x_replace_menu + 42,y_replace_menu + 162);

  //draw the equal replace check box
  draw_empty_menu (screen, white, x_replace_menu + 40, y_replace_menu + 180,14, 14);
  print_string ("=", black, white, x_replace_menu + 42 + 14,y_replace_menu + 182);
  if(temp_tolerance_replace_mode == tolerance_replace_equal)
  print_string ("X", black, white, x_replace_menu + 42,y_replace_menu + 182);


  print_string ("Replace With:", black, white, x_replace_menu + 4,y_replace_menu + 202);

  //draw the pattern replace check box
  draw_empty_menu (screen, white, x_replace_menu + 40, y_replace_menu + 220,14, 14);
  print_string ("Solid", black, white, x_replace_menu + 42 + 14,y_replace_menu + 222);
  if(temp_tolerance_replace_mode_2 == replace_mode_solid)
  print_string ("X", black, white, x_replace_menu + 42,y_replace_menu + 222);


  //draw the pattern replace check box
  draw_empty_menu (screen, white, x_replace_menu + 40, y_replace_menu + 240,14, 14);
  print_string ("Pattern", black, white, x_replace_menu + 42 + 14,y_replace_menu + 242);
  if(temp_tolerance_replace_mode_2 == replace_mode_pattern)
  print_string ("X", black, white, x_replace_menu + 42,y_replace_menu + 242);

  //draw the pattern file name.
  print_string ("Pattern:", black, white, x_replace_menu +2,y_replace_menu + 262);
  draw_empty_menu (screen, white, x_replace_menu + 60, y_replace_menu + 260,172, 14);
  j=0;
		while(1)
		{
			if(pattern_file_name[j]==0)break;
			j++;
		}
		i=j;
		if(j>20)
			{
				j-=24;
				k=i-j;
			}
		else
			{
				k=j;
				j=0;
			}
		i=0;
		while(i<k)
		{
			cur_char=pattern_file_name[j];
			*(str+i)=cur_char;
			if(cur_char==0)break;
			j++;
			i++;
		}
		*(str+i)=0;
  if(!current_pattern.object_mem)print_string("None", black, white, x_replace_menu +62,y_replace_menu + 262);
  else
  print_string(str, black, white, x_replace_menu +62,y_replace_menu + 262);

  //draw the OK, Cancel and Change pattern buttons
  draw_empty_menu (screen, white, x_replace_menu + 30, y_replace_menu + 280,20, 14);
  print_string ("Ok", black, white, x_replace_menu + 32,y_replace_menu + 282);
  draw_empty_menu (screen, white, x_replace_menu + 60, y_replace_menu + 280,50, 14);
  print_string ("Cancel", black, white, x_replace_menu + 62,y_replace_menu + 282);
  draw_empty_menu (screen, white, x_replace_menu + 120, y_replace_menu + 280,110, 14);
  print_string ("Change Pattern", black, white, x_replace_menu + 122,y_replace_menu + 282);
}


void check_replace_menu (char text_input_char)
{
  //right mouse button kills the menu (cancel)
  if (long_pressed_button_r == 1)
    show_replace_menu = 0;
  else
    //check the greater than tolerance mode
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_replace_menu + 40
	&& x_mouse_pos < x_replace_menu + 40 + 14
	&& y_mouse_pos >= y_replace_menu + 60
	&& y_mouse_pos < y_replace_menu + 60 + 14)
    temp_tolerance_mode = greater;
  else
    //check the leaser than tolerance mode
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_replace_menu + 40
	&& x_mouse_pos < x_replace_menu + 40 + 14
	&& y_mouse_pos >= y_replace_menu + 80
	&& y_mouse_pos < y_replace_menu + 80 + 14)
    temp_tolerance_mode = leaser;
  else
    //check the leaser or greater tolerance mode
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_replace_menu + 40
	&& x_mouse_pos < x_replace_menu + 40 + 14
	&& y_mouse_pos >= y_replace_menu + 100
	&& y_mouse_pos < y_replace_menu + 100 + 14)
    temp_tolerance_mode = greater_or_leaser;
  else
  //check the greater replace mode
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_replace_menu + 40
	&& x_mouse_pos < x_replace_menu + 40 + 14
	&& y_mouse_pos >= y_replace_menu + 140
	&& y_mouse_pos < y_replace_menu + 140 + 14)
    temp_tolerance_replace_mode = tolerance_replace_plus;
  else
  //check the leaser replace mode
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_replace_menu + 40
	&& x_mouse_pos < x_replace_menu + 40 + 14
	&& y_mouse_pos >= y_replace_menu + 160
	&& y_mouse_pos < y_replace_menu + 160 + 14)
    temp_tolerance_replace_mode = tolerance_replace_minus;
  else
  //check the equal replace mode
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_replace_menu + 40
	&& x_mouse_pos < x_replace_menu + 40 + 14
	&& y_mouse_pos >= y_replace_menu + 180
	&& y_mouse_pos < y_replace_menu + 180 + 14)
    temp_tolerance_replace_mode = tolerance_replace_equal;
  else
  //check the pattern replace_mode_2
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_replace_menu + 40
	&& x_mouse_pos < x_replace_menu + 40 + 14
	&& y_mouse_pos >= y_replace_menu + 220
	&& y_mouse_pos < y_replace_menu + 220 + 14)
    temp_tolerance_replace_mode_2 = replace_mode_solid;
  else
  //check the pattern replace_mode_2
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_replace_menu + 40
	&& x_mouse_pos < x_replace_menu + 40 + 14
	&& y_mouse_pos >= y_replace_menu + 240
	&& y_mouse_pos < y_replace_menu + 240 + 14)
    temp_tolerance_replace_mode_2 = replace_mode_pattern;
  else

  //check the cancel button
  if ((long_pressed_button_l == 1 && x_mouse_pos >= x_replace_menu + 60
       && x_mouse_pos < x_replace_menu + 60 + 50
       && y_mouse_pos >= y_replace_menu + 280
       && y_mouse_pos < y_replace_menu + 280 + 14)
      || text_input_char == SDLK_ESCAPE)
    show_replace_menu = 0;
  else
  //check the load pattern button
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_replace_menu + 120
       && x_mouse_pos < x_replace_menu + 120 + 110
       && y_mouse_pos >= y_replace_menu + 280
       && y_mouse_pos < y_replace_menu + 280 + 14)
    {
		SDL_Event event;
		if(current_pattern.object_mem)
			{
				free(current_pattern.object_mem);
				current_pattern.object_mem=0;
			}
		load_object=2;//tell the file open save function to load a pattern
		long_pressed_button_l = 0;
		DoFileOpenSave (0);
    	while (SDL_PollEvent (&event));	//clears all the events
	}

  else
    //check the OK button
  if ((long_pressed_button_l == 1 && x_mouse_pos >= x_replace_menu + 30
	 && x_mouse_pos < x_replace_menu + 30 + 20
	 && y_mouse_pos >= y_replace_menu + 280
	 && y_mouse_pos < y_replace_menu + 280 + 14)
	|| text_input_char == SDLK_RETURN)
  {
    int box_tolerance;
    box_tolerance = atoi (numeric_dialog_boxes[tolerance].dialog_text);
    //bounds checking
    if (box_tolerance > numeric_dialog_boxes[tolerance].max_number)
      box_tolerance = numeric_dialog_boxes[tolerance].max_number;
    else if (box_tolerance < numeric_dialog_boxes[tolerance].min_number)
      box_tolerance = numeric_dialog_boxes[tolerance].min_number;
    tolerance_value = box_tolerance;
    tolerance_mode = temp_tolerance_mode;
    tolerance_replace_mode = temp_tolerance_replace_mode;
    tolerance_replace_mode_2 = temp_tolerance_replace_mode_2;
    show_replace_menu = 0;
  }
  else
    //now, check to see if we get any character
  if (text_input_char)
  {
    int dialog_text_offset;
    //check to see if it is a numeric char, and if we didn't exceede the max lenght limit
    if (text_input_char >= '0' && text_input_char <= '9' &&
	numeric_dialog_boxes[tolerance].text_offset <
	numeric_dialog_boxes[tolerance].dialog_lenght)
    {
      dialog_text_offset = numeric_dialog_boxes[tolerance].text_offset;
      numeric_dialog_boxes[tolerance].dialog_text[dialog_text_offset] =
	text_input_char;
      numeric_dialog_boxes[tolerance].dialog_text[dialog_text_offset + 1] = 0;
      numeric_dialog_boxes[tolerance].text_offset++;

    }
    else
      if (text_input_char == SDLK_BACKSPACE
	  && numeric_dialog_boxes[tolerance].text_offset > 0)
    {
      numeric_dialog_boxes[tolerance].text_offset--;
      numeric_dialog_boxes[tolerance].
	dialog_text[numeric_dialog_boxes[tolerance].text_offset] = 0;
    }

  }

}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////
//draw the global replace menu
void draw_global_replace_menu (SDL_Surface * this_screen)
{
  int x, y, my_pitch;
  char cur_pixel;
  int i,j,k,l;
  char cur_char;
  char str[120];
  Uint8 *screen_buffer;
  screen_buffer = (Uint8 *) this_screen->pixels;
  my_pitch = this_screen->pitch;

  draw_empty_menu (screen, white,x_global_replace_menu,y_global_replace_menu,x_global_replace_menu_lenght,y_global_replace_menu_lenght);
  //draw the window title
  for (y = y_global_replace_menu; y < y_global_replace_menu + 15; y++)
    for (x = x_global_replace_menu; x < x_global_replace_menu + x_global_replace_menu_lenght; x++)
      *(screen_buffer + y * my_pitch + x) = darkblue;

  print_string ("Replace Settings", white, darkblue, x_global_replace_menu + 2,y_global_replace_menu + 2);
  //draw the tolerance string and box
  print_string ("Tolerance:", black, white, x_global_replace_menu + 2,y_global_replace_menu + 20);
  draw_down_button (screen, x_global_replace_menu + 80, y_global_replace_menu + 18, 25, 14);
  print_string (numeric_dialog_boxes[global_tolerance].dialog_text, black, white,x_global_replace_menu + 82, y_global_replace_menu + 20);

  print_string ("Tolerance Mode:", black, white, x_global_replace_menu + 4,y_global_replace_menu + 42);
  //draw the greater tolerance check box
  draw_empty_menu (screen, white, x_global_replace_menu + 40, y_global_replace_menu + 60,14, 14);
  print_string ("+", black, white, x_global_replace_menu + 42 + 14,y_global_replace_menu + 62);
  if(temp_global_tolerance_mode == greater)
  print_string ("X", black, white, x_global_replace_menu + 42,y_global_replace_menu + 62);

  //draw the leaser tolerance check box
  draw_empty_menu (screen, white, x_global_replace_menu + 40, y_global_replace_menu + 80,14, 14);
  print_string ("-", black, white, x_global_replace_menu + 42 + 14,y_global_replace_menu + 82);
  if(temp_global_tolerance_mode == leaser)
  print_string ("X", black, white, x_global_replace_menu + 42,y_global_replace_menu + 82);

  //draw the greater or leaser tolerance check box
  draw_empty_menu (screen, white, x_global_replace_menu + 40, y_global_replace_menu + 100,14, 14);
  print_string ("+/-", black, white, x_global_replace_menu + 42 + 14,y_global_replace_menu + 102);
  if(temp_global_tolerance_mode == greater_or_leaser)
  print_string ("X", black, white, x_global_replace_menu + 42,y_global_replace_menu + 102);

  print_string ("Replace Mode:", black, white, x_global_replace_menu + 4,y_global_replace_menu + 122);

  //draw the greater replace check box
  draw_empty_menu (screen, white, x_global_replace_menu + 40, y_global_replace_menu + 140,14, 14);
  print_string ("+", black, white, x_global_replace_menu + 42 + 14,y_global_replace_menu + 142);
  if(temp_global_tolerance_replace_mode == tolerance_replace_plus)
  print_string ("X", black, white, x_global_replace_menu + 42,y_global_replace_menu + 142);

  //draw the leaser replace check box
  draw_empty_menu (screen, white, x_global_replace_menu + 40, y_global_replace_menu + 160,14, 14);
  print_string ("-", black, white, x_global_replace_menu + 42 + 14,y_global_replace_menu + 162);
  if(temp_global_tolerance_replace_mode == tolerance_replace_minus)
  print_string ("X", black, white, x_global_replace_menu + 42,y_global_replace_menu + 162);

  //draw the equal replace check box
  draw_empty_menu (screen, white, x_global_replace_menu + 40, y_global_replace_menu + 180,14, 14);
  print_string ("=", black, white, x_global_replace_menu + 42 + 14,y_global_replace_menu + 182);
  if(temp_global_tolerance_replace_mode == tolerance_replace_equal)
  print_string ("X", black, white, x_global_replace_menu + 42,y_global_replace_menu + 182);


  print_string ("Replace With:", black, white, x_global_replace_menu + 4,y_global_replace_menu + 202);

  //draw the pattern replace check box
  draw_empty_menu (screen, white, x_global_replace_menu + 40, y_global_replace_menu + 220,14, 14);
  print_string ("Solid", black, white, x_global_replace_menu + 42 + 14,y_global_replace_menu + 222);
  if(temp_global_tolerance_replace_mode_2 == replace_mode_solid)
  print_string ("X", black, white, x_global_replace_menu + 42,y_global_replace_menu + 222);


  //draw the pattern replace check box
  draw_empty_menu (screen, white, x_global_replace_menu + 40, y_global_replace_menu + 240,14, 14);
  print_string ("Pattern", black, white, x_global_replace_menu + 42 + 14,y_global_replace_menu + 242);
  if(temp_global_tolerance_replace_mode_2 == replace_mode_pattern)
  print_string ("X", black, white, x_global_replace_menu + 42,y_global_replace_menu + 242);

  //draw the pattern file name.
  print_string ("Pattern:", black, white, x_global_replace_menu +2,y_global_replace_menu + 262);
  draw_empty_menu (screen, white, x_global_replace_menu + 60, y_global_replace_menu + 260,172, 14);
  j=0;
		while(1)
		{
			if(pattern_file_name[j]==0)break;
			j++;
		}
		i=j;
		if(j>20)
			{
				j-=24;
				k=i-j;
			}
		else
			{
				k=j;
				j=0;
			}
		i=0;
		while(i<k)
		{
			cur_char=pattern_file_name[j];
			*(str+i)=cur_char;
			if(cur_char==0)break;
			j++;
			i++;
		}
		*(str+i)=0;
  if(!current_pattern.object_mem)print_string("None", black, white, x_global_replace_menu +62,y_global_replace_menu + 262);
  else
  print_string(str, black, white, x_global_replace_menu +62,y_global_replace_menu + 262);

  //draw the OK, Cancel and Change pattern buttons
  draw_empty_menu (screen, white, x_global_replace_menu + 30, y_global_replace_menu + 280,20, 14);
  print_string ("Ok", black, white, x_global_replace_menu + 32,y_global_replace_menu + 282);
  draw_empty_menu (screen, white, x_global_replace_menu + 60, y_global_replace_menu + 280,50, 14);
  print_string ("Cancel", black, white, x_global_replace_menu + 62,y_global_replace_menu + 282);
  draw_empty_menu (screen, white, x_global_replace_menu + 120, y_global_replace_menu + 280,110, 14);
  print_string ("Change Pattern", black, white, x_global_replace_menu + 122,y_global_replace_menu + 282);
}


void check_global_replace_menu (char text_input_char)
{
  //right mouse button kills the menu (cancel)
  if (long_pressed_button_r == 1)
    show_global_replace_menu = 0;
  else
    //check the greater than tolerance mode
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_global_replace_menu + 40
	&& x_mouse_pos < x_global_replace_menu + 40 + 14
	&& y_mouse_pos >= y_global_replace_menu + 60
	&& y_mouse_pos < y_global_replace_menu + 60 + 14)
    temp_global_tolerance_mode = greater;
  else
    //check the leaser than tolerance mode
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_global_replace_menu + 40
	&& x_mouse_pos < x_global_replace_menu + 40 + 14
	&& y_mouse_pos >= y_global_replace_menu + 80
	&& y_mouse_pos < y_global_replace_menu + 80 + 14)
    temp_global_tolerance_mode = leaser;
  else
    //check the leaser or greater tolerance mode
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_global_replace_menu + 40
	&& x_mouse_pos < x_global_replace_menu + 40 + 14
	&& y_mouse_pos >= y_global_replace_menu + 100
	&& y_mouse_pos < y_global_replace_menu + 100 + 14)
    temp_global_tolerance_mode = greater_or_leaser;
  else
  //check the greater replace mode
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_global_replace_menu + 40
	&& x_mouse_pos < x_global_replace_menu + 40 + 14
	&& y_mouse_pos >= y_global_replace_menu + 140
	&& y_mouse_pos < y_global_replace_menu + 140 + 14)
    temp_global_tolerance_replace_mode = tolerance_replace_plus;
  else
  //check the leaser replace mode
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_global_replace_menu + 40
	&& x_mouse_pos < x_global_replace_menu + 40 + 14
	&& y_mouse_pos >= y_global_replace_menu + 160
	&& y_mouse_pos < y_global_replace_menu + 160 + 14)
    temp_global_tolerance_replace_mode = tolerance_replace_minus;
  else
  //check the equal replace mode
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_global_replace_menu + 40
	&& x_mouse_pos < x_global_replace_menu + 40 + 14
	&& y_mouse_pos >= y_global_replace_menu + 180
	&& y_mouse_pos < y_global_replace_menu + 180 + 14)
    temp_global_tolerance_replace_mode = tolerance_replace_equal;
  else
  //check the pattern replace_mode_2
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_global_replace_menu + 40
	&& x_mouse_pos < x_global_replace_menu + 40 + 14
	&& y_mouse_pos >= y_global_replace_menu + 220
	&& y_mouse_pos < y_global_replace_menu + 220 + 14)
    temp_global_tolerance_replace_mode_2 = replace_mode_solid;
  else
  //check the pattern replace_mode_2
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_global_replace_menu + 40
	&& x_mouse_pos < x_global_replace_menu + 40 + 14
	&& y_mouse_pos >= y_global_replace_menu + 240
	&& y_mouse_pos < y_global_replace_menu + 240 + 14)
    temp_global_tolerance_replace_mode_2 = replace_mode_pattern;
  else

  //check the cancel button
  if ((long_pressed_button_l == 1 && x_mouse_pos >= x_global_replace_menu + 60
       && x_mouse_pos < x_global_replace_menu + 60 + 50
       && y_mouse_pos >= y_global_replace_menu + 280
       && y_mouse_pos < y_global_replace_menu + 280 + 14)
      || text_input_char == SDLK_ESCAPE)
    show_global_replace_menu = 0;
  else
  //check the load pattern button
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_global_replace_menu + 120
       && x_mouse_pos < x_global_replace_menu + 120 + 110
       && y_mouse_pos >= y_global_replace_menu + 280
       && y_mouse_pos < y_global_replace_menu + 280 + 14)
    {
		SDL_Event event;
		if(current_pattern.object_mem)
			{
				free(current_pattern.object_mem);
				current_pattern.object_mem=0;
			}
		load_object=2;//tell the file open save function to load a pattern
		long_pressed_button_l = 0;
		DoFileOpenSave (0);
    	while (SDL_PollEvent (&event));	//clears all the events
	}

  else
    //check the OK button
  if ((long_pressed_button_l == 1 && x_mouse_pos >= x_global_replace_menu + 30
	 && x_mouse_pos < x_global_replace_menu + 30 + 20
	 && y_mouse_pos >= y_global_replace_menu + 280
	 && y_mouse_pos < y_global_replace_menu + 280 + 14)
	|| text_input_char == SDLK_RETURN)
  {
    int box_tolerance;
    box_tolerance = atoi (numeric_dialog_boxes[global_tolerance].dialog_text);
    //bounds checking
    if (box_tolerance > numeric_dialog_boxes[global_tolerance].max_number)
      box_tolerance = numeric_dialog_boxes[global_tolerance].max_number;
    else if (box_tolerance < numeric_dialog_boxes[global_tolerance].min_number)
      box_tolerance = numeric_dialog_boxes[global_tolerance].min_number;
    global_tolerance_value = box_tolerance;
    global_tolerance_mode = temp_global_tolerance_mode;
    global_tolerance_replace_mode = temp_global_tolerance_replace_mode;
    global_tolerance_replace_mode_2 = temp_global_tolerance_replace_mode_2;
    show_global_replace_menu = 0;
  }
  else
    //now, check to see if we get any character
  if (text_input_char)
  {
    int dialog_text_offset;
    //check to see if it is a numeric char, and if we didn't exceede the max lenght limit
    if (text_input_char >= '0' && text_input_char <= '9' &&
	numeric_dialog_boxes[global_tolerance].text_offset <
	numeric_dialog_boxes[global_tolerance].dialog_lenght)
    {
      dialog_text_offset = numeric_dialog_boxes[global_tolerance].text_offset;
      numeric_dialog_boxes[global_tolerance].dialog_text[dialog_text_offset] =
	text_input_char;
      numeric_dialog_boxes[global_tolerance].dialog_text[dialog_text_offset + 1] = 0;
      numeric_dialog_boxes[global_tolerance].text_offset++;

    }
    else
      if (text_input_char == SDLK_BACKSPACE
	  && numeric_dialog_boxes[global_tolerance].text_offset > 0)
    {
      numeric_dialog_boxes[global_tolerance].text_offset--;
      numeric_dialog_boxes[global_tolerance].
	dialog_text[numeric_dialog_boxes[global_tolerance].text_offset] = 0;
    }

  }

}

/////////////////////////////////////////////////
//draw the object menu
void draw_object_menu (SDL_Surface * this_screen)
{
  int x, y, my_pitch;
  char cur_pixel;
  char str[20];
  Uint8 *screen_buffer;
  screen_buffer = (Uint8 *) this_screen->pixels;
  my_pitch = this_screen->pitch;

  draw_empty_menu (screen, white, x_object_menu, y_object_menu,
		   x_object_menu_lenght, y_object_menu_lenght);
  //draw the window title
  for (y = y_object_menu; y < y_object_menu + 15; y++)
    for (x = x_object_menu; x < x_object_menu + x_object_menu_lenght; x++)
      *(screen_buffer + y * my_pitch + x) = darkblue;
  print_string ("Object Settings", white, darkblue, x_object_menu + 2,y_object_menu + 2);
  //draw the "Mode string"
  print_string ("Put object mode:", black, white, x_object_menu + 4,y_object_menu + 22);
  //draw the put object mode
  draw_empty_menu (screen, white, x_object_menu + 40, y_object_menu + 40,14, 14);
  print_string ("Place over terain", black, white, x_object_menu + 42 + 14,y_object_menu + 42);
  if(object_mode==put_object)
  print_string ("X", black, white, x_object_menu + 42,y_object_menu + 42);

  //draw the increase terrain
  draw_empty_menu (screen, white, x_object_menu + 40, y_object_menu + 60,14, 14);
  print_string ("Increase terrain", black, white, x_object_menu + 42 + 14,y_object_menu + 62);
  if(object_mode==add_object)
  print_string ("X", black, white, x_object_menu + 42,y_object_menu + 62);

  //draw the decrease terrain
  draw_empty_menu (screen, white, x_object_menu + 40, y_object_menu + 80,14, 14);
  print_string ("Decrease terrain", black, white, x_object_menu + 42 + 14,y_object_menu + 82);
  if (object_mode==sub_object)
    print_string ("X", black, white, x_object_menu + 42,y_object_menu + 82);

  //draw the OK and Cancel buttons
  draw_empty_menu (screen, white, x_object_menu + 60, y_object_menu + 100,20, 14);
  print_string ("Ok", black, white, x_object_menu + 62,y_object_menu + 102);
  draw_empty_menu (screen, white, x_object_menu + 90, y_object_menu + 100,50, 14);
  print_string ("Cancel", black, white, x_object_menu + 92,y_object_menu + 102);
}

void check_object_menu (char text_input_char)
{
  //right mouse button kills the menu (cancel)
  if(long_pressed_button_r == 1)
  show_object_menu = 0;
  else
    //check the put mode
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_object_menu + 40
	&& x_mouse_pos < x_object_menu + 40 + 14
	&& y_mouse_pos >= y_object_menu + 40
	&& y_mouse_pos < y_object_menu + 40 + 14)
    object_mode=put_object;
  else
    //check the leaser than mode
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_object_menu + 40
	&& x_mouse_pos < x_object_menu + 40 + 14
	&& y_mouse_pos >= y_object_menu + 60
	&& y_mouse_pos < y_object_menu + 60 + 14)
    object_mode=add_object;
  else
    //check the leaser or greater mode
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_object_menu + 40
	&& x_mouse_pos < x_object_menu + 40 + 14
	&& y_mouse_pos >= y_object_menu + 80
	&& y_mouse_pos < y_object_menu + 80 + 14)
    object_mode=sub_object;

  //check the cancel button
  if ((long_pressed_button_l == 1 && x_mouse_pos >= x_object_menu + 90
       && x_mouse_pos < x_object_menu + 90 + 50
       && y_mouse_pos >= y_object_menu + 100
       && y_mouse_pos < y_object_menu + 100 + 14)
      || text_input_char == SDLK_ESCAPE)
    show_object_menu = 0;
  else
    //check the OK button
  if ((long_pressed_button_l == 1 && x_mouse_pos >= x_object_menu + 60
	 && x_mouse_pos < x_object_menu + 60 + 20
	 && y_mouse_pos >= y_object_menu + 100
	 && y_mouse_pos < y_object_menu + 100 + 14)
	|| text_input_char == SDLK_RETURN)
    show_object_menu = 0;

}

/////////////////////////////////////////////////
//draw the error dialogue box
void
draw_error_box(SDL_Surface * this_screen)
{
  int x, y, my_pitch;
  char cur_pixel;
  char str[20];
  Uint8 *screen_buffer;
  screen_buffer = (Uint8 *) this_screen->pixels;
  my_pitch = this_screen->pitch;

  draw_empty_menu (screen, white, x_error_menu, y_error_menu,
		   x_error_menu_lenght, y_error_menu_lenght);
  //draw the window title
  for (y = y_error_menu; y < y_error_menu + 15; y++)
    for (x = x_error_menu; x < x_error_menu + x_error_menu_lenght; x++)
      *(screen_buffer + y * my_pitch + x) = darkblue;
  print_string ("Error!", white, darkblue, x_error_menu + 2,
		y_error_menu + 2);
  //draw the error strings
  print_string (&error_msg_1, black, white, x_error_menu + 2,
		y_error_menu + 20);

  print_string (&error_msg_2, black, white, x_error_menu + 2,
		y_error_menu + 36);


  //draw the OK button
  draw_empty_menu (screen, white, x_error_menu + 200, y_error_menu + 52,
		   20, 14);
  print_string ("Ok", black, white, x_error_menu + 202,
		y_error_menu + 54);
}

///////////////////////////////////////////////////
void
check_error_menu (char text_input_char)
{
  //right mouse button kills the menu (cancel)
  if (long_pressed_button_r == 1 || text_input_char==SDLK_RETURN || text_input_char==SDLK_ESCAPE)
    view_error_menu = 0;
  else
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_error_menu + 202
	&& x_mouse_pos < x_error_menu + 202 + 14
	&& y_mouse_pos >= y_error_menu + 54
	&& y_mouse_pos < y_error_menu + 54 + 14)
    view_error_menu = 0;
}

/////////////////////////////////////////////////////////////////////////////////
//ok, now the Posix Menus (especially file menus)
#ifndef WINDOWS

draw_file_menu(SDL_Surface * this_screen)
{
  int x, y, my_pitch,i,j,k,l;
  char cur_char;
  char str[120];
  Uint8 *screen_buffer;
  screen_buffer = (Uint8 *) this_screen->pixels;
  my_pitch = this_screen->pitch;

  draw_empty_menu (screen, white, x_file_menu, y_file_menu,x_file_menu_lenght, y_file_menu_lenght);

//print the current directory name
		j=0;
		while(1)
		{
			if(cur_dir[j]==0)break;
			j++;
		}
		i=j;
		if(j>54)
			{
				j-=54;
				k=i-j;
			}
		else
			{
				k=j;
				j=0;
			}
		i=0;
		while(i<k)
		{
			cur_char=cur_dir[j];
			*(str+i)=cur_char;
			if(cur_char==0)break;
			j++;
			i++;
		}
		*(str+i)=0;
print_string (str, black, white, x_file_menu + 2,y_file_menu+2);

  draw_empty_menu (screen, white, x_file_menu+2, y_file_menu+14,x_file_menu_lenght-4, y_file_menu_lenght-35);
  //ok, now, print the files from the current directory...
  if(no_of_files-start_file_offset<18)start_file_offset=no_of_files-18;
  if(start_file_offset<0)start_file_offset=0;
  l=0;
  for(i=start_file_offset;i<start_file_offset+18;i++)
  	{
		j=0;
		k=0;
		//if it is a directory, add a / before
		if(file_names[i].is_directory==1)
			{
				*(str+k)='/';
				k++;
			}
		while(j<55)
		{
			cur_char=file_names[i].file_name[j];
			*(str+k)=cur_char;
			if(cur_char==0)break;
			j++;
			k++;
		}
		*(str+k)=0;
		print_string (str, black, white, x_file_menu + 2,y_file_menu+16+(l*12));
		l++;
	}
print_string ("<<", black, white, x_file_menu + 4,y_file_menu+y_file_menu_lenght-34);
print_string (">>", black, white, x_file_menu + x_file_menu_lenght-20,y_file_menu+y_file_menu_lenght-34);

//draw the "current file" dialogue box
    draw_down_button (screen, x_file_menu + 2,y_file_menu+y_file_menu_lenght-18, x_file_menu_lenght-110, 14);
//print the current selected file name
		j=0;
		while(1)
		{
			if(cur_file_name[j]==0)break;
			j++;
		}
		i=j;
		if(j>44)
			{
				j-=44;
				k=i-j;
			}
		else
			{
				k=j;
				j=0;
			}
		i=0;
		while(i<k)
		{
			cur_char=cur_file_name[j];
			*(str+i)=cur_char;
			if(cur_char==0)break;
			j++;
			i++;
		}
		*(str+i)=0;
print_string (str, black, white, x_file_menu + 4,y_file_menu+y_file_menu_lenght-16);



//draw the load/save button
  draw_empty_menu (screen, white, x_file_menu_lenght+x_file_menu-104, y_file_menu+y_file_menu_lenght-18,35, 14);
  if(!save_file)print_string ("Load", black, white, x_file_menu_lenght+x_file_menu-102,y_file_menu+y_file_menu_lenght-16);
  else print_string ("Save", black, white, x_file_menu_lenght+x_file_menu-102,y_file_menu+y_file_menu_lenght-16);

//draw the cancel button
  draw_empty_menu (screen, white, x_file_menu_lenght+x_file_menu-64, y_file_menu+y_file_menu_lenght-18,50, 14);
  print_string ("Cancel", black, white, x_file_menu_lenght+x_file_menu-62,y_file_menu+y_file_menu_lenght-16);


}
////////////////////////////////////////////////////////////////
//////////////////////

void
check_file_menu (unsigned char text_input_char)
{
  //right mouse button kills the menu (cancel)
  if (long_pressed_button_r == 1)
    view_file_menu = 0;
  else
    //check the load/save button
  if ((long_pressed_button_l == 1 && x_mouse_pos >= x_file_menu_lenght+x_file_menu-104
	 && x_mouse_pos < x_file_menu_lenght+x_file_menu-104 + 35
	 && y_mouse_pos >= y_file_menu+y_file_menu_lenght-18
	 && y_mouse_pos < y_file_menu+y_file_menu_lenght-18 + 14)
	|| text_input_char == SDLK_RETURN)
  {
	if(save_file)SaveFile(&cur_file_name);
	else
	if(load_object)do_load_object(&cur_file_name,&current_object);
	else LoadFile(&cur_file_name);
    view_file_menu = 0;
  }
  else
  //check to see if we selected any file/dir
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_file_menu+2
	 && x_mouse_pos < x_file_menu+x_file_menu_lenght-4
	 && y_mouse_pos >= y_file_menu+14
	 && y_mouse_pos < y_file_menu+y_file_menu_lenght-35)
	 {
		 int i;
		 int j=0;
		 char cur_char;
		 i=((y_mouse_pos-y_file_menu-16)/12)+start_file_offset;

		 //see if it is dir, and, if so, change the current dir
		 if(file_names[i].is_directory)ChangeDir(file_names[i].file_name);
		 else
		while(1)
		 {
		 	cur_char=file_names[i].file_name[j];
		 	*(cur_file_name+j)=cur_char;
		 	if(cur_char==0)break;
		 	j++;
		}

	 }
	 else
	 //check for the cancel button
	   if ((long_pressed_button_l == 1 && x_mouse_pos >= x_file_menu_lenght+x_file_menu-62
	 	 && x_mouse_pos < x_file_menu_lenght+x_file_menu-62 + 50
	 	 && y_mouse_pos >= y_file_menu+y_file_menu_lenght-18
	 	&& y_mouse_pos < y_file_menu+y_file_menu_lenght-18 + 14)
	 	|| text_input_char == SDLK_ESCAPE)view_file_menu=0;
	else
	//check for the << button
	   if (long_pressed_button_l == 1 && x_mouse_pos >= x_file_menu+4
	 	 && x_mouse_pos < x_file_menu + 4 + 14
	 	 && y_mouse_pos >= y_file_menu+y_file_menu_lenght-34
	 	&& y_mouse_pos < y_file_menu+y_file_menu_lenght-34 + 14)start_file_offset-=18;
	else
	//check for the >> button
	   if (long_pressed_button_l == 1 && x_mouse_pos >= x_file_menu+x_file_menu_lenght-20
	 	 && x_mouse_pos < x_file_menu+x_file_menu_lenght-20 + 14
	 	 && y_mouse_pos >= y_file_menu+y_file_menu_lenght-34
	 	&& y_mouse_pos < y_file_menu+y_file_menu_lenght-34 + 14)start_file_offset+=18;
  else
    //now, check to see if we get any character
  if (text_input_char)
  {
    int dialog_text_offset=0;
	while(1)
	{
		if(cur_file_name[dialog_text_offset]==0)break;
		dialog_text_offset++;
	}
    //check to see if it is a numeric char, and if we didn't exceede the max lenght limit
    if (text_input_char == SDLK_BACKSPACE && dialog_text_offset > 0)
	cur_file_name[dialog_text_offset-1]=0;
    else
    if (text_input_char >=32 && text_input_char<128 && dialog_text_offset<119)
    {
    	cur_file_name[dialog_text_offset]=text_input_char;
    	cur_file_name[dialog_text_offset+1]=0;
	}

  }

}



#endif










