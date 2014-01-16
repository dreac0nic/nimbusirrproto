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

#include <stdio.h>
#include <string.h>
#include "settings.h"


#ifdef WINDOWS
#include <windows.h>
#include <winbase.h>//for the GetCurrentDirectory
#endif

//load the settings, at startup
void
load_settings ()
{
  FILE *f = NULL;

  #ifdef WINDOWS
  GetCurrentDirectory(sizeof(conf_file_path),conf_file_path);
  #else
  getcwd(200,conf_file_path);
  #endif

  strcat(conf_file_path,"/settings.cfg");

  f = fopen (conf_file_path, "rb");
  if (!f)
    return;			//file not found
  fread (settings, 1, sizeof (settings), f);
  fclose (f);
//ok, now set the variables
  window_width = settings[0].window_x;
  window_height = settings[0].window_y;

  min_map_x = settings[0].minmap_x;
  min_map_y = settings[0].minmap_y;
  mini_map = settings[0].minmap_active;

  tool_bar_x = settings[0].toolbar_x;
  tool_bar_y = settings[0].toolbar_y;
  tool_bar = settings[0].toolbar_active;

  status_bar_x = settings[0].statusbar_x;
  status_bar_y = settings[0].statusbar_y;
  status_bar = settings[0].statusbar_active;

  grid = settings[0].grid_size;
  color_1 = settings[0].last_height_used;
  tolerance_value = settings[0].replace_tolerance;
  tolerance_mode = settings[0].tolerance_mode;
  overwrite_terrain = settings[0].overwrite_terrain;
  gray_shades = settings[0].gray_shades;


}

void
save_settings ()
{
  FILE *f = NULL;

  settings[0].window_x = window_width;
  settings[0].window_y = window_height;

  settings[0].minmap_x = min_map_x;
  settings[0].minmap_y = min_map_y;
  settings[0].minmap_active = mini_map;

  settings[0].toolbar_x = tool_bar_x;
  settings[0].toolbar_y = tool_bar_y;
  settings[0].toolbar_active = tool_bar;

  settings[0].statusbar_x = status_bar_x;
  settings[0].statusbar_y = status_bar_y;
  settings[0].statusbar_active = status_bar;

  settings[0].grid_size = grid;
  settings[0].last_height_used = color_1;
  settings[0].replace_tolerance = tolerance_value;
  settings[0].tolerance_mode = tolerance_mode;
  settings[0].overwrite_terrain = overwrite_terrain;
  settings[0].gray_shades = gray_shades;

  f = fopen (conf_file_path, "wb");
  fwrite (settings, sizeof (settings), 1, f);
  fclose (f);
}
