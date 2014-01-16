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
#include <math.h>
#include "isometric.h"


//this function is a quick hack, and it also have some debugging things in it, so forgive my
//coding style here, it should eb fixed and improved in later versions

void generate_isometric_terrain()
{
  Uint8 *isometric_pointer;
  Uint8 *height_map = terrain_height;
  int xlenght = 0, ylenght = 0;
  int i, j, k=0;
  int xr,yr;//x and y rotated
  Uint8 some_char;
  int top_height;
  int drawing_area_start=0;
  float x_start,x_step,x_end,y_start,y_step,y_end,x,y;

  isometric_window_buffer=(Uint8 *)calloc ( window_width * window_height, sizeof(Uint8));
  isometric_pointer = isometric_window_buffer;
  //clear the window (CLS)
  for(i=0;i<window_width * window_height;i++)*(isometric_pointer+i)=black;

  if(!terrain_height)return;//memory allocation failed.
  if (xoffset < 0)
    xoffset = 0;
  if (yoffset < 0)
    yoffset = 0;

  if (WIDTH < window_width)
    x_screen_offset = (window_width - WIDTH) / 2;
  else
    x_screen_offset = 0;
  if (HEIGHT < window_height)
    y_screen_offset = (window_height - HEIGHT) / 2;
  else
    y_screen_offset = 0;
  if (WIDTH  < window_width)
    xlenght = WIDTH;
  else
    xlenght = window_width;
  if (HEIGHT < window_height)
    ylenght = HEIGHT;
  else
    ylenght = window_height;

/*
//very debug
y_start=0;
y_step=1.0f;

x_start=0;
x_step=1.0f;
*/


    drawing_area_start = (y_screen_offset * window_width + x_screen_offset);
    height_map += (yoffset * WIDTH + xoffset);
//    y=y_start;
    for (y = 0; y < ylenght; y++)
    {
//		y+=y_step;
//		x=x_start;
      for (x = 0; x < xlenght; x++)
      {
//		 x+=x_step;
		some_char = *(height_map++);

		top_height=y_screen_offset+y;
		if(some_char<top_height)top_height=some_char;

		if (some_char != 0)some_char = some_char / 4;
		else some_char = 255;

		isometric_pointer=isometric_window_buffer+drawing_area_start+(int)(y*window_width+x);
		for(k=0;k<=top_height;k++)*(isometric_pointer-k*window_width) = some_char;

      }

      height_map += (WIDTH - xlenght);
    }

}

void draw_isometric_terrain(SDL_Surface * this_screen)
{
  int x, y, my_pitch;
  Uint8 *screen_buffer;
  Uint8 *isometric_pointer;


  screen_buffer = (Uint8 *) this_screen->pixels;
  my_pitch = this_screen->pitch;

  if(kill_isometric_buffer_semaphore)
  	{
		if(isometric_window_buffer)free(isometric_window_buffer);
      	isometric_window_buffer=NULL;
  		kill_isometric_buffer_semaphore=0;
	}

  	if(!isometric_window_buffer)generate_isometric_terrain(screen);
  	isometric_pointer = isometric_window_buffer;


  for(y=0;y<window_height;y++)
  	{
		for(x=0;x<window_width;x++)*(screen_buffer++)=*(isometric_pointer++);
		screen_buffer+=my_pitch-window_width;
	}

  if(kill_isometric_buffer_semaphore)
  	{
		if(isometric_window_buffer)free(isometric_window_buffer);
      	isometric_window_buffer=NULL;
  		kill_isometric_buffer_semaphore=0;
	}

}

