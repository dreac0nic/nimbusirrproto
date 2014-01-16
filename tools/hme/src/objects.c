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

#include "objects.h"
#include <SDL/SDL_events.h>


void pre_load_object()
{
	SDL_Event event;
	if(!current_object.object_mem)
	{
		load_object=1;//tell the file open save function to load an object, not a terrain
		DoFileOpenSave (0);
    	while (SDL_PollEvent (&event));	//clears all the events
	}
}


void draw_object_on_screen(SDL_Surface * this_screen)
{
	  int my_pitch;
	  int object_x_start,object_y_start;
	  int object_x_end,object_y_end;
	  int object_x_screen_start,object_y_screen_start;
	  int object_x_screen_end,object_y_screen_end;
	  int object_x_terrain_start,object_y_terrain_start;
	  int object_x_terrain_end,object_y_terrain_end;

	  int x,y,i,j,k,l;

	  int cur_height;
	  Uint8 * start_display_pointer;
	  Uint8 * start_object_pointer;

	  Uint8 *screen_buffer;
	  screen_buffer = (Uint8 *) this_screen->pixels;
  	  my_pitch = this_screen->pitch;

    	  //first, check to see if we really have the object
    	  //if we don't have it, it means that the user tried to load an invalid file
    	  //or he pressed the cancel button.

  	  if(!current_object.object_mem)
  	  {
  		  int i;
  		  current_object.object_mem=0;
  		  //change the tool to the draw tool
  		  current_tool=t_place;
  		  for(i=0;i<no_of_main_tool_bar_icons;i++)main_tool_bar[i].icon_active = 0;
  		  main_tool_bar[0].icon_active = 1;
  		  change_cursor_show(cursor_put);
  		  return;
  	  }

	  //ok, first, get the object screen x/y, according to the zoom level (if any)
	  object_x_screen_start=x_mouse_pos-(current_object.object_x_len/2*terrain_ratio);
	  object_y_screen_start=y_mouse_pos-(current_object.object_y_len/2*terrain_ratio);
	  object_x_screen_end=x_mouse_pos+(current_object.object_x_len/2*terrain_ratio);
	  object_y_screen_end=y_mouse_pos+(current_object.object_y_len/2*terrain_ratio);
	  //now, find out which part of the object we display (if it is outside of the screen)
	  //the start part
	  if(object_x_screen_start>0)object_x_start=0;
	  else object_x_start=(object_x_screen_start*-1)/terrain_ratio;
	  if(object_y_screen_start>0)object_y_start=0;
	  else object_y_start=(object_y_screen_start*-1)/terrain_ratio;
	  //end part
	  if(object_x_screen_end<window_width)object_x_end=current_object.object_x_len;
	  else object_x_end=current_object.object_x_len-((object_x_screen_end-window_width)/terrain_ratio);
	  if(object_y_screen_end<window_height)object_y_end=current_object.object_y_len;
	  else object_y_end=current_object.object_y_len-((object_y_screen_end-window_height)/terrain_ratio);
	  //do some final adjustments
	  if(object_x_screen_start<0)object_x_screen_start=0;
	  if(object_y_screen_start<0)object_y_screen_start=0;

	  //now, do get the terrain coordinates.
	  object_x_terrain_start=((x_mouse_pos-x_screen_offset)-(current_object.object_x_len/2*terrain_ratio))/ terrain_ratio + xoffset;
	  object_y_terrain_start=((y_mouse_pos-y_screen_offset)-(current_object.object_y_len/2*terrain_ratio))/ terrain_ratio + yoffset;
	  object_x_terrain_end=((x_mouse_pos-x_screen_offset)+(current_object.object_x_len/2*terrain_ratio))/ terrain_ratio + xoffset;
	  object_y_terrain_end=((y_mouse_pos-y_screen_offset)+(current_object.object_y_len/2*terrain_ratio))/ terrain_ratio + yoffset;
  if(terrain_ratio==1)
  {
	  //ok, now just display the object
	  if(object_mode==put_object)
	  {
	  	i=0;
	  	k=object_y_terrain_start+object_y_start;
	  	for(y=object_y_start;y<object_y_end;y++)
	  		{
	  			start_object_pointer=current_object.object_mem+y*current_object.object_x_len;
	  			start_display_pointer=screen_buffer+(object_y_screen_start+i)*my_pitch;
	  			j=object_x_screen_start;
	  			l=object_x_terrain_start+object_x_start;
	  			for(x=object_x_start;x<object_x_end;x++)
	  				{
						cur_height=*(start_object_pointer+x);
						if(cur_height && l>=0 && l<WIDTH && k>=0 && k<HEIGHT)
							{
	  							*(start_display_pointer+j)=cur_height/4;
							}
					    j++;
					    l++;

					}
	  			i++;
	  			k++;
			}
	  return;
	  }//ok, end of place_mode
	  else
	  if(object_mode==add_object)
	  {
	  	i=0;
	  	k=object_y_terrain_start+object_y_start;
	  	for(y=object_y_start;y<object_y_end;y++)
	  		{
	  			start_object_pointer=current_object.object_mem+y*current_object.object_x_len;
	  			start_display_pointer=screen_buffer+(object_y_screen_start+i)*my_pitch;
	  			j=object_x_screen_start;
	  			l=object_x_terrain_start+object_x_start;
	  			for(x=object_x_start;x<object_x_end;x++)
	  				{
						cur_height=*(start_object_pointer+x);
						if(cur_height && l>=0 && l<WIDTH && k>=0 && k<HEIGHT)
							{
	  							cur_height+=*(terrain_height+k*WIDTH+l);
	  							if(cur_height>255)cur_height=255;
	  							*(start_display_pointer+j)=cur_height/4;
							}
					    j++;
					    l++;

					}
	  			i++;
	  			k++;
			}
	  return;
	  }//ok, end of add_mode
	  else
	  if(object_mode==sub_object)
	  {
	  	i=0;
	  	k=object_y_terrain_start+object_y_start;
	  	for(y=object_y_start;y<object_y_end;y++)
	  		{
	  			start_object_pointer=current_object.object_mem+y*current_object.object_x_len;
	  			start_display_pointer=screen_buffer+(object_y_screen_start+i)*my_pitch;
	  			j=object_x_screen_start;
	  			l=object_x_terrain_start+object_x_start;
	  			for(x=object_x_start;x<object_x_end;x++)
	  				{
						cur_height=*(start_object_pointer+x);
						if(cur_height && l>=0 && l<WIDTH && k>=0 && k<HEIGHT)
							{
	  							cur_height=*(terrain_height+k*WIDTH+l)-cur_height;
	  							if(cur_height<0)*(start_display_pointer+j)=black;
	  							else *(start_display_pointer+j)=cur_height/4;
							}
					    j++;
					    l++;

					}
	  			i++;
	  			k++;
			}
	  }//ok, end of sub_mode
  }
  else //the terain is zoomed in, use other routines, for better optimization
  {
	  int screen_size=window_height*my_pitch;
	  int screen_offset_int_pointer;
	  //ok, now just display the object
	  if(object_mode==put_object)
	  {
	  	i=0;
	  	k=object_y_terrain_start+object_y_start;
	  	for(y=object_y_start;y<object_y_end;y++)
	  		{
	  			start_object_pointer=current_object.object_mem+y*current_object.object_x_len;
	  			start_display_pointer=screen_buffer+(object_y_screen_start+i*terrain_ratio)*my_pitch;
	  			screen_offset_int_pointer=(object_y_screen_start+i*terrain_ratio)*my_pitch;
	  			j=object_x_screen_start;
	  			l=object_x_terrain_start+object_x_start;
	  			for(x=object_x_start;x<object_x_end;x++)
	  				{
						cur_height=*(start_object_pointer+x);
						if(cur_height && l>=0 && l<WIDTH && k>=0 && k<HEIGHT)
							{
								int m,n,another_displacement;
								cur_height/=4;
								for(m=0;m<terrain_ratio;m++)
								for(n=0;n<terrain_ratio;n++)
									{
										another_displacement=m*my_pitch+n;
	  									if(screen_offset_int_pointer+j+another_displacement<screen_size)*(start_display_pointer+j+another_displacement)=cur_height;
									}
							}
					    j+=terrain_ratio;
					    l++;

					}
	  			i++;
	  			k++;
			}
	  return;
	  }//ok, end of place_mode
	  else
	  if(object_mode==add_object)
	  {
	  	i=0;
	  	k=object_y_terrain_start+object_y_start;
	  	for(y=object_y_start;y<object_y_end;y++)
	  		{
	  			start_object_pointer=current_object.object_mem+y*current_object.object_x_len;
	  			start_display_pointer=screen_buffer+(object_y_screen_start+i*terrain_ratio)*my_pitch;
	  			screen_offset_int_pointer=(object_y_screen_start+i*terrain_ratio)*my_pitch;
	  			j=object_x_screen_start;
	  			l=object_x_terrain_start+object_x_start;
	  			for(x=object_x_start;x<object_x_end;x++)
	  				{
						cur_height=*(start_object_pointer+x);
						if(cur_height && l>=0 && l<WIDTH && k>=0 && k<HEIGHT)
							{
								int m,n,another_displacement;
	  							cur_height+=*(terrain_height+k*WIDTH+l);
	  							if(cur_height>255)cur_height=255;

								cur_height/=4;
								for(m=0;m<terrain_ratio;m++)
								for(n=0;n<terrain_ratio;n++)
									{
										another_displacement=m*my_pitch+n;
	  									if(screen_offset_int_pointer+j+another_displacement<screen_size)*(start_display_pointer+j+another_displacement)=cur_height;
									}
							}
					    j+=terrain_ratio;
					    l++;

					}
	  			i++;
	  			k++;
			}
	  return;
	  }//ok, end of add_mode
	  else
	  if(object_mode==sub_object)
	  		{
			  i=0;
			  k=object_y_terrain_start+object_y_start;
			  for(y=object_y_start;y<object_y_end;y++)
			  {
	  			start_object_pointer=current_object.object_mem+y*current_object.object_x_len;
	  			start_display_pointer=screen_buffer+(object_y_screen_start+i*terrain_ratio)*my_pitch;
	  			screen_offset_int_pointer=(object_y_screen_start+i*terrain_ratio)*my_pitch;
	  			j=object_x_screen_start;
	  			l=object_x_terrain_start+object_x_start;
	  			for(x=object_x_start;x<object_x_end;x++)
	  				{
						cur_height=*(start_object_pointer+x);
						if(cur_height && l>=0 && l<WIDTH && k>=0 && k<HEIGHT)
							{
								int m,n,another_displacement;
	  							cur_height=*(terrain_height+k*WIDTH+l)-cur_height;
	  							if(cur_height<0)cur_height=black;
	  							else cur_height/=4;
								for(m=0;m<terrain_ratio;m++)
								for(n=0;n<terrain_ratio;n++)
									{
										another_displacement=m*my_pitch+n;
	  									if(screen_offset_int_pointer+j+another_displacement<screen_size)*(start_display_pointer+j+another_displacement)=cur_height;
									}
							}
					    j+=terrain_ratio;
					    l++;

					}
	  			i++;
	  			k++;
			}
	  }//ok, end of sub_mode

  }//end of the zoomed in terrain display

}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
void do_load_object(char * FileName, terrain_object *this_current_object)
{
  int i;
  int file_header[25];
  FILE *f = NULL;
i=0;
//get the file name, if it is a pattern
	if(load_object==2)
	{
		sprintf(pattern_file_name, FileName);
	}

//get the file extension
while(1)
{
	if(*(FileName+i)==0)break;
	i++;
}
i-=3;
if((*(FileName+i)=='B' || *(FileName+i)=='b') &&
(*(FileName+i+1)=='M' || *(FileName+i+1)=='m') &&
(*(FileName+i+2)=='P' || *(FileName+i+2)=='p'))
	{
      load_bmp_object(FileName,this_current_object);
	  return;
	}
else
if((*(FileName+i)=='H' || *(FileName+i)=='h') &&
(*(FileName+i+1)=='M' || *(FileName+i+1)=='m') &&
(*(FileName+i+2)=='P' || *(FileName+i+2)=='p'))
i=0;
else
		{
			sprintf(error_msg_1,"Invalid file format!");
			sprintf(error_msg_2,"Please use only bmp or hmp extensions!");
			view_error_menu=1;
			return;
		}

  f = fopen (FileName, "rb");
  if (f)
  {
    fread (file_header, 1, 100, f);
    this_current_object->object_x_len = file_header[0];
    this_current_object->object_y_len = file_header[1];

	this_current_object->object_mem=(Uint8 *)calloc ( this_current_object->object_x_len*this_current_object->object_y_len, sizeof(Uint8));
	if(!this_current_object->object_mem)return;

	fread (this_current_object->object_mem, 1, this_current_object->object_x_len * this_current_object->object_y_len, f);
	fclose (f);

  }
}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
bool load_bmp_object(char * FileName, terrain_object *this_current_object)
{
	int i,x,y,x_padding,x_size,y_size,colors_no,current_color,current_pallete_entry;
	Uint8 * file_mem;
	Uint8 * file_mem_start;
	Uint8 * color_pallete;
	bool is_24b=0;
	FILE *f = NULL;
	int file_lenght;

  	f = fopen (FileName, "rb");
  	if (!f)
  		{
			sprintf(error_msg_1,"Unable to open file!");
			sprintf(error_msg_2,"File doesn't exist, or bad permission!");
			view_error_menu=1;
  			return false;//something went wrong
		}
  	file_mem = (Uint8 *) calloc ( 20000, sizeof(Uint8));
  	fread (file_mem, 1, 50, f);//header only
  	//now, check to see if our bmp file is indeed a bmp file, and if it is 8 bits, uncompressed
  	if(*((short *) file_mem)!=19778)//BM (the identifier)
  	{
		free(file_mem);
		fclose (f);
			sprintf(error_msg_1,"Unsuported BMP format!");
			sprintf(error_msg_2,"BMP files have to be 8 or 24b, uncompressed!");
			view_error_menu=1;
		return false;
	}
	file_mem+=18;
	this_current_object->object_x_len=*((int *) file_mem);
	file_mem+=4;
	this_current_object->object_y_len=*((int *) file_mem);
	file_mem+=6;
	if(*((short *)file_mem)!=8)//8 bit/pixel?
	if(*((short *)file_mem)!=24)
	  {
		free(file_mem);
		fclose (f);
			sprintf(error_msg_1,"Unsuported BMP format!");
			sprintf(error_msg_2,"BMP files have to be 8 or 24b, uncompressed!");
			view_error_menu=1;
		return false;
	  }
	  else is_24b=true;
	file_mem+=2;
	if(*((int *)file_mem)!=0)//any compression?
	  {
		free(file_mem);
		fclose (f);
			sprintf(error_msg_1,"Unsuported BMP format!");
			sprintf(error_msg_2,"BMP files have to be 8 or 24b, uncompressed!");
			view_error_menu=1;
		return false;
	  }
	  file_mem+=16;

	  colors_no=*((int *)file_mem);
	  if(!colors_no)colors_no=256;
	  file_mem+=8;//here comes the pallete
	  //if we have a 24 bit bmp, then we don't need the pallete stuff

	  if(is_24b)
	  		{
				this_current_object->object_mem=(Uint8 *)calloc ( this_current_object->object_x_len*this_current_object->object_y_len, sizeof(Uint8));
				if(!this_current_object->object_mem)
						  {
								free(file_mem);
								fclose (f);
								sprintf(error_msg_1,"Not enough memory!");
								sprintf(error_msg_2,"Choose a smaller object!");
								view_error_menu=1;
								return false;
						  }

				x_padding=this_current_object->object_x_len*3%4;
				if(x_padding)x_padding=4-x_padding;

				for(y=this_current_object->object_y_len-1;y>=0;y--)
					{
						fread (file_mem, 1, this_current_object->object_x_len*3+x_padding, f);
						//now, get the luminosity of each pixel
						for(x=0;x<this_current_object->object_x_len;x++)
						{
							current_color=*(file_mem+x*3);
							current_color+=*(file_mem+x*3+1);
							current_color+=*(file_mem+x*3+2);
							*(this_current_object->object_mem+y*this_current_object->object_x_len+x)=current_color/3;
						}

					}

				free(file_mem);
				fclose (f);
				return true;
	  		}



	  color_pallete=file_mem+4;
	  fread (file_mem, 1, colors_no*4+4, f);//header only
	  file_mem+=colors_no*4;

	x_padding=this_current_object->object_x_len%4;
	if(x_padding)x_padding=4-x_padding;

	//now, allocate the memory for the new terrain
	this_current_object->object_mem=(Uint8 *)calloc ( this_current_object->object_x_len*this_current_object->object_y_len, sizeof(Uint8));
	if(!this_current_object->object_mem)
		  {
				free(file_mem);
				fclose (f);
				sprintf(error_msg_1,"Not enough memory!");
				sprintf(error_msg_2,"Choose a smaller object!");
				view_error_menu=1;
				return false;
		  }



	for(y=this_current_object->object_y_len-1;y>=0;y--)
		{
			fread (this_current_object->object_mem+y*this_current_object->object_x_len, 1, this_current_object->object_x_len-x_padding, f);
			//now, get the luminosity of each pixel
			for(x=0;x<this_current_object->object_x_len;x++)
			{
				current_pallete_entry=*(this_current_object->object_mem+y*this_current_object->object_x_len+x);
				current_color=*(color_pallete+current_pallete_entry*4);
				current_color+=*(color_pallete+current_pallete_entry*4+1);
				current_color+=*(color_pallete+current_pallete_entry*4+2);
				*(this_current_object->object_mem+y*this_current_object->object_x_len+x)=current_color/3;
			}

		}

	free(file_mem);
	fclose (f);
	return true;
}