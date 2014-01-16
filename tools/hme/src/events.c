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

#include <SDL/SDL_events.h>
#include <SDL/SDL_keysym.h>
#include "events.h"

void
events_loop (void)
{
  SDL_Event event;
  SDLMod mod_key_status;
  int i;

  while (1)
  {
    SDL_WaitEvent (&event);
    if (event.type == SDL_QUIT)
      break;
    mod_key_status=SDL_GetModState();
    if(mod_key_status&KMOD_CAPS)caps_look_on=1;
	else caps_look_on=0;

    if (event.type == SDL_MOUSEBUTTONUP)
    {
      while (SDL_PollEvent (&event));	//clears all the events
	if((selection_x_1!=-1 && selection_x_2==-1) || selection_x_1==selection_x_2 || selection_y_1==selection_y_2)
	{
		selection_x_1=-1;
		selection_y_1=-1;
		selection_x_2=-1;
		selection_y_2=-1;
	}

      drag_minimap = 0;
      drag_toolbar = 0;
      drag_statusbar = 0;

      last_drawn_x = -1;
      last_drawn_y = -1;
      //mark buttons as unpressed at all, so they are fresh.
      long_pressed_button_l = 0;
      long_pressed_button_r = 0;
      if (SDL_GetMouseState (NULL, NULL) & SDL_BUTTON (SDL_BUTTON_LEFT))
	button_l = 1;
      else
	button_l = 0;
      if (SDL_GetMouseState (NULL, NULL) & SDL_BUTTON (SDL_BUTTON_RIGHT))
	button_r = 1;
      else
	button_r = 0;
      //now, check to see if there is any button up on the toolbar
      check_toolbar_release ();

    }

    if (event.type == SDL_VIDEORESIZE)
    {
	  no_update_now=1;
      window_width = event.resize.w;
      window_height = event.resize.h;
      if (window_width < 680)window_width = 680;
      if (window_height < 450)window_height = 450;
      window_width=window_width|3;
      screen = SDL_SetVideoMode (window_width, window_height,8,SDL_HWSURFACE | SDL_RESIZABLE | SDL_HWPALETTE);
      SDL_SetPalette (screen, SDL_LOGPAL | SDL_PHYSPAL, colors, 0, 256);
      if(isometric_window_buffer)free(isometric_window_buffer);
      isometric_window_buffer=NULL;

    }
if(!isometric_terrain)
{
    if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN)
    {
      x_mouse_pos = event.motion.x;
      y_mouse_pos = event.motion.y;
      mouse_delta_x = event.motion.xrel;
      mouse_delta_y = event.motion.yrel;
      //get the buttons state
      if (SDL_GetMouseState (NULL, NULL) & SDL_BUTTON (SDL_BUTTON_LEFT))
      {
	button_l = 1;
	long_pressed_button_l++;
      }
      else
	button_l = 0;

      if (SDL_GetMouseState (NULL, NULL) & SDL_BUTTON (SDL_BUTTON_RIGHT))
      {
	button_r = 1;
	long_pressed_button_r++;
      }
      else
	button_r = 0;
      if (drag_minimap)
	move_minimap ();
      else if (drag_toolbar)
	move_toolbar ();
      else if (drag_statusbar)
	move_statusbar ();

#ifndef WINDOWS
      if (view_file_menu)	//in case the file menu is active, go and stay there
      {
	check_file_menu (0);
	continue;
      }
#endif

      if (view_error_menu)	//in case the replace menu is active, go and stay there
      {
	check_error_menu (0);
	continue;
      }

      if (show_new_terrain_menu)	//in case the generate terrain menu is active, go and stay there
      {
	check_new_terrain_menu (0);
	continue;
      }

      if (show_generate_terrain_menu)	//in case the generate terrain menu is active, go and stay there
      {
	check_generate_terrain_menu (0);
	continue;
      }

      if (show_view_menu)	//in case the view menu is active, go and stay there
      {
	check_view_menu (0);
	continue;
      }

      if (show_replace_menu)	//in case the replace menu is active, go and stay there
      {
	check_replace_menu (0);
	continue;
      }

      if (show_global_replace_menu)	//in case the replace menu is active, go and stay there
      {
	check_global_replace_menu (0);
	continue;
      }

      if (show_rotate_menu)	//in case the replace menu is active, go and stay there
      {
	check_rotate_menu (0);
	continue;
      }

      if (show_object_menu)	//in case the replace menu is active, go and stay there
      {
	check_object_menu (0);
	continue;
      }

      check_toolbar_mouse_over ();

      if (button_l || button_r)
	mouse_click (button_l, button_r, x_mouse_pos, y_mouse_pos);

    }//end of SDL_MOUSEMOTION event


#ifndef WINDOWS
    if (view_file_menu)
    {
      char some_char = 0;
      if (event.type == SDL_KEYDOWN)
      {
	some_char = event.key.keysym.sym;
      }
      check_file_menu (some_char);
      continue;
    }
#endif

    if (view_error_menu)
    {
      char some_char = 0;
      if (event.type == SDL_KEYDOWN)
      {
	some_char = event.key.keysym.sym;
      }
      check_error_menu (some_char);
      continue;
    }


    if (show_new_terrain_menu)	//in case the generate terrain menu is active, go and stay there
    {
      char some_char = 0;
      if (event.type == SDL_KEYDOWN)
      {
	some_char = event.key.keysym.sym;
      }
      check_new_terrain_menu (some_char);
      continue;
    }

    if (show_generate_terrain_menu)	//in case the generate terrain menu is active, go and stay there
    {
      char some_char = 0;
      if (event.type == SDL_KEYDOWN)
      {
	some_char = event.key.keysym.sym;
      }
      check_generate_terrain_menu (some_char);
      continue;
    }

    if (show_replace_menu)
    {
      char some_char = 0;
      if (event.type == SDL_KEYDOWN)
      {
	some_char = event.key.keysym.sym;
      }
      check_replace_menu (some_char);
      continue;
    }

    if (show_global_replace_menu)
    {
      char some_char = 0;
      if (event.type == SDL_KEYDOWN)
      {
	some_char = event.key.keysym.sym;
      }
      check_global_replace_menu (some_char);
      continue;
    }

    if (show_object_menu)
    {
      char some_char = 0;
      if (event.type == SDL_KEYDOWN)
      {
	some_char = event.key.keysym.sym;
      }
      check_object_menu (some_char);
      continue;
    }



    if (event.type == SDL_KEYDOWN)
    {
      Uint8 *keystate = SDL_GetKeyState (NULL);
      if (keystate[SDLK_DOWN]&& (HEIGHT * terrain_ratio - yoffset) > window_height)yoffset += 4;
      if (keystate[SDLK_UP]&& yoffset > 0)yoffset -= 4;
      if (keystate[SDLK_LEFT] && xoffset > 0)xoffset -= 4;
      if (keystate[SDLK_RIGHT]&& (WIDTH * terrain_ratio - xoffset) > window_width)xoffset += 4;
      if (keystate[SDLK_TAB])
      	{
      		isometric_terrain=!isometric_terrain;
			kill_isometric_buffer_semaphore=1;
		}

	  if (keystate[SDLK_z])
	  	{
			mod_key_status=SDL_GetModState();
			if(mod_key_status&KMOD_CTRL)do_undo();
		}
    }
}//end of the isometrical view thing
else
    if (event.type == SDL_KEYDOWN)
    {
      Uint8 *keystate = SDL_GetKeyState (NULL);
      if (keystate[SDLK_TAB])
      	{
      		isometric_terrain=!isometric_terrain;
			kill_isometric_buffer_semaphore=1;
		}

    }

  }
}

void
mouse_click (bool left_b, bool right_b, int mouse_x, int mouse_y)
{
  //check the tool bar
  if (tool_bar)
    if (check_toolbar_press ())return;

  //check to see if we clicked on the minimap
  if (mini_map)
    if (check_mouse_minimap ())return;
  //ok, so no minimap

  //check the status bar
  if (status_bar)
    if (status_bar_press ())return;

  //check if there is a right click on the terrain, to show the view menu
  if(long_pressed_button_r == 1)
  //see if we are dragging a terrain object
  if(current_tool==t_object)
  {
	  int i;
	  free(current_object.object_mem);
	  current_object.object_mem=0;
	  //change the tool to the draw tool
	  current_tool=t_place;
	  for(i=0;i<no_of_main_tool_bar_icons;i++)main_tool_bar[i].icon_active = 0;
	  main_tool_bar[0].icon_active = 1;
  }
  //if not, then just pop up the View menu
  else show_view_menu = 1;


  //don't do any terain realted things, if the right button is pressed
  if (long_pressed_button_r != 0)
    return;
  //after all tests ended
  if (last_click_on != click_terrain)
    if (long_pressed_button_l != 1)
      return;
    else
      last_click_on = click_terrain;
  switch (current_tool)
  {
  case t_peek:
    pick_height (left_b, right_b);
    return;
    break;

  case t_place:
    draw_brush_line ();
    return;
    break;

  case t_elevate:
    draw_brush_line ();
    return;
    break;

  case t_escavate:
    draw_brush_line ();
    return;
    break;

  case t_flood:
    pre_flood_area ();
    return;
    break;

  case t_replace:
    pre_change_area ();
    return;
    break;

  case t_global_replace:
    global_replace();
    return;
    break;

  case t_zoom_in:
    zoom_in ();
    return;
    break;

  case t_select:
    select_area();
    return;
    break;

  case t_object:
    if(long_pressed_button_l==1)stamp_object();
    return;
    break;

  default:
    return;
  }
}
