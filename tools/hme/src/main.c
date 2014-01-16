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

#include <SDL/SDL.h>
#include <SDL/SDL_endian.h>	/* Used for the endian-dependent 24 bpp mode */
#include <stdlib.h>
#include <time.h>

// WINDOWS is or is not defined in global.h
#include "global.h"


#ifdef WINDOWS
#include <windows.h>
#endif

#include "init.h"
#include "cursors.h"
#include "load_save.h"
#include "global_tools.h"
#include "tools.h"
#include "actions.h"
#include "draw_stuff.h"
#include "menus.h"
#include "font.h"
#include "generate_terrain.h"
#include "display_terrain.h"
#include "events.h"
#include "settings.h"
#include "objects.h"


int
#ifdef WINDOWS
Main()
#else
main ()
#endif
{
  //int i;
  Uint32 (*on_screen_pointer) (unsigned int) = on_screen;
  SDL_Init (SDL_INIT_VIDEO || SDL_INIT_TIMER);
  load_settings ();
  screen = SDL_SetVideoMode (window_width, window_height, 8,SDL_HWSURFACE | SDL_RESIZABLE | SDL_HWPALETTE);
  SDL_WM_SetIcon(SDL_LoadBMP("icon.bmp"), NULL);
  SDL_WM_SetCaption ("Terrain Editor", "Terrain Editor");
  if (screen == NULL)
  {
    fprintf (stderr, "Could not initialize video\n");
    exit (1);
  }
  load_font();
  load_tool_bar();
  build_tool_bar();
  load_cursors();
  build_numeric_dialog_boxes();
  build_cursors();
  change_cursor(cursor_put);
  SDL_EnableKeyRepeat (200, 100);

  //now, define our custom colors
  //black
  colors[255].r = 0;
  colors[255].g = 0;
  colors[255].b = 0;
  //white
  colors[254].r = 255;
  colors[254].g = 255;
  colors[254].b = 255;
  //darkblue
  colors[253].r = 20;
  colors[253].g = 40;
  colors[253].b = 160;
  //light blue
  colors[252].r = 20;
  colors[252].g = 140;
  colors[252].b = 255;
  //green
  colors[251].r = 20;
  colors[251].g = 255;
  colors[251].b = 100;
  //red
  colors[250].r = 250;
  colors[250].g = 55;
  colors[250].b = 10;
  //gray
  colors[249].r = 150;
  colors[249].g = 150;
  colors[249].b = 150;
  //steel blue
  colors[248].r = 140;
  colors[248].g = 170;
  colors[248].b = 200;
  //light steel blue
  colors[247].r = 170;
  colors[247].g = 200;
  colors[247].b = 230;
  //very light steel blue
  colors[246].r = 190;
  colors[246].g = 220;
  colors[246].b = 250;
  //dark steel blue
  colors[245].r = 100;
  colors[245].g = 130;
  colors[245].b = 160;

if(gray_shades)make_gray_pallete();
else make_color_pallete();

  seed = time (NULL);
  srand (seed);
  allocate_mem();
  overdraw_terrain ();
  SDL_SetTimer (100, on_screen_pointer);
  events_loop ();
  save_settings ();		//save the settings, at exit
  SDL_Quit ();
  //clear the allocated memory
  if (terrain_height)free (terrain_height);
  if (temp_buffer)free (temp_buffer);
  if (handle_font_mem)free(handle_font_mem);
  if (handle_tool_bar_mem)free(handle_tool_bar_mem);
  if (cursors_mem)free(cursors_mem);
  return 1;
}

#ifdef WINDOWS
int STDCALL WinMain (HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, int nShow)
{
Main();
  return 0;
}
#endif
