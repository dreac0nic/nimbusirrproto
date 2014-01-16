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

#include "global_tools.h"

void new_terrain_menu ()
{
  show_new_terrain_menu = 1;
  sprintf (numeric_dialog_boxes[x_map_size_dialog].dialog_text, "%d", WIDTH);
  sprintf (numeric_dialog_boxes[y_map_size_dialog].dialog_text, "%d", HEIGHT);
  sprintf (numeric_dialog_boxes[base_height_dialog].dialog_text, "%d",
  numeric_dialog_boxes[base_height_dialog].current_number);

}

void generate_menu ()
{
  show_generate_terrain_menu = 1;
  sprintf (numeric_dialog_boxes[seed_dialog].dialog_text, "%d", seed);
  numeric_dialog_boxes[seed_dialog].text_offset = 0;
  change_cursor(cursor_arrow);

}

void do_clear_temp_buffer ()
{
  int x, y;
  int *temp_buffer_pointer;
  temp_buffer_pointer = (int *) temp_buffer;
  temp_buffer_pointer += (WIDTH * min_drawn_y + min_drawn_x) / 4;
  for (y = min_drawn_y; y <= max_drawn_y; y++)
  {
    for (x = min_drawn_x / 4; x <= max_drawn_x / 4; x++)
      *(temp_buffer_pointer++) = 0;
    temp_buffer_pointer += (WIDTH - (max_drawn_x - min_drawn_x) - 4) / 4;
  }
}

void global_replace()
{
  int i,x,y;
  int cur_height;
  int map_size=WIDTH*HEIGHT;
  if(!terrain_height)return;
  if (!get_cur_x_y())return;
  if(global_tolerance_replace_mode_2==replace_mode_pattern)
  {
	  if(!current_pattern.object_mem)
	  {
					sprintf(error_msg_1,"Pattern filling mode, but there is no pattern!");
					sprintf(error_msg_2,"Please select a pattern!");
					view_error_menu=1;
					return;
	  }

  }
  change_cursor(cursor_wait);
  copy_to_undo_buffer();
  color_2 = *(terrain_height + cur_y * WIDTH + cur_x);	//get the deepth

  for (i = 0; i < map_size; i++)
  	{
	  	cur_height=*(terrain_height + i);
	  	//check to see if we got a match
			if ((global_tolerance_mode == greater &&
			cur_height>=color_2 && cur_height<=color_2+global_tolerance_value) ||
			(global_tolerance_mode == leaser &&
			cur_height<=color_2 && cur_height>=color_2-global_tolerance_value) ||
			(global_tolerance_mode == greater_or_leaser &&
			cur_height>=color_2-global_tolerance_value && cur_height<=color_2+global_tolerance_value))
				{
						if(global_tolerance_replace_mode_2==replace_mode_pattern)
							{
								y=i/WIDTH;
								x=i%WIDTH;
								put_pattern(terrain_height+i,x,y);
							}
						else
						{

							if(global_tolerance_replace_mode==tolerance_replace_equal)
							 *(terrain_height+i)=color_1;
							else
							if(global_tolerance_replace_mode==tolerance_replace_plus)
							{
								if(*(terrain_height+i)+color_1>255)*(terrain_height+i)=255;
								else *(terrain_height+i)+=color_1;
							}
							else if(global_tolerance_replace_mode==tolerance_replace_minus)
							{
								if(*(terrain_height+i)-color_1<0)*(terrain_height+i)=0;
								else *(terrain_height+i)-=color_1;
							}
						}
				}

	}

  change_cursor(last_cursor);
}

void do_undo()
{
	int x,y,x_start,x_end,swap_int;
	Uint8 * swap_var;
	if(undo==partial_undo)
	{
		for(y=min_drawn_y;y<=max_drawn_y;y++)
		{
			x_start=min_drawn_x-3;
			if(x_start<0)x_start=0;
			x_end=max_drawn_x+3;
			if(x_end>WIDTH)x_end=WIDTH;

			for(x=x_start;x<=x_end;x++)
			{
				if(*(temp_buffer + y * WIDTH + x))
				*(terrain_height + y * WIDTH + x)=*(undo_buffer + y * WIDTH + x);
			}
		}
	}
	else
	if(undo==total_undo)
	{
		swap_var=terrain_height;
		terrain_height=(char*)undo_buffer;
		undo_buffer=(char*)swap_var;
	}
	else
	if(undo==total_undo_swap_x_y)
	{
		swap_int=HEIGHT;
		HEIGHT=WIDTH;
		WIDTH=swap_int;
		swap_var=terrain_height;
		terrain_height=(char*)undo_buffer;
		undo_buffer=(char*)swap_var;
	}


undo=no_undo;
}

void copy_to_undo_buffer()
{
	Uint8 *	undo_buffer_pointer=undo_buffer;
	Uint8 *	terrain_buffer_pointer=terrain_height;
	int i=0;
	int map_size=WIDTH*HEIGHT;
	for(i=0;i<map_size;i++)*undo_buffer_pointer++=*terrain_buffer_pointer++;
	undo=total_undo;
}

void rise_terrain ()
{
  int i;
  int map_size=WIDTH*HEIGHT;
  if(!terrain_height)return;
  change_cursor(cursor_wait);
  copy_to_undo_buffer();
  for (i = 0; i < map_size; i++)
    if (*(terrain_height + i) + color_1 < 255)
      *(terrain_height + i) += color_1;
    else
      *(terrain_height + i) = 255;
  change_cursor(last_cursor);
}

void sink_terrain ()
{
  int i;
  int map_size=WIDTH*HEIGHT;
  if (!terrain_height)return;
  change_cursor(cursor_wait);
  copy_to_undo_buffer();
  for (i = 0; i < map_size; i++)
    if (*(terrain_height + i) - color_1 > 0)
      *(terrain_height + i) -= color_1;
    else
      *(terrain_height + i) = 0;
  change_cursor(last_cursor);
}

void flip_z ()
{
  int i;
  int map_size=WIDTH*HEIGHT;
  if (!terrain_height)return;
  copy_to_undo_buffer();
  change_cursor(cursor_wait);
  for (i = 0; i < map_size; i++)*(terrain_height + i) = 0-*(terrain_height + i);
  change_cursor(last_cursor);
}

void flip_y ()
{
  int x,y,map_offset,undo_offset;
  int map_size=WIDTH*HEIGHT;
  if (!terrain_height)return;
  change_cursor(cursor_wait);
  copy_to_undo_buffer();
  for (y = 0; y<HEIGHT; y++)
  	{
		map_offset=y*WIDTH;
		undo_offset=(HEIGHT-1-y)*WIDTH;
		for (x = 0; x<WIDTH; x++)
			{
				*(terrain_height + map_offset)=*(undo_buffer + undo_offset);
				map_offset++;
				undo_offset++;
			}

	}
  change_cursor(last_cursor);

}

void flip_x ()
{
  int x,y,map_offset,undo_offset;
  int map_size=WIDTH*HEIGHT;
  if (!terrain_height)return;
  change_cursor(cursor_wait);
  copy_to_undo_buffer();
  for (y = 0; y<HEIGHT; y++)
  	{
		map_offset=y*WIDTH;
		undo_offset=(y+1)*WIDTH-1;
		for (x = 0; x<WIDTH; x++)
			{
				*(terrain_height + map_offset)=*(undo_buffer + undo_offset);
				map_offset++;
				undo_offset--;
			}

	}
  change_cursor(last_cursor);

}

void rotate_90_CW()
{
  int x,y,map_offset,undo_offset,old_height,old_width;
  int map_size=WIDTH*HEIGHT;
  if (!terrain_height)return;
  change_cursor(cursor_wait);
  copy_to_undo_buffer();
  old_height=HEIGHT;
  old_width=WIDTH;
  HEIGHT=WIDTH;
  WIDTH=old_height;
  map_offset=0;
  for (y = 0; y<old_height; y++)
  	{
		map_offset=old_height-1-y;
		undo_offset=y*old_width;
		for (x = 0; x<old_width; x++)
			{
				*(terrain_height + map_offset)=*(undo_buffer + undo_offset);
				map_offset+=WIDTH;
				undo_offset++;
			}
	}
	undo=total_undo_swap_x_y;
	change_cursor(last_cursor);
}

void rotate_90_CCW()
{
  int x,y,map_offset,undo_offset,old_height,old_width;
  int map_size=WIDTH*HEIGHT;
  if (!terrain_height)return;
  change_cursor(cursor_wait);
  copy_to_undo_buffer();
  old_height=HEIGHT;
  old_width=WIDTH;
  HEIGHT=WIDTH;
  WIDTH=old_height;
  map_offset=0;
  for (y = 0; y<old_height; y++)
  	{
		map_offset=y;
		undo_offset=(y+1)*old_width-1;
		for (x = 0; x<old_width; x++)
			{
				*(terrain_height + map_offset)=*(undo_buffer + undo_offset);
				map_offset+=WIDTH;
				undo_offset--;
			}
	}
	undo=total_undo_swap_x_y;
	change_cursor(last_cursor);
}


void rotate_180 ()
{
  int x,y,map_offset,undo_offset;
  int map_size=WIDTH*HEIGHT;
  if (!terrain_height)return;
  change_cursor(cursor_wait);
  copy_to_undo_buffer();
  for (y = 0; y<HEIGHT; y++)
  	{
		map_offset=(y+1)*WIDTH-1;
		undo_offset=(HEIGHT-1-y)*WIDTH;
		for (x = 0; x<WIDTH; x++)
			{
				*(terrain_height + map_offset)=*(undo_buffer + undo_offset);
				map_offset--;
				undo_offset++;
			}

	}
change_cursor(last_cursor);

}


void smooth_terrain ()
{
  int x, y, sum;
  if(!terrain_height)return;
  change_cursor(cursor_wait);
  copy_to_undo_buffer();
  for (y = 1; y < HEIGHT - 1; y++)
    for (x = 1; x < WIDTH - 1; x++)
    {
      sum = *(terrain_height + y * WIDTH + x);
      sum += *(terrain_height + ((y - 1) * WIDTH) + x - 1);
      sum += *(terrain_height + ((y - 1) * WIDTH) + x);
      sum += *(terrain_height + ((y - 1) * WIDTH) + x + 1);
      sum += *(terrain_height + (y * WIDTH) + x - 1);
      sum += *(terrain_height + (y * WIDTH) + x + 1);
      sum += *(terrain_height + ((y + 1) * WIDTH) + x - 1);
      sum += *(terrain_height + ((y + 1) * WIDTH) + x);
      sum += *(terrain_height + ((y + 1) * WIDTH) + x + 1);

      if(sum%9>4)sum = (sum / 9)+1;
      else sum=sum/9;
      *(terrain_height + y * WIDTH + x) = sum;
    }
    change_cursor(last_cursor);

}

void smooth_selection ()
{
  int x, y, start_x,start_y,end_x,end_y,sum;
  if (!terrain_height)return;
  change_cursor(cursor_wait);
  copy_to_undo_buffer();
    if(selection_x_1<selection_x_2)
    {
	  start_x=selection_x_1;
	  end_x=selection_x_2;
	}
	else
    {
	  start_x=selection_x_2;
	  end_x=selection_x_1;
	}
    if(selection_y_1<selection_y_2)
    {
	  start_y=selection_y_1;
	  end_y=selection_y_2;
	}
	else
    {
	  start_y=selection_y_2;
	  end_y=selection_y_1;
	}

  if(start_x==0)start_x=1;
  if(start_y==0)start_y=1;
  if(end_x==WIDTH)end_x=WIDTH-1;
  if(end_y==HEIGHT)end_y=HEIGHT-1;

  for (y = start_y; y < end_y; y++)
    for (x = start_x; x < end_x; x++)
    {
      sum = *(terrain_height + y * WIDTH + x);
      sum += *(terrain_height + ((y - 1) * WIDTH) + x - 1);
      sum += *(terrain_height + ((y - 1) * WIDTH) + x);
      sum += *(terrain_height + ((y - 1) * WIDTH) + x + 1);
      sum += *(terrain_height + (y * WIDTH) + x - 1);
      sum += *(terrain_height + (y * WIDTH) + x + 1);
      sum += *(terrain_height + ((y + 1) * WIDTH) + x - 1);
      sum += *(terrain_height + ((y + 1) * WIDTH) + x);
      sum += *(terrain_height + ((y + 1) * WIDTH) + x + 1);

      if(sum%9>4)sum = (sum / 9)+1;
      else sum=sum/9;
      *(terrain_height + y * WIDTH + x) = sum;
    }
	change_cursor(last_cursor);
}

void rise_selection ()
{
  int x, y, start_x,start_y,end_x,end_y,cur_height;
  if (!terrain_height)return;
  change_cursor(cursor_wait);
  copy_to_undo_buffer();
    if(selection_x_1<selection_x_2)
    {
	  start_x=selection_x_1;
	  end_x=selection_x_2;
	}
	else
    {
	  start_x=selection_x_2;
	  end_x=selection_x_1;
	}
    if(selection_y_1<selection_y_2)
    {
	  start_y=selection_y_1;
	  end_y=selection_y_2;
	}
	else
    {
	  start_y=selection_y_2;
	  end_y=selection_y_1;
	}

  for (y = start_y; y < end_y; y++)
    for (x = start_x; x < end_x; x++)
    {
		    if (*(terrain_height + y * WIDTH + x) + color_1 < 255)
		      *(terrain_height + y * WIDTH + x) += color_1;
		    else
		      *(terrain_height + y * WIDTH + x) = 255;
    }
  change_cursor(last_cursor);
}

void sink_selection()
{
  int x, y, start_x,start_y,end_x,end_y,cur_height;
  if (!terrain_height)return;
  change_cursor(cursor_wait);
  copy_to_undo_buffer();
    if(selection_x_1<selection_x_2)
    {
	  start_x=selection_x_1;
	  end_x=selection_x_2;
	}
	else
    {
	  start_x=selection_x_2;
	  end_x=selection_x_1;
	}
    if(selection_y_1<selection_y_2)
    {
	  start_y=selection_y_1;
	  end_y=selection_y_2;
	}
	else
    {
	  start_y=selection_y_2;
	  end_y=selection_y_1;
	}


  for (y = start_y; y < end_y; y++)
    for (x = start_x; x < end_x; x++)
    {
		    if (*(terrain_height + y * WIDTH + x) - color_1 > 0)
		      *(terrain_height + y * WIDTH + x) -= color_1;
		    else
		      *(terrain_height + y * WIDTH + x) = 0;
    }
  change_cursor(last_cursor);
}

void clear_selection ()
{
  int x, y, start_x,start_y,end_x,end_y,cur_height;
  if (!terrain_height)return;
  change_cursor(cursor_wait);
  copy_to_undo_buffer();
    if(selection_x_1<selection_x_2)
    {
	  start_x=selection_x_1;
	  end_x=selection_x_2;
	}
	else
    {
	  start_x=selection_x_2;
	  end_x=selection_x_1;
	}
    if(selection_y_1<selection_y_2)
    {
	  start_y=selection_y_1;
	  end_y=selection_y_2;
	}
	else
    {
	  start_y=selection_y_2;
	  end_y=selection_y_1;
	}

  for (y = start_y; y < end_y; y++)
    for (x = start_x; x < end_x; x++)*(terrain_height + y * WIDTH + x) = color_1;
  change_cursor(last_cursor);
}