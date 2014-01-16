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
load_cursors()
{
  int f_size,cursors_colors_no,x,y,i;
  FILE *f = NULL;
  Uint8 * cursors_mem_bmp;
  Uint8 *handle_cursors_mem_bmp;
  Uint8 cur_color;
  f = fopen ("cursors.bmp", "rb");
  fseek (f, 0, SEEK_END);
  f_size = ftell (f);
//ok, allocate memory for it
  cursors_mem_bmp = calloc ( f_size, sizeof(char) );
  handle_cursors_mem_bmp=cursors_mem_bmp;
  fseek (f, 0, SEEK_SET);
  fread (cursors_mem_bmp, 1, f_size, f);
  fclose (f);

  cursors_mem_bmp += 18;		//x lenght is at offset+18
  cursors_x_lenght = *((int *) cursors_mem_bmp);
  cursors_mem_bmp += 4;		//y lenght is at offset+22
  cursors_y_lenght = *((int *) cursors_mem_bmp);
  cursors_mem_bmp += 46 - 22;
  cursors_colors_no = *((int *) cursors_mem_bmp);
  cursors_mem_bmp += 54 - 46 + cursors_colors_no * 4;

//ok, now transform the bitmap in cursors info
cursors_mem = calloc ( cursors_x_lenght*cursors_y_lenght*2, sizeof(char));

	for(y=cursors_y_lenght-1;y>=0;y--)
		{
			i=(cursors_y_lenght-y-1)*cursors_x_lenght;
			for(x=0;x<cursors_x_lenght;x++)
			{
			cur_color=*(cursors_mem_bmp+y*cursors_x_lenght+x);
			if(cur_color==0)//transparent
				{
				*(cursors_mem+(i+x)*2)=0;
				*(cursors_mem+(i+x)*2+1)=0;
				}
			else
			if(cur_color==1)//white
				{
				*(cursors_mem+(i+x)*2)=0;
				*(cursors_mem+(i+x)*2+1)=1;
				}
			else
			if(cur_color==2)//black
				{
				*(cursors_mem+(i+x)*2)=1;
				*(cursors_mem+(i+x)*2+1)=1;
				}
			else
			if(cur_color==3)//reverse
				{
				*(cursors_mem+(i+x)*2)=1;
				*(cursors_mem+(i+x)*2+1)=0;
				}
			}

		}
free(handle_cursors_mem_bmp);
}

assign_cursor(int cursor_id)
{
	int hot_x,hot_y,x,y,i,cur_color,cur_byte,cur_bit;
	Uint8 cur_mask;
	Uint8 cursor_data[16*16/8];
	Uint8 cursor_mask[16*16/8];
	Uint8 *cur_cursor_mem;
	//clear the data and mask
	for(i=0;i<16*16/8;i++)cursor_data[i]=0;
	for(i=0;i<16*16/8;i++)cursor_mask[i]=0;

	cur_cursor_mem=calloc(16*16*2, sizeof(char));

	i=0;
	for(y=0;y<cursors_y_lenght;y++)
	for(x=cursor_id*16;x<cursor_id*16+16;x++)
		{
			cur_color=*(cursors_mem+(y*cursors_x_lenght+x)*2);
			*(cur_cursor_mem+i)=cur_color;//data
			cur_color=*(cursors_mem+(y*cursors_x_lenght+x)*2+1);
			*(cur_cursor_mem+i+256)=cur_color;//mask
			i++;
		}
	//ok, now put the data into the bit data and bit mask
	for(i=0;i<16*16;i++)
	{
		cur_color=*(cur_cursor_mem+i);
		cur_byte=i/8;
		cur_bit=i%8;
		if(cur_color)//if it is 0, let it alone, no point in setting it
		  {
			  if(cur_bit==0)cur_mask=128;
			  else if(cur_bit==1)cur_mask=64;
			  else if(cur_bit==2)cur_mask=32;
			  else if(cur_bit==3)cur_mask=16;
			  else if(cur_bit==4)cur_mask=8;
			  else if(cur_bit==5)cur_mask=4;
			  else if(cur_bit==6)cur_mask=2;
			  else if(cur_bit==7)cur_mask=1;
			  cursor_data[cur_byte]|=cur_mask;
		  }

	}
	for(i=0;i<16*16;i++)
	{
		cur_color=*(cur_cursor_mem+i+256);
		cur_byte=i/8;
		cur_bit=i%8;
		if(cur_color)//if it is 0, let it alone, no point in setting it
		  {
			  if(cur_bit==0)cur_mask=128;
			  else if(cur_bit==1)cur_mask=64;
			  else if(cur_bit==2)cur_mask=32;
			  else if(cur_bit==3)cur_mask=16;
			  else if(cur_bit==4)cur_mask=8;
			  else if(cur_bit==5)cur_mask=4;
			  else if(cur_bit==6)cur_mask=2;
			  else if(cur_bit==7)cur_mask=1;
			  cursor_mask[cur_byte]|=cur_mask;
		  }
	}

	hot_x=cursors_array[cursor_id].hot_x;
	hot_y=cursors_array[cursor_id].hot_y;
	cursors_array[cursor_id].cursor_pointer=(Uint8 *)SDL_CreateCursor(cursor_data,cursor_mask,16,16,hot_x,hot_y);
    free(cur_cursor_mem);

}

change_cursor(int cursor_id)
{

	if(current_cursor!=cursor_arrow && current_cursor!=cursor_wait && current_cursor!=cursor_target)last_cursor=current_cursor;
	SDL_SetCursor(cursors_array[cursor_id].cursor_pointer);
	current_cursor=cursor_id;
}

change_cursor_show(int cursor_id)
{

	if(current_cursor!=cursor_arrow && current_cursor!=cursor_wait && current_cursor!=cursor_target)last_cursor=current_cursor;
	SDL_SetCursor(cursors_array[cursor_id].cursor_pointer);
	current_cursor=cursor_id;
	SDL_WarpMouse(x_mouse_pos,y_mouse_pos);
}


