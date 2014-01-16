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

#include "display_terrain.h"


void terrain_on_screen (SDL_Surface * this_screen)
{
  Uint8 *screen_buffer;
  Uint8 *height_map = terrain_height;
  int my_pitch = 0;
  int xlenght = 0, ylenght = 0;
  int i = 0, j = 0;
  Uint8 some_char;

  screen_buffer = (Uint8 *) this_screen->pixels;

  if(!terrain_height)return;//memory allocation failed.
  my_pitch = this_screen->pitch;
  if (xoffset < 0)
    xoffset = 0;
  if (yoffset < 0)
    yoffset = 0;

  if (WIDTH * terrain_ratio < window_width)
    x_screen_offset = (window_width - WIDTH * terrain_ratio) / 2;
  else
    x_screen_offset = 0;
  if (HEIGHT * terrain_ratio < window_height)
    y_screen_offset = (window_height - HEIGHT * terrain_ratio) / 2;
  else
    y_screen_offset = 0;
  if (WIDTH * terrain_ratio < window_width)
    xlenght = WIDTH;
  else
    xlenght = window_width / terrain_ratio;
  if (HEIGHT * terrain_ratio < window_height)
    ylenght = HEIGHT;
  else
    ylenght = window_height / terrain_ratio;
  //check to see, in case of a window resize, if we exceeded the map size
  //and, in case we did, change the x/yoffset
  if ((xlenght + xoffset) > WIDTH)
    xoffset = WIDTH - xlenght;
  if ((ylenght + yoffset) > HEIGHT)
    yoffset = HEIGHT - ylenght;


  if (terrain_ratio == 1)	//no rescale needed
  {
    screen_buffer += (y_screen_offset * my_pitch + x_screen_offset);
    height_map += (yoffset * WIDTH + xoffset);
    for (i = 0; i < ylenght; i++)
    {
      for (j = 0; j < xlenght; j++)
      {
		some_char = *(height_map++);
		if (some_char != 0)some_char = some_char / 4;
		else some_char = 255;
		*(screen_buffer++) = some_char;
      }
      screen_buffer += (my_pitch - xlenght);
      height_map += (WIDTH - xlenght);
    }
  }
  else
  {
    int x, y;

    height_map += (yoffset * WIDTH + xoffset);
    for (i = 0; i < ylenght; i++)
    {
      for (j = 0; j < xlenght; j++)
      {
	some_char = *(height_map++);
	if (some_char != 0)
	  some_char = some_char / 4;
	else
	  some_char = 255;
	//now, we need two fors in order to draw a big pixel...
	for (y = 0; y < terrain_ratio; y++)
	  for (x = 0; x < terrain_ratio; x++)
	    *(screen_buffer +
	      (i * my_pitch * terrain_ratio + j * terrain_ratio) +
	      ((y + y_screen_offset) * my_pitch + x + x_screen_offset)) = some_char;

      }
      height_map += (WIDTH - xlenght);
    }
  }



}

void
cls (SDL_Surface * this_screen)
{
  // Defs
  int some_module, my_pitch;
  int map_size;
  int i,j;
  if (x_screen_offset == 0 && y_screen_offset == 0 && terrain_ratio == 1 && terrain_height)
    return;			/*no need to clear the screen,
				  the terrain is all over it anyway */

  my_pitch = this_screen->pitch;

	if(terrain_ratio>1 && x_screen_offset == 0 && y_screen_offset == 0)
	//we need to clear only the right 'frame' and the lower 'frame'
		{
			int *screen_buffer;
			screen_buffer = (int *) this_screen->pixels;
			//clear the right frame
			screen_buffer+=(window_width-16)/4;
			for(i=0;i<window_height;i++)
				{
					for(j=0;j<4;j++) *screen_buffer++=0xffffffff;
					screen_buffer+=(window_width/4)-4;
				}
			//clear the bottom frame
			screen_buffer = (int *) this_screen->pixels;
			screen_buffer+=(window_width*window_height-16*window_width)/4;
			for(i=0;i<window_width*16/4;i++)*screen_buffer++=0xffffffff;

		 	return;
		}

  map_size = window_height * window_width;
  my_pitch = this_screen->pitch;
  //test to see if the map size is divisible by 4. If so, we clear the screen using a Dword
  some_module = map_size % 4;
  if (!some_module)		//yes, it is divisible by 4!
  {
    int *screen_buffer;
    int i;
    screen_buffer = (int *) this_screen->pixels;
    for (i = 0; i < map_size / 4; i++)
      *(screen_buffer + i) = 0xfefefefe;
  }
  else if (some_module = 2)	//yes, it is divisible by 2!
  {
    short *screen_buffer;
    int i;
    screen_buffer = (short *) this_screen->pixels;
    for (i = 0; i < map_size / 2; i++)
      *(screen_buffer + i) = 0xfefe;
  }

}

void
draw_grid (SDL_Surface * this_screen)	//draw the grid
{
  int x_grid_start, y_grid_start, x, y, my_pitch;

  Uint8 *screen_buffer;
  screen_buffer = (Uint8 *) this_screen->pixels;
  my_pitch = this_screen->pitch;

  x_grid_start = x_screen_offset + (grid - xoffset % grid) * terrain_ratio;
  y_grid_start = y_screen_offset + (grid - yoffset % grid) * terrain_ratio;
  //draw x grid (|)
  for (x = x_grid_start; x < window_width - x_screen_offset;
       x += grid * terrain_ratio)
    for (y = y_screen_offset; y < window_height - y_screen_offset; y++)
      *(screen_buffer + my_pitch * y + x) = 255;
  //draw y grid (-)
  for (y = y_grid_start; y < window_height - y_screen_offset;
       y += grid * terrain_ratio)
    for (x = x_screen_offset; x < window_width - x_screen_offset; x++)
      *(screen_buffer + my_pitch * y + x) = 255;
}

//draws the select area (in fact, the lines)
void draw_selection(SDL_Surface * this_screen)
{
	char str[800];//debug
  int line_1_x,line_1_y,line_2_x,line_2_y;
  int hor_line_len,ver_line_len;
  int s_selection_x_1,s_selection_x_2,s_selection_y_1,s_selection_y_2;
  int x, y, my_pitch;

  Uint8 *screen_buffer;
  screen_buffer = (Uint8 *) this_screen->pixels;
  my_pitch = this_screen->pitch;
  if(selection_x_2==-1 && selection_y_2==-1)return;//no selection to draw
  //ok now, put in s_selection_x_1,s_selection_y_1 the upper left corner of the selection
  if(selection_x_1<selection_x_2)
  	{
  		s_selection_x_1=selection_x_1;
  		s_selection_x_2=selection_x_2;
	}
  else
  	{
  		s_selection_x_1=selection_x_2;
  		s_selection_x_2=selection_x_1;
	}

  if(selection_y_1<selection_y_2)
  	{
  		s_selection_y_1=selection_y_1;
  		s_selection_y_2=selection_y_2;
	}
  else
  	{
  		s_selection_y_1=selection_y_2;
  		s_selection_y_2=selection_y_1;
	}
//ok, now let's try to get the SCREEN coordinates of this shit.
line_1_x=(s_selection_x_1-xoffset+x_screen_offset)*terrain_ratio;
line_1_y=(s_selection_y_1-yoffset+y_screen_offset)*terrain_ratio;
line_2_x=(s_selection_x_2-xoffset+x_screen_offset)*terrain_ratio;
line_2_y=(s_selection_y_2-yoffset+y_screen_offset)*terrain_ratio;

hor_line_len=line_2_x-line_1_x;
ver_line_len=line_2_y-line_1_y;

//now, test the lenght of the lines (and adjust them, if neccesary)
if(line_1_x+hor_line_len>window_width)hor_line_len=window_width-line_1_x;
if(line_1_y+ver_line_len>window_height)ver_line_len=window_height-line_1_y;

//
if(line_1_y<0)
{
	ver_line_len+=line_1_y;
	line_1_y=0;
}
if(line_1_x<0)
{
	hor_line_len+=line_1_x;
	line_1_x=0;
}



if(line_1_y>0 && line_1_y<=window_height)
for (x=line_1_x; x<line_1_x+hor_line_len; x+=2)*(screen_buffer + my_pitch * line_1_y + x) = black;
if(line_2_y>0 && line_2_y<=window_height)
for (x=line_1_x; x<line_1_x+hor_line_len; x+=2)*(screen_buffer + my_pitch * line_2_y + x) = black;

if(line_1_x>0 && line_1_x<=window_width)
for (y=line_1_y; y<line_1_y+ver_line_len; y+=2)*(screen_buffer + my_pitch * y + line_1_x) = black;
if(line_2_x>0 && line_2_x<=window_width)
for (y=line_1_y; y<line_1_y+ver_line_len; y+=2)*(screen_buffer + my_pitch * y + line_2_x) = black;

}

void debug_info ()
{
  char str[80];
  sprintf (str, "1021%4= %d", sizeof(str));
  print_string (str, black, white, 1, window_height - 156);

}

void put_right_cursor()
{
	bool mouse_shape_arrow=0;
	if(current_cursor==cursor_wait)return;

	if(show_new_terrain_menu || show_generate_terrain_menu || show_view_menu
	|| show_replace_menu || show_rotate_menu || show_object_menu || show_global_replace_menu || view_error_menu || isometric_terrain)
		if(current_cursor!=cursor_arrow)
		{
			change_cursor(cursor_arrow);
			return;
		}
		else return;

	#ifndef WINDOWS
	  if (view_file_menu)
	  if(current_cursor!=cursor_arrow)
	 	 {
	 		change_cursor(cursor_arrow);
	 		return;
		 }
		 else return;
	#endif

	//now, check and see if the mouse is over the toolbar, minimap, or status bar,
	//and, if it is, the cursor's shape is arrow.
  if(last_click_on!=click_terrain || (last_click_on==click_terrain && long_pressed_button_l==0))
  	{
	  if(status_bar)if(x_mouse_pos < status_bar_x || x_mouse_pos > (status_bar_x + status_bar_x_lenght)
	      || y_mouse_pos < status_bar_y || y_mouse_pos > (status_bar_y + status_bar_y_lenght))
	      mouse_shape_arrow=0;
	      else
	      		if(current_cursor!=cursor_arrow)
		  		{
		  			change_cursor_show(cursor_arrow);
		  			return;
		  		}
				else return;
	if(mini_map)if(x_mouse_pos > min_map_x && x_mouse_pos < (min_map_x + 255) && y_mouse_pos > min_map_y && y_mouse_pos < (min_map_y + 255))
		       if(current_cursor!=cursor_arrow)
		  		{
		  			change_cursor_show(cursor_arrow);
		  			return;
		  		}
				else return;
    if(tool_bar)if(x_mouse_pos >= tool_bar_x && x_mouse_pos <= tool_bar_x + tool_bar_x_lenght
	&& y_mouse_pos >= tool_bar_y && y_mouse_pos <= tool_bar_y + tool_bar_y_lenght)
			    if(current_cursor!=cursor_arrow)
			  	 {
			  		change_cursor_show(cursor_arrow);
			  		return;
			  	 }
				 else return;
	}

  if(!caps_look_on)
  {
	if(current_tool==t_place && current_cursor!=cursor_put)change_cursor_show(cursor_put);
	else
	if(current_tool==t_escavate && current_cursor!=cursor_dig)change_cursor_show(cursor_dig);
	else
	if(current_tool==t_elevate && current_cursor!=cursor_elevate)change_cursor_show(cursor_elevate);
	else
	if(current_tool==t_peek && current_cursor!=cursor_peek)change_cursor_show(cursor_peek);
	else
	if(current_tool==t_replace && current_cursor!=cursor_replace)change_cursor_show(cursor_replace);
	else
	if(current_tool==t_flood && current_cursor!=cursor_flood)change_cursor_show(cursor_flood);
	else
	if(current_tool==t_zoom_in && current_cursor!=cursor_zoom)change_cursor_show(cursor_zoom);
	else
	if(current_tool==t_select && current_cursor!=cursor_select)change_cursor_show(cursor_select);
	else
	if(current_tool==t_object && current_cursor!=cursor_null)change_cursor_show(cursor_null);
	else
	if(current_tool==t_global_replace && current_cursor!=cursor_global_replace)change_cursor_show(cursor_global_replace);

  }
  else
  //draw the target cursor
  if(current_cursor!=cursor_target)change_cursor_show(cursor_target);
}


Uint32
on_screen (unsigned int some_int)	//build the 'scene'
{
	put_right_cursor();
	check_toolbar_mouse_over();
	if(no_update_now)
	{
		no_update_now=0;
		return some_int;
	}

  if(isometric_terrain)draw_isometric_terrain(screen);
  else
  	{
	  cls (screen);
  	  terrain_on_screen(screen);
  	  draw_selection(screen);
	//  debug_info();
	  if (current_tool == t_object && current_cursor!=cursor_arrow)draw_object_on_screen(screen);
	  if (grid)draw_grid (screen);
	  if (status_bar)draw_status_bar ();
   	  if (mini_map)draw_minimap (screen);
	  if (tool_bar)draw_tool_bar (screen);
	  if (show_tip)draw_tool_tip();
	  if (show_new_terrain_menu)draw_new_terrain_menu (screen);
	  if (show_generate_terrain_menu)draw_generate_menu (screen);
	  if (show_view_menu)draw_view_menu (screen);
	  if (show_object_menu)draw_object_menu(screen);
	  if (show_replace_menu)draw_replace_menu (screen);
	  if (show_global_replace_menu)draw_global_replace_menu (screen);
	  if (show_rotate_menu)draw_rotate_menu(screen);
	  if (view_error_menu)draw_error_box(screen);
	#ifndef WINDOWS
	  if (view_file_menu)draw_file_menu(screen);
	#endif
	}

  SDL_UpdateRect (screen, 0, 0, 0, 0);	//blit
  return some_int;
}
