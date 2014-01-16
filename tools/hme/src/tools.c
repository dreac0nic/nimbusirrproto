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
#include "tools.h"

void draw_brush (int cur_x, int cur_y);

/*
This function gets the x and y of the height that is pointed by the mouse.
It returns 0, in case the mouse points to no pixel, otherwise return 1
*/
int
get_cur_x_y ()
{
  if(!terrain_height)return 0;//we don't have a terrain
  cur_x = (x_mouse_pos - x_screen_offset) / terrain_ratio + xoffset;
  cur_y = (y_mouse_pos - y_screen_offset) / terrain_ratio + yoffset;
  if (cur_x >= 0 && cur_x < WIDTH && cur_y >= 0 && cur_y < HEIGHT)
    return 1;
  last_drawn_x = -1;
  last_drawn_y = -1;
  return 0;

}

void zoom_in ()
{
  int some_x_lenght, some_y_lenght;
  if (terrain_ratio > 15)
    return;
  if (!get_cur_x_y ())
    return;
  some_x_lenght = (window_width / (terrain_ratio + 1)) / 2;
  some_y_lenght = (window_height / (terrain_ratio + 1)) / 2;
  xoffset = (cur_x - some_x_lenght);
  yoffset = (cur_y - some_y_lenght);
  terrain_ratio++;
}

//the 'eye drop' tool, get the current pixel, under the mouse.
void pick_height (bool button_l, bool button_r)
{
  if (!get_cur_x_y ())
    return;
  color_1 = *(terrain_height + cur_y * WIDTH + cur_x);	//get the deepth
}


void select_area()
{
	if (!get_cur_x_y ())return;
	if(long_pressed_button_l==1 && selection_x_1!=-1)//we already have a selection, kill it
	{
		selection_x_1=-1;
		selection_y_1=-1;
		selection_x_2=-1;
		selection_y_2=-1;
		return;
	}

	if(long_pressed_button_l==1 && selection_x_1==-1 && selection_y_1==-1)
		{
			selection_x_1=cur_x;
			selection_y_1=cur_y;
			return;
		}

	if(long_pressed_button_l!=0 && selection_x_1!=-1)
		{
			selection_x_2=cur_x;
			selection_y_2=cur_y;
		}


}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void put_pattern(Uint8 * this_location,int x,int y)
{
	int x_pattern,y_pattern,pattern_height;

	x_pattern=x%current_pattern.object_x_len;
	y_pattern=y%current_pattern.object_y_len;
	pattern_height=*(current_pattern.object_mem+y_pattern*current_pattern.object_x_len+x_pattern);
  if(pattern_height)
  {
		if(tolerance_replace_mode==tolerance_replace_equal)
		*this_location=pattern_height;
		else if(tolerance_replace_mode==tolerance_replace_plus)
		{
			if(*this_location+pattern_height>255)
			*this_location=255;
			else
			*this_location+=pattern_height;
		}
		else if(tolerance_replace_mode==tolerance_replace_minus)
		{
			if(*this_location-pattern_height<0)
			*this_location=0;
			else
			*this_location-=pattern_height;
		}
 }

}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void replace_ver_line(short orig_x,short orig_y)
{
	int x=orig_x;
	int y=orig_y;
	int buffer_offset;
	//fill upwards
	for(;y>=0;y--)
		{
			buffer_offset=y*WIDTH+x;
			curent_height=*(terrain_height+buffer_offset);
			if (((tolerance_mode == greater &&
			curent_height>=color_2 && curent_height<=color_2+tolerance_value) ||
			(tolerance_mode == leaser &&
			curent_height<=color_2 && curent_height>=color_2-tolerance_value) ||
			(tolerance_mode == greater_or_leaser &&
			curent_height>=color_2-tolerance_value && curent_height<=color_2+tolerance_value))
			&& *(temp_buffer+buffer_offset)!=already_filled)
			{
				//now, try to see the mode we should use for the replacing
			if(tolerance_replace_mode_2==replace_mode_pattern)
			put_pattern(terrain_height+buffer_offset,x,y);
			else
			{

				if(tolerance_replace_mode==tolerance_replace_equal)
				 *(terrain_height+buffer_offset)=color_1;
				else
				if(tolerance_replace_mode==tolerance_replace_plus)
				{
					if(*(terrain_height+buffer_offset)+color_1>255)*(terrain_height+buffer_offset)=255;
					else *(terrain_height+buffer_offset)+=color_1;
				}
				else if(tolerance_replace_mode==tolerance_replace_minus)
				{
					if(*(terrain_height+buffer_offset)-color_1<0)*(terrain_height+buffer_offset)=0;
					else *(terrain_height+buffer_offset)-=color_1;
				}
			}
				 *(temp_buffer+buffer_offset)=already_filled;
				 //now, scan for the up and down neighbours
				 if(x>0)
				 	{
				 			curent_height=*(terrain_height+buffer_offset-1);
				 			if (((tolerance_mode == greater &&
				 			curent_height>=color_2 && curent_height<=color_2+tolerance_value) ||
				 			(tolerance_mode == leaser &&
				 			curent_height<=color_2 && curent_height>=color_2-tolerance_value) ||
				 			(tolerance_mode == greater_or_leaser &&
				 			curent_height>=color_2-tolerance_value && curent_height<=color_2+tolerance_value))
				 			&& *(temp_buffer+buffer_offset-1)!=already_filled)
							*(temp_buffer+buffer_offset-1)=pending_fill;
					}
				 if(x<WIDTH-1)
				 	{
				 			curent_height=*(terrain_height+buffer_offset+1);
				 			if (((tolerance_mode == greater &&
				 			curent_height>=color_2 && curent_height<=color_2+tolerance_value) ||
				 			(tolerance_mode == leaser &&
				 			curent_height<=color_2 && curent_height>=color_2-tolerance_value) ||
				 			(tolerance_mode == greater_or_leaser &&
				 			curent_height>=color_2-tolerance_value && curent_height<=color_2+tolerance_value))
				 			&& *(temp_buffer+buffer_offset+1)!=already_filled)
							*(temp_buffer+buffer_offset+1)=pending_fill;
					}
			 }
			 else break;
		}
	//fill downwards
	for(y=orig_y+1;y<HEIGHT;y++)
		{
			buffer_offset=y*WIDTH+x;
			curent_height=*(terrain_height+buffer_offset);
			if (((tolerance_mode == greater &&
			curent_height>=color_2 && curent_height<=color_2+tolerance_value) ||
			(tolerance_mode == leaser &&
			curent_height<=color_2 && curent_height>=color_2-tolerance_value) ||
			(tolerance_mode == greater_or_leaser &&
			curent_height>=color_2-tolerance_value && curent_height<=color_2+tolerance_value))
			&& *(temp_buffer+buffer_offset)!=already_filled)
			{
				//now, try to see the mode we should use for the replacing
			if(tolerance_replace_mode_2==replace_mode_pattern)
			put_pattern(terrain_height+buffer_offset,x,y);
			else
			{

				if(tolerance_replace_mode==tolerance_replace_equal)
				 *(terrain_height+buffer_offset)=color_1;
				else
				if(tolerance_replace_mode==tolerance_replace_plus)
				{
					if(*(terrain_height+buffer_offset)+color_1>255)*(terrain_height+buffer_offset)=255;
					else *(terrain_height+buffer_offset)+=color_1;
				}
				else if(tolerance_replace_mode==tolerance_replace_minus)
				{
					if(*(terrain_height+buffer_offset)-color_1<0)*(terrain_height+buffer_offset)=0;
					else *(terrain_height+buffer_offset)-=color_1;
				}
			}

				 *(temp_buffer+buffer_offset)=already_filled;
				 //now, scan for the up and down neighbours
				 if(x>0)
				 	{
				 			curent_height=*(terrain_height+buffer_offset-1);
				 			if (((tolerance_mode == greater &&
				 			curent_height>=color_2 && curent_height<=color_2+tolerance_value) ||
				 			(tolerance_mode == leaser &&
				 			curent_height<=color_2 && curent_height>=color_2-tolerance_value) ||
				 			(tolerance_mode == greater_or_leaser &&
				 			curent_height>=color_2-tolerance_value && curent_height<=color_2+tolerance_value))
				 			&& *(temp_buffer+buffer_offset-1)!=already_filled)
							*(temp_buffer+buffer_offset-1)=pending_fill;
					}
				 if(x<WIDTH-1)
				 	{
				 			curent_height=*(terrain_height+buffer_offset+1);
				 			if (((tolerance_mode == greater &&
				 			curent_height>=color_2 && curent_height<=color_2+tolerance_value) ||
				 			(tolerance_mode == leaser &&
				 			curent_height<=color_2 && curent_height>=color_2-tolerance_value) ||
				 			(tolerance_mode == greater_or_leaser &&
				 			curent_height>=color_2-tolerance_value && curent_height<=color_2+tolerance_value))
				 			&& *(temp_buffer+buffer_offset+1)!=already_filled)
							*(temp_buffer+buffer_offset+1)=pending_fill;
					}
			 }
			 else break;
		}

}

///////////////////////////////////////////////////////////////////////////
void replace_line(short orig_x,short orig_y)
{
	int x=orig_x;
	int y=orig_y;
	int buffer_offset;
	//scan left
	for(;x>=0;x--)
		{
			buffer_offset=y*WIDTH+x;
			curent_height=*(terrain_height+buffer_offset);
			if (((tolerance_mode == greater &&
			curent_height>=color_2 && curent_height<=color_2+tolerance_value) ||
			(tolerance_mode == leaser &&
			curent_height<=color_2 && curent_height>=color_2-tolerance_value) ||
			(tolerance_mode == greater_or_leaser &&
			curent_height>=color_2-tolerance_value && curent_height<=color_2+tolerance_value))
			&& *(temp_buffer+buffer_offset)!=already_filled)
			 {
				//now, try to see the mode we should use for the replacing
			if(tolerance_replace_mode_2==replace_mode_pattern)
			put_pattern(terrain_height+buffer_offset,x,y);
			else
			{
				if(tolerance_replace_mode==tolerance_replace_equal)
				 *(terrain_height+buffer_offset)=color_1;
				else
				if(tolerance_replace_mode==tolerance_replace_plus)
				{
					if(*(terrain_height+buffer_offset)+color_1>255)*(terrain_height+buffer_offset)=255;
					else *(terrain_height+buffer_offset)+=color_1;
				}
				else if(tolerance_replace_mode==tolerance_replace_minus)
				{
					if(*(terrain_height+buffer_offset)-color_1<0)*(terrain_height+buffer_offset)=0;
					else *(terrain_height+buffer_offset)-=color_1;
				}
			}


				 *(temp_buffer+buffer_offset)=already_filled;
				 //now, scan for the up and down neighbours
				 if(y>0)
				 	{
				 			curent_height=*(terrain_height+buffer_offset-WIDTH);
				 			if (((tolerance_mode == greater &&
				 			curent_height>=color_2 && curent_height<=color_2+tolerance_value) ||
				 			(tolerance_mode == leaser &&
				 			curent_height<=color_2 && curent_height>=color_2-tolerance_value) ||
				 			(tolerance_mode == greater_or_leaser &&
				 			curent_height>=color_2-tolerance_value && curent_height<=color_2+tolerance_value))
				 			&& *(temp_buffer+buffer_offset-WIDTH)!=already_filled)
				 			replace_ver_line((short)x,(short)y-1);
					}

				 if(y<HEIGHT-1)
				    {
				 			curent_height=*(terrain_height+buffer_offset+WIDTH);
				 			if (((tolerance_mode == greater &&
				 			curent_height>=color_2 && curent_height<=color_2+tolerance_value) ||
				 			(tolerance_mode == leaser &&
				 			curent_height<=color_2 && curent_height>=color_2-tolerance_value) ||
				 			(tolerance_mode == greater_or_leaser &&
				 			curent_height>=color_2-tolerance_value && curent_height<=color_2+tolerance_value))
				 			&& *(temp_buffer+buffer_offset+WIDTH)!=already_filled)
				 			replace_ver_line((short)x,(short)y+1);
					}

			 }
			 else break;
		}

	//scan right
	for(x=orig_x+1;x<WIDTH;x++)
		{
			buffer_offset=y*WIDTH+x;
			curent_height=*(terrain_height+buffer_offset);
			if (((tolerance_mode == greater &&
			curent_height>=color_2 && curent_height<=color_2+tolerance_value) ||
			(tolerance_mode == leaser &&
			curent_height<=color_2 && curent_height>=color_2-tolerance_value) ||
			(tolerance_mode == greater_or_leaser &&
			curent_height>=color_2-tolerance_value && curent_height<=color_2+tolerance_value))
			&& *(temp_buffer+buffer_offset)!=already_filled)
			 {
				//now, try to see the mode we should use for the replacing
			if(tolerance_replace_mode_2==replace_mode_pattern)
			put_pattern(terrain_height+buffer_offset,x,y);
			else
			{
				if(tolerance_replace_mode==tolerance_replace_equal)
				 *(terrain_height+buffer_offset)=color_1;
				else
				if(tolerance_replace_mode==tolerance_replace_plus)
				{
					if(*(terrain_height+buffer_offset)+color_1>255)*(terrain_height+buffer_offset)=255;
					else *(terrain_height+buffer_offset)+=color_1;
				}
				else if(tolerance_replace_mode==tolerance_replace_minus)
				{
					if(*(terrain_height+buffer_offset)-color_1<0)*(terrain_height+buffer_offset)=0;
					else *(terrain_height+buffer_offset)-=color_1;
				}
			}

				 *(temp_buffer+buffer_offset)=already_filled;
				 //now, scan for the up and down neighbours
				 if(y>0)
				 	{
				 			curent_height=*(terrain_height+buffer_offset-WIDTH);
				 			if (((tolerance_mode == greater &&
				 			curent_height>=color_2 && curent_height<=color_2+tolerance_value) ||
				 			(tolerance_mode == leaser &&
				 			curent_height<=color_2 && curent_height>=color_2-tolerance_value) ||
				 			(tolerance_mode == greater_or_leaser &&
				 			curent_height>=color_2-tolerance_value && curent_height<=color_2+tolerance_value))
				 			&& *(temp_buffer+buffer_offset-WIDTH)!=already_filled)
				 			replace_ver_line((short)x,(short)y-1);
					}

				 if(y<HEIGHT-1)
				 	{
				 			curent_height=*(terrain_height+buffer_offset+WIDTH);
				 			if (((tolerance_mode == greater &&
				 			curent_height>=color_2 && curent_height<=color_2+tolerance_value) ||
				 			(tolerance_mode == leaser &&
				 			curent_height<=color_2 && curent_height>=color_2-tolerance_value) ||
				 			(tolerance_mode == greater_or_leaser &&
				 			curent_height>=color_2-tolerance_value && curent_height<=color_2+tolerance_value))
				 			&& *(temp_buffer+buffer_offset+WIDTH)!=already_filled)
				 			replace_ver_line((short)x,(short)y+1);
					}

			 }
			 else break;
		 }

}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////


//the fill tool
void pre_change_area()
{
  int i,x,y;
  int map_size=WIDTH*HEIGHT;
  char * some_temp_buffer;
  bool no_pending_found=0;
  if (!get_cur_x_y())return;
  //try to see if the desired filling mode is pattern fill, and if we have a current pattern.
  if(tolerance_replace_mode_2==replace_mode_pattern)
  {
	  if(!current_pattern.object_mem)
	  {
					sprintf(error_msg_1,"Pattern filling mode, but there is no pattern!");
					sprintf(error_msg_2,"Righ click on the Magic Wand tool, and select a pattern!");
					view_error_menu=1;
					return;
	  }

  }

  change_cursor(cursor_wait);
  if(long_pressed_button_l==1)copy_to_undo_buffer();
  color_2 = *(terrain_height + cur_y * WIDTH + cur_x);	//get the deepth
  some_temp_buffer=temp_buffer;
  for (i = 0; i <map_size; i++)*(some_temp_buffer++)=not_filled;//clear the temp buffer
  replace_line((short)cur_x,(short)cur_y);
	while(1)
	{
		no_pending_found=0;
		some_temp_buffer=temp_buffer;
		for(i=0;i<map_size;i++)
		if(*(some_temp_buffer++)==pending_fill)
			{
				no_pending_found=1;
				y=i/WIDTH;
				x=i-y*WIDTH;
				replace_line((short)x,(short)y);
			}
		if(!no_pending_found)break;
	}
	some_temp_buffer=temp_buffer;
	for (i = 0; i <map_size; i++)*(some_temp_buffer++)=not_filled;//clear the temp buffer
	change_cursor(last_cursor);
}



void flood_ver_line(short orig_x,short orig_y)
{
	int x=orig_x;
	int y=orig_y;
	int buffer_offset;
	//fill upwards
	for(;y>=0;y--)
		{
			buffer_offset=y*WIDTH+x;
			if(*(terrain_height+buffer_offset)!=color_1)
			 {
				 *(terrain_height+buffer_offset)=color_1;
				 *(temp_buffer+buffer_offset)=already_filled;
				 //now, scan for the up and down neighbours
				 if(x>0)
				 if(*(terrain_height+buffer_offset-1)!=color_1)
				 *(temp_buffer+buffer_offset-1)=pending_fill;
				 if(x<WIDTH-1)
				 if(*(terrain_height+buffer_offset+1)!=color_1)
				 *(temp_buffer+buffer_offset+1)=pending_fill;
			 }
			 else break;
		}
	//fill downwards
	for(y=orig_y+1;y<HEIGHT;y++)
		{
			buffer_offset=y*WIDTH+x;
			if(*(terrain_height+buffer_offset)!=color_1)
			 {
				 *(terrain_height+buffer_offset)=color_1;
				 *(temp_buffer+buffer_offset)=already_filled;
				 //now, scan for the up and down neighbours
				 if(x>0)
				 if(*(terrain_height+buffer_offset-1)!=color_1)
				 *(temp_buffer+buffer_offset-1)=pending_fill;
				 if(x<WIDTH-1)
				 if(*(terrain_height+buffer_offset+1)!=color_1)
				 *(temp_buffer+buffer_offset+1)=pending_fill;
			 }
			 else break;
		}

}

///////////////////////////////////////////////////////////////////////////
void flood_line(short orig_x,short orig_y)
{
	int x=orig_x;
	int y=orig_y;
	int buffer_offset;
	//scan left
	for(;x>=0;x--)
		{
			buffer_offset=y*WIDTH+x;
			if(*(terrain_height+buffer_offset)!=color_1)
			 {
				 *(terrain_height+buffer_offset)=color_1;
				 *(temp_buffer+buffer_offset)=already_filled;
				 //now, scan for the up and down neighbours
				 if(y>0)
				 if(*(terrain_height+buffer_offset-WIDTH)!=color_1)
				 flood_ver_line((short)x,(short)y-1);
				 if(y<HEIGHT-1)
				 if(*(terrain_height+buffer_offset+WIDTH)!=color_1)
				 flood_ver_line((short)x,(short)y+1);
			 }
			 else break;
		}

	//scan right
	for(x=orig_x+1;x<WIDTH;x++)
		{
			buffer_offset=y*WIDTH+x;
			if(*(terrain_height+buffer_offset)!=color_1)
			 {
				 *(terrain_height+buffer_offset)=color_1;
				 *(temp_buffer+buffer_offset)=already_filled;
				 //now, scan for the up and down neighbours
				 if(y>0)
				 if(*(terrain_height+buffer_offset-WIDTH)!=color_1)
				 flood_ver_line((short)x,(short)y-1);
				 if(y<HEIGHT-1)
				 if(*(terrain_height+buffer_offset+WIDTH)!=color_1)
				 flood_ver_line((short)x,(short)y+1);
			 }
			 else break;
		}
}



//the fill tool
void pre_flood_area ()
{
  int i,x,y;
  int map_size=WIDTH*HEIGHT;
  char * some_temp_buffer;
  bool no_pending_found=0;
  if (!get_cur_x_y ())return;
  change_cursor(cursor_wait);
  if(long_pressed_button_l==1)copy_to_undo_buffer();
  some_temp_buffer=temp_buffer;
  for (i = 0; i <map_size; i++)*(some_temp_buffer++)=not_filled;//clear the temp buffer
  flood_line((short)cur_x,(short)cur_y);
	while(1)
	{
		no_pending_found=0;
		some_temp_buffer=temp_buffer;
		for(i=0;i<map_size;i++)
		if(*(some_temp_buffer++)==pending_fill)
			{
				no_pending_found=1;
				y=i/WIDTH;
				x=i-y*WIDTH;
				flood_line((short)x,(short)y);
			}
		if(!no_pending_found)break;
	}
	some_temp_buffer=temp_buffer;
	for (i = 0; i <map_size; i++)*(some_temp_buffer++)=not_filled;//clear the temp buffer
	change_cursor(last_cursor);
}


///////////////////////////////////////////////////////////////////////////
void
draw_brush_line ()
{
  int start_x, start_y, x_len, y_len;
  int i = 0;
  int delta_x, delta_y, line_lenght;
  float xstep, ystep, x, y;

  if (!get_cur_x_y ())
  {
    last_drawn_x = -1;
    last_drawn_y = -1;
    return;			//nope, not on the map
  }


  /*
     Ok, now, if the user moves the mouse very fast, what s/he draws will be fragmented.
     So, we need to do some sort of interpolations, and draw lines.
   */
  if (last_drawn_x == -1)
    delta_x = 0;
  else
    delta_x = last_drawn_x - cur_x;


  if (last_drawn_y == -1)
    delta_y = 0;
  else
    delta_y = last_drawn_y - cur_y;


  line_lenght = (int) sqrt (delta_x * delta_x + delta_y * delta_y);

  //ok, now update the last drawn x and y
  last_drawn_x = cur_x;
  last_drawn_y = cur_y;

  if (line_lenght == 0)		//just draw this point
  {
    draw_brush (cur_x, cur_y);
    return;
  }

  ystep = (float) delta_y / line_lenght;
  xstep = (float) delta_x / line_lenght;
  x = (float) cur_x;
  y = (float) cur_y;
  for (; i <= line_lenght; i++)
  {
    draw_brush ((int) x, (int) y);
    x += xstep;
    y += ystep;
  }

}


void
draw_brush (int this_cur_x, int this_cur_y)
{
  int x, y, start_x, start_y, x_len, y_len;

  //see if we have to clear the temp buffer
    if(clear_temp_buffer && long_pressed_button_l==1)
      {
		do_clear_temp_buffer ();
		clear_temp_buffer = 0;
		min_drawn_x = 0xffff;
		min_drawn_y = 0xffff;
		max_drawn_x = 0;
		max_drawn_y = 0;
      }

  undo=partial_undo;//the undo type we have here

  if (brush_size == 1)		//very small brush (1 pixel)
  {
    start_y = this_cur_y;
    start_x = this_cur_x;
    y_len = 1;
    x_len = 1;
  }
  else if (brush_size == 2)	//small brush (3 pixels)
  {
    start_y = this_cur_y - 1;
    start_x = this_cur_x - 1;
    y_len = 3;
    x_len = 3;
  }
  else if (brush_size == 3)	//medium brush (5 pixels)
  {
    start_y = this_cur_y - 2;
    start_x = this_cur_x - 2;
    y_len = 5;
    x_len = 5;
  }
  else if (brush_size == 4)	//large brush (7 pixels)
  {
    start_y = this_cur_y - 3;
    start_x = this_cur_x - 3;
    y_len = 7;
    x_len = 7;
  }
  else if (brush_size == 5)	//extra large brush (9 pixels)
  {
    start_y = this_cur_y - 4;
    start_x = this_cur_x - 4;
    y_len = 9;
    x_len = 9;
  }

  for (y = start_y; y < start_y + y_len; y++)
    for (x = start_x; x < start_x + x_len; x++)
      if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
	if (*(temp_buffer + y * WIDTH + x) == 0)	//did we already draw here, since the last mouse down evenet?
	{
	  //first thing to do is save the current pixel, in the undo buffer
	  *(undo_buffer + y * WIDTH + x)=*(terrain_height + y * WIDTH + x);
	  //now, find what tool we use
	  if (current_tool == t_place)
	    *(terrain_height + y * WIDTH + x) = color_1;
	  else if (current_tool == t_escavate)
	  {
	    if (*(terrain_height + y * WIDTH + x) - color_1 > 0)
	      *(terrain_height + y * WIDTH + x) -= color_1;
	    else
	      *(terrain_height + y * WIDTH + x) = 0;
	  }
	  else if (current_tool == t_elevate)
	  {
	    if (*(terrain_height + y * WIDTH + x) + color_1 < 255)
	      *(terrain_height + y * WIDTH + x) += color_1;
	    else
	      *(terrain_height + y * WIDTH + x) = 255;
	  }
	  //ok, now it's time to mark this pixel as 'already modified'
	  *(temp_buffer + y * WIDTH + x) = 1;
	  //now, update the min and max drawn
	  if (x < min_drawn_x)
	    min_drawn_x = x;
	  if (y < min_drawn_y)
	    min_drawn_y = y;
	  if (x > max_drawn_x)
	    max_drawn_x = x;
	  if (y > max_drawn_y)
	    max_drawn_y = y;
	  max_drawn_x = max_drawn_x & 0xfffc;
	  min_drawn_x = min_drawn_x | 3;

	  //and, we should also clear the buffer, at the next mouse up event.
	  clear_temp_buffer = 1;

	}

}

void stamp_object()
{
	  int object_x_start=0;
	  int object_y_start=0;
	  int object_x_terrain_start,object_y_terrain_start;
	  int object_x_terrain_end,object_y_terrain_end;

	  int x,y,j,k;

	  int cur_height;

	  copy_to_undo_buffer();
	  //now, do get the terrain coordinates.
	  object_x_terrain_start=((x_mouse_pos-x_screen_offset)-(current_object.object_x_len/2*terrain_ratio))/ terrain_ratio + xoffset;
	  object_y_terrain_start=((y_mouse_pos-y_screen_offset)-(current_object.object_y_len/2*terrain_ratio))/ terrain_ratio + yoffset;
	  object_x_terrain_end=((x_mouse_pos-x_screen_offset)+(current_object.object_x_len/2*terrain_ratio))/ terrain_ratio + xoffset;
	  object_y_terrain_end=((y_mouse_pos-y_screen_offset)+(current_object.object_y_len/2*terrain_ratio))/ terrain_ratio + yoffset;


	  if(object_x_terrain_start<0)object_x_start=object_x_terrain_start*-1;
	  if(object_y_terrain_start<0)object_y_start=object_y_terrain_start*-1;

	  //do some final adjustments
	  if(object_x_terrain_start<0)object_x_terrain_start=0;
	  if(object_y_terrain_start<0)object_y_terrain_start=0;
	  if(object_x_terrain_end>WIDTH)object_x_terrain_end=WIDTH;
	  if(object_y_terrain_end>HEIGHT)object_y_terrain_end=HEIGHT;

	  //ok, now just display the object
	  if(object_mode==put_object)
	  {
		j=object_y_start;
	  	for(y=object_y_terrain_start;y<object_y_terrain_end;y++)
	  		{
				k=object_x_start;
	  			for(x=object_x_terrain_start;x<object_x_terrain_end;x++)
	  				{
						cur_height=*(current_object.object_mem+j*current_object.object_x_len+k);
						if(cur_height)
							{
	  							*(terrain_height+y*WIDTH+x)=cur_height;
							}
						k++;
					}
				j++;
			}
	  return;
	  }//ok, end of place_mode
	  else
	  if(object_mode==add_object)
	  {
		j=object_y_start;
	  	for(y=object_y_terrain_start;y<object_y_terrain_end;y++)
	  		{
				k=object_x_start;
	  			for(x=object_x_terrain_start;x<object_x_terrain_end;x++)
	  				{
						cur_height=*(current_object.object_mem+j*current_object.object_x_len+k);
						if(cur_height)
							{
								cur_height+=*(terrain_height+y*WIDTH+x);
								if(cur_height>255)cur_height=255;
			  					*(terrain_height+y*WIDTH+x)=cur_height;
							}
						k++;
					}
				j++;
			}
	  return;
	  }//ok, end of add_mode
	  else
	  if(object_mode==sub_object)
	  {
		j=object_y_start;
	  	for(y=object_y_terrain_start;y<object_y_terrain_end;y++)
	  		{
				k=object_x_start;
	  			for(x=object_x_terrain_start;x<object_x_terrain_end;x++)
	  				{
						cur_height=*(current_object.object_mem+j*current_object.object_x_len+k);
						if(cur_height)
							{
								cur_height=*(terrain_height+y*WIDTH+x)-cur_height;
								if(cur_height<0)cur_height=0;
			  					*(terrain_height+y*WIDTH+x)=cur_height;
							}
						k++;
					}
				j++;
			}
	  return;
	  }//ok, end of sub_mode

}