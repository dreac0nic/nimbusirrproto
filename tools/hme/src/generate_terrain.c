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


/*******************************************************
 * Parts of this code are stolen and modified from sdlplasma,
 * by Stefan Hellkvist, stefan@hellkvist.org
 * Copyright: see GPL
 *******************************************************/
#include "generate_terrain.h"

__inline int
getPixel (int x, int y)
{
  return *(terrain_height + (y * WIDTH + x));
}

__inline void
putPixel (int x, int y, Uint8 color)
{
  *(terrain_height + (y * WIDTH + x)) = color;
}


__inline int mrandom (int max)
{
  return (int) ((float) max * rand () / (RAND_MAX + 120.0));
}

__inline int getNewColor (int c1, int c2, int dist)
{
  unsigned int this_height;
  unsigned int random_displacement;
  random_displacement = (mrandom (dist) - dist / 2);


  this_height = (c1 + c2 + random_displacement);
  if (this_height < 512)
    this_height = this_height / 2;
  else
    this_height = this_height / 3;
  return this_height;
}

__inline int
getNewColor4 (int c1, int c2, int c3, int c4, int dist)
{
  unsigned int this_height;
  unsigned int random_displacement;
  random_displacement = (mrandom (dist) - dist / 2);

  this_height = (c1 + c2 + c3 + c4 + random_displacement);
  if (this_height < 1024)
    this_height = this_height / 4;
  else
    this_height = this_height / 5;
  return this_height;

}

// NON INLINE

void drawSeed (int width, int height)
{
  putPixel (0, 0, mrandom (255));
  putPixel (width, 0, mrandom (255));
  putPixel (width, height, mrandom (255));
  putPixel (0, height, mrandom (255));
}

void drawSeed_no_overwrite (int width, int height)
{
  if(!getPixel(0,0))putPixel(0,0,mrandom(255));
  if(!getPixel(width,0))putPixel(width,0,mrandom(255));
  if(!getPixel(width,height))putPixel(width,height,mrandom(255));
  if(!getPixel(0,height))putPixel(0,height,mrandom(255));
}

void drawMap (int x1, int y1, int x2, int y2)
{
  int midx = (x1 + x2) / 2;
  int midy = (y1 + y2) / 2;

  if (!getPixel (midx, y1))
    putPixel (midx, y1,getNewColor (getPixel (x1, y1), getPixel (x2, y1), x2 - x1));
  if (!getPixel (x2, midy))
    putPixel (x2, midy,getNewColor (getPixel (x2, y1), getPixel (x2, y2), y2 - y1));
  if (!getPixel (midx, y2))
    putPixel (midx, y2,getNewColor (getPixel (x1, y2), getPixel (x2, y2), x2 - x1));
  if (!getPixel (x1, midy))
    putPixel (x1, midy,getNewColor (getPixel (x1, y1), getPixel (x1, y2), y2 - y1));
  if (!getPixel (midx, midy))
    putPixel (midx, midy,
	      getNewColor4 (getPixel (x1, midy), getPixel (x2, midy),
			    getPixel (midx, y1), getPixel (midx, y2),
			    y2 - y1));

  if (x2 > x1 + 1 || y2 > y1 + 1)
  {
    drawMap (x1, y1, midx, midy);
    drawMap (midx, y1, x2, midy);
    drawMap (midx, midy, x2, y2);
    drawMap (x1, midy, midx, y2);
  }
}


int overdraw_terrain()
{
  int map_size=WIDTH*HEIGHT;
  int i;
  if(!terrain_height)return;//we don't have a terrain
  change_cursor(cursor_wait);
  for (i = 0; i <map_size; i++)*(terrain_height + i)=0;
  drawSeed (WIDTH - 1, HEIGHT - 1);
  drawMap (0, 0, WIDTH - 1, HEIGHT - 1);
  change_cursor(last_cursor);
  return 1;
}

int
make_terrain ()
{
  int map_size=WIDTH*HEIGHT;
  if(!terrain_height)return;//we don't have a terrain
  change_cursor(cursor_wait);
  drawSeed_no_overwrite(WIDTH - 1, HEIGHT - 1);
  drawMap (0, 0, WIDTH - 1, HEIGHT - 1);
  change_cursor(last_cursor);
  return 1;
}

void clear_mem()
{
  if (terrain_height)free(terrain_height);
  terrain_height=0;
  if (temp_buffer)free(temp_buffer);
  temp_buffer=0;
  if (undo_buffer)free(undo_buffer);
  undo_buffer=0;

}

void allocate_mem()
{
  int i;
  int map_size=WIDTH*HEIGHT;
  clear_mem();
  undo=no_undo;//we can't undo, right now.
  clear_temp_buffer=0;//needed, otherwise it might crash next time you draw something
  terrain_height = calloc ( WIDTH * HEIGHT, sizeof(Uint8));
  temp_buffer = calloc ( WIDTH * HEIGHT, sizeof(Uint8));
  undo_buffer = calloc ( WIDTH * HEIGHT, sizeof(Uint8));
  if(!terrain_height || !temp_buffer || !undo_buffer)
    {
  		sprintf(error_msg_1,"Not enough memory for the height map!");
  		sprintf(error_msg_2,"Please use a smaller map size!");
  		view_error_menu=1;
  		clear_mem();
  		return;
  	}
  //clear the buffer
  for (i = 0; i <map_size; i++)*(terrain_height + i)=0;
}
