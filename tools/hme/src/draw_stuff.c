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

#include "draw_stuff.h"

void
draw_frame (SDL_Surface * this_screen, int xmenu, int ymenu, int xlen,
	    int ylen)
{
  int x, y, my_pitch;
  Uint8 *screen_buffer;
  screen_buffer = (Uint8 *) this_screen->pixels;
  my_pitch = this_screen->pitch;

  for (x = xmenu; x < xmenu + xlen; x++)
    *(screen_buffer + my_pitch * ymenu + x) = gray;
  for (y = ymenu; y < ymenu + ylen; y++)
    *(screen_buffer + my_pitch * y + xmenu) = gray;
  for (x = xmenu; x < xmenu + xlen; x++)
    *(screen_buffer + my_pitch * (ymenu + ylen) + x) = black;
  for (y = ymenu; y < ymenu + ylen; y++)
    *(screen_buffer + my_pitch * y + xmenu + xlen) = black;

}

void
draw_down_button (SDL_Surface * this_screen, int xmenu, int ymenu, int xlen,
		  int ylen)
{
  int x, y, my_pitch;
  Uint8 *screen_buffer;
  screen_buffer = (Uint8 *) this_screen->pixels;
  my_pitch = this_screen->pitch;

  for (x = xmenu; x < xmenu + xlen; x++)
    *(screen_buffer + my_pitch * ymenu + x) = dark_steel_blue;
  for (x = xmenu; x < xmenu + xlen; x++)
    *(screen_buffer + my_pitch * (ymenu + 1) + x) = dark_steel_blue;
  for (x = xmenu; x < xmenu + xlen; x++)
    *(screen_buffer + my_pitch * (ymenu + ylen) + x) = light_steel_blue;
  for (x = xmenu + 1; x < xmenu + xlen + 1; x++)
    *(screen_buffer + my_pitch * (ymenu + ylen + 1) + x) = light_steel_blue;

  for (y = ymenu; y < ymenu + ylen; y++)
    *(screen_buffer + my_pitch * y + xmenu) = dark_steel_blue;
  for (y = ymenu + 1; y < ymenu + ylen + 1; y++)
    *(screen_buffer + my_pitch * y + xmenu + 1) = dark_steel_blue;
  for (y = ymenu; y < ymenu + ylen; y++)
    *(screen_buffer + my_pitch * y + xmenu + xlen) = light_steel_blue;
  for (y = ymenu + 1; y < ymenu + ylen + 1; y++)
    *(screen_buffer + my_pitch * y + xmenu + xlen + 1) = light_steel_blue;
}

void
draw_up_button (SDL_Surface * this_screen, int xmenu, int ymenu, int xlen,
		int ylen)
{
  int x, y, my_pitch;
  Uint8 *screen_buffer;
  screen_buffer = (Uint8 *) this_screen->pixels;
  my_pitch = this_screen->pitch;

  for (x = xmenu; x < xmenu + xlen; x++)
    *(screen_buffer + my_pitch * ymenu + x) = light_steel_blue;
  for (x = xmenu; x < xmenu + xlen; x++)
    *(screen_buffer + my_pitch * (ymenu + 1) + x) = light_steel_blue;
  for (x = xmenu; x < xmenu + xlen; x++)
    *(screen_buffer + my_pitch * (ymenu + ylen) + x) = dark_steel_blue;
  for (x = xmenu + 1; x < xmenu + xlen + 1; x++)
    *(screen_buffer + my_pitch * (ymenu + ylen + 1) + x) = dark_steel_blue;

  for (y = ymenu; y < ymenu + ylen; y++)
    *(screen_buffer + my_pitch * y + xmenu) = light_steel_blue;
  for (y = ymenu + 1; y < ymenu + ylen + 1; y++)
    *(screen_buffer + my_pitch * y + xmenu + 1) = light_steel_blue;
  for (y = ymenu; y < ymenu + ylen; y++)
    *(screen_buffer + my_pitch * y + xmenu + xlen) = dark_steel_blue;
  for (y = ymenu + 1; y < ymenu + ylen + 1; y++)
    *(screen_buffer + my_pitch * y + xmenu + xlen + 1) = dark_steel_blue;
}


void draw_empty_menu (SDL_Surface * this_screen, char color, int xmenu, int ymenu,
		 int xlen, int ylen)
{
  int x, y, my_pitch;
  char cur_pixel;
  Uint8 *screen_buffer;
  screen_buffer = (Uint8 *) this_screen->pixels;
  my_pitch = this_screen->pitch;
  screen_buffer += ymenu * my_pitch + xmenu;

  //draw the main menu (without borders)
  for (y = ymenu; y < ymenu + ylen; y++)
  {
    for (x = xmenu; x < xmenu + xlen; x++)
      *(screen_buffer++) = color;
    screen_buffer += (my_pitch - xlen);
  }

  draw_frame (screen, xmenu, ymenu, xlen, ylen);
}


void draw_tool_bar_big_icon (SDL_Surface * this_screen, int mode, int icon_no,
			int icon_x_screen, int icon_y_screen)
{
  int x, y, my_pitch;
  char cur_pixel;
  Uint8 *screen_buffer;
  screen_buffer = (Uint8 *) this_screen->pixels;
  my_pitch = this_screen->pitch;
  screen_buffer += icon_y_screen * my_pitch + icon_x_screen;


  for (y = y_tool_bar_bmp - 1; y != 15; y--)
  {
    Uint8 cur_color;
    for (x = icon_no * 32; x < icon_no * 32 + 32; x++)
    {
      cur_color = *(tool_bar_mem + x_tool_bar_bmp * y + x);
      if (cur_color == 131 || cur_color == 130)
	if (mode == mode_pushed)
	  cur_color = light_steel_blue;
	else if (mode == mode_not_pushed)
	  cur_color = steel_blue;
      *(++screen_buffer) = cur_color;
    }
    screen_buffer += my_pitch - 32;
  }

}

void draw_tool_bar_small_icon (SDL_Surface * this_screen, int mode, int icon_no,
			  int icon_x_screen, int icon_y_screen)
{
  int x, y, my_pitch;
  char cur_pixel;
  Uint8 *screen_buffer;
  screen_buffer = (Uint8 *) this_screen->pixels;
  my_pitch = this_screen->pitch;
  screen_buffer += icon_y_screen * my_pitch + icon_x_screen;


  for (y = 15; y != -1; y--)
  {
    Uint8 cur_color;
    for (x = icon_no * 16; x < icon_no * 16 + 16; x++)
    {
      cur_color = *(tool_bar_mem + x_tool_bar_bmp * y + x);
      if (cur_color == 131 || cur_color == 130)
	if (mode == mode_pushed)
	  cur_color = light_steel_blue;
	else if (mode == mode_not_pushed)
	  cur_color = steel_blue;
      *(++screen_buffer) = cur_color;
    }
    screen_buffer += my_pitch - 16;
  }

}

void draw_tool_bar (SDL_Surface * this_screen)
{
  int i, my_pitch;
  char str[20];
  int x, y;
  Uint8 *screen_buffer;
  screen_buffer = (Uint8 *) this_screen->pixels;
  my_pitch = this_screen->pitch;

  //check to see if we didn't drag the tool bar outside of the screen
  if (tool_bar_x < 0)
    tool_bar_x = 0;
  else if ((tool_bar_x + tool_bar_x_lenght + 1) > window_width)
    tool_bar_x = window_width - tool_bar_x_lenght - 1;
  if (tool_bar_y < 0)
    tool_bar_y = 0;
  else if ((tool_bar_y + tool_bar_y_lenght + 1) > window_height)
    tool_bar_y = window_height - tool_bar_y_lenght - 1;


  draw_empty_menu (screen, steel_blue, tool_bar_x, tool_bar_y,
		   tool_bar_x_lenght, tool_bar_y_lenght);
  //now, draw the icons
  for (i = 0; i < no_of_main_tool_bar_icons; i++)
  {

    if (main_tool_bar[i].icon_active == 1
	|| main_tool_bar[i].icon_pressed == 1)
    {
      draw_tool_bar_big_icon (screen, mode_pushed, main_tool_bar[i].icon_id,
			      tool_bar_x + (i * 36) + 3, tool_bar_y + 3);
      draw_down_button (screen, tool_bar_x + (i * 36) + 2, tool_bar_y + 2, 33,
			33);
    }

    else if (!main_tool_bar[i].icon_dont_stay_pressed
	     || main_tool_bar[i].icon_mouse_over)
    {
      draw_tool_bar_big_icon (screen, mode_not_pushed,
			      main_tool_bar[i].icon_id,
			      tool_bar_x + (i * 36) + 3, tool_bar_y + 3);
      draw_up_button (screen, tool_bar_x + (i * 36) + 2, tool_bar_y + 2, 33,
		      33);
    }

    else if (main_tool_bar[i].icon_dont_stay_pressed)
    {
      draw_tool_bar_big_icon (screen, mode_not_pushed,
			      main_tool_bar[i].icon_id,
			      tool_bar_x + (i * 36) + 3, tool_bar_y + 3);
    }

  }
///////////////////////////////////////////////////////
//now, draw the small icons
  for (i = 0; i < no_of_small_tool_bar_icons; i++)
  {

    if (small_tool_bar[i].icon_active == 1
	|| small_tool_bar[i].icon_pressed == 1)
    {
      draw_tool_bar_small_icon (screen, mode_pushed,
				small_tool_bar[i].icon_id,
				tool_bar_x + (i * 20) + 3,
				tool_bar_y + 3 + 38);
      draw_down_button (screen, tool_bar_x + (i * 20) + 2,
			tool_bar_y + 2 + 38, 17, 17);
    }

    else if (!small_tool_bar[i].icon_dont_stay_pressed
	     || small_tool_bar[i].icon_mouse_over)
    {
      draw_tool_bar_small_icon (screen, mode_not_pushed,
				small_tool_bar[i].icon_id,
				tool_bar_x + (i * 20) + 3,
				tool_bar_y + 3 + 38);
      draw_up_button (screen, tool_bar_x + (i * 20) + 2, tool_bar_y + 2 + 38,
		      17, 17);
    }

    else if (small_tool_bar[i].icon_dont_stay_pressed)
    {
      draw_tool_bar_small_icon (screen, mode_not_pushed,
				small_tool_bar[i].icon_id,
				tool_bar_x + (i * 20) + 3,
				tool_bar_y + 3 + 38);
    }

  }

/////////////////////////////////////////////////////////
// draw the heights bar

  i = 0;
  for (x = tool_bar_x + no_of_small_tool_bar_icons * 20 + 4;
       x < tool_bar_x + no_of_small_tool_bar_icons * 20 + 4 + 256; x++)
  {
    for (y = tool_bar_y + 2 + 40; y < tool_bar_y + 2 + 40 + 14; y++)
      *(screen_buffer + y * my_pitch + x) = i / 4;
    i++;
  }
//draw the current color pointer
  x = tool_bar_x + no_of_small_tool_bar_icons * 20 + 4 + color_1;
  y = tool_bar_y + 2 + 40 + 6;
  *(screen_buffer + y * my_pitch + x) = red;
  *(screen_buffer + y * my_pitch + x + 1) = red;
  *(screen_buffer + (y + 1) * my_pitch + x) = red;
  *(screen_buffer + (y + 1) * my_pitch + x + 1) = red;
  draw_frame (screen, tool_bar_x + no_of_small_tool_bar_icons * 20 + 4,
	      tool_bar_y + 2 + 40, 256, 14);

//now, print the current color
  draw_empty_menu (screen, white,
		   tool_bar_x + no_of_small_tool_bar_icons * 20 + 4 + 256 + 4,
		   tool_bar_y + 2 + 40, 25, 14);

  sprintf (str, "%d", color_1);
  print_string (str, black, white,
		tool_bar_x + no_of_small_tool_bar_icons * 20 + 4 + 256 + 4 +
		2, tool_bar_y + 2 + 40 + 2);

}



void draw_status_bar ()
{
  char str[80];
  int cur_z;

  //check to see if we didn't drag the status bar outside of the screen
  if (status_bar_x < 0)
    status_bar_x = 0;
  else if ((status_bar_x + status_bar_x_lenght + 1) > window_width)
    status_bar_x = window_width - status_bar_x_lenght - 1;
  if (status_bar_y < 0)
    status_bar_y = 0;
  else if ((status_bar_y + status_bar_y_lenght + 1) > window_height)
    status_bar_y = window_height - status_bar_y_lenght - 1;

  if (!get_cur_x_y ())
    return;
  cur_z = *(terrain_height + cur_y * WIDTH + cur_x);	//get the deepth
  draw_empty_menu (screen, white, status_bar_x, status_bar_y,
		   status_bar_x_lenght, status_bar_y_lenght);
  sprintf (str, "XSize: %d, YSize: %d, Map scale: %d/1, X: %d, Y: %d Z: %d",
	   WIDTH, HEIGHT, terrain_ratio, cur_x, cur_y, cur_z);
  print_string (str, black, white, status_bar_x + 2, status_bar_y + 3);

}

void draw_tool_tip()
{
  tip_x_lenght=7*strlen(tip_text)+6;
  //check to see if we didn't drag the tip outside of the screen
  if (tip_x < 0)tip_x = 0;
  else if ((tip_x + tip_x_lenght+1) > window_width)tip_x =window_width - tip_x_lenght - 1;
  if (tip_y < 0)tip_y = 0;
  else if ((tip_y + tip_y_lenght + 1) > window_height)tip_y =window_height - tip_y_lenght - 1;
  draw_empty_menu (screen, white, tip_x, tip_y,tip_x_lenght, tip_y_lenght);
  print_string (tip_text, black, white, tip_x + 2, tip_y + 3);

}


void draw_minimap (SDL_Surface * this_screen)
{
  int my_pitch;
  float x, y, x_ratio, y_ratio;
  Uint8 cur_pixel;
  Uint8 *screen_buffer;
  Uint8 *height_map = terrain_height;
  int min_map_pos_x, min_map_pos_y, min_map_x_pos_lenght,
    min_map_y_pos_lenght;

  screen_buffer = (Uint8 *) this_screen->pixels;
  my_pitch = this_screen->pitch;
  if(!terrain_height)return;//no terrain

  //check to see if we didn't drag the minimap outside of the screen
  if (min_map_x < 0)
    min_map_x = 0;
  else if ((min_map_x + 256) > window_width)
    min_map_x = window_width - 256;
  if (min_map_y < 0)
    min_map_y = 0;
  else if ((min_map_y + 256) > window_height)
    min_map_y = window_height - 256;

  screen_buffer += min_map_y * my_pitch + min_map_x;
  x_ratio = (float) WIDTH / (float) 256;
  y_ratio = (float) HEIGHT / (float) 256;
  for (y = 0; y < 256; y++)
  {
    for (x = 0; x < 256; x++)
    {
      cur_pixel =
	*(height_map + (int) (WIDTH * (int) (y * y_ratio) + (x * x_ratio)));
      if (cur_pixel)
	cur_pixel = cur_pixel / 4;
      else
	cur_pixel = 255;	//black
      *(screen_buffer++) = cur_pixel;
    }
    screen_buffer += my_pitch - 256;
  }
  //now, let's draw the rectangle that shows us where exactly we are


  min_map_pos_x = (int) (xoffset / x_ratio + min_map_x);
  min_map_pos_y = (int) (yoffset / y_ratio + min_map_y);
  min_map_x_pos_lenght = (int) (window_width / (x_ratio * terrain_ratio) - 1);
  min_map_y_pos_lenght =
    (int) (window_height / (y_ratio * terrain_ratio) - 1);

  //take care not to exceede the minmap limits, for smaller maps
  if (min_map_x_pos_lenght > 255)
    min_map_x_pos_lenght = 255;
  if (min_map_y_pos_lenght > 255)
    min_map_y_pos_lenght = 255;
  draw_frame (screen, min_map_pos_x, min_map_pos_y, min_map_x_pos_lenght,
	      min_map_y_pos_lenght);

  //now, draw the minimap frame
  draw_frame (screen, min_map_x, min_map_y, 255, 255);
}
