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

#include "font.h"
#include <stdlib.h>

void
load_font ()
{
  int f_size;
  FILE *f = NULL;
  f = fopen ("font.bmp", "rb");
  fseek (f, 0, SEEK_END);
  f_size = ftell (f);
//ok, allocate memory for it
  font_mem = calloc ( f_size, sizeof(char) );
  handle_font_mem=font_mem;
  fseek (f, 0, SEEK_SET);
  fread (font_mem, 1, f_size, f);
  fclose (f);

  font_mem += 18;		//x lenght is at offset+18
  x_font_bmp = *((int *) font_mem);
  font_mem += 4;		//y lenght is at offset+22
  y_font_bmp = *((int *) font_mem);
  font_mem += 46 - 22;		//y lenght is at offset+22
  font_colors_no = *((int *) font_mem);
  font_mem += 54 - 46 + font_colors_no * 4;

}

void
draw_char (SDL_Surface * this_screen, Uint8 my_char, char font_color,
	   char background_color, int char_xscreen, int char_yscreen)
{

  int x, y, my_pitch;
  char cur_pixel;
  Uint8 *screen_buffer;
  screen_buffer = (Uint8 *) this_screen->pixels;
  my_pitch = this_screen->pitch;
  screen_buffer += char_yscreen * my_pitch + char_xscreen;
  my_char -= 32;

  for (y = y_font_bmp - 1; y != -1; y--)
  {
    for (x = my_char * char_lenght; x < my_char * char_lenght + char_lenght;
	 x++)
    {
      cur_pixel = *(font_mem + x_font_bmp * y + x + 2);
      if (cur_pixel)
	*(++screen_buffer) = font_color;
      else
	*(++screen_buffer) = background_color;
    }
    screen_buffer += my_pitch - char_lenght;
  }

}

void
print_string (char *str, char char_color, char background_color,
	      int char_xscreen, int char_yscreen)
{
  while (*(str) != 0)
  {
    draw_char (screen, *str, char_color, background_color, char_xscreen,
	       char_yscreen);
    str++;
    char_xscreen += char_lenght;
  }

}
