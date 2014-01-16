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

#include "load_save.h"

#ifdef WINDOWS

#include <windows.h>

#endif

//builds the bmp header
void save_bmp(char * FileName, char * raw_mem, int x_size, int y_size)
{
	int i,x,y,x_padding;
	Uint8 * file_mem;
	Uint8 * file_mem_start;
	FILE *f = NULL;
	int file_lenght;
	x_padding=x_size%4;
	if(x_padding)x_padding=4-x_padding;
	file_lenght=1078+(x_size+x_padding)*y_size;
  	f = fopen (FileName, "wb");
  	if(!f)
  		{
			sprintf(error_msg_1,"Unable to create file!");
			sprintf(error_msg_2,"File already in use, or bad permission!");
			view_error_menu=1;
			return;
		}
	file_mem = (Uint8 *) calloc ( 20000, sizeof(Uint8));
	//clear the header...
	for(i=0;i<1078;i++)*(file_mem+i)=0;

	file_mem_start=file_mem;
	*((short *) file_mem)=19778;//BM (the identifier)
	file_mem+=2;
	*((int *) file_mem)=file_lenght;//file lenght
	file_mem+=8;
	*((int *) file_mem)=1078;//offset of data
	file_mem+=4;
	*((int *) file_mem)=40;//bitmap header lenght
	file_mem+=4;
	*((int *) file_mem)=x_size;//bitmap width
	file_mem+=4;
	*((int *) file_mem)=y_size;//bitmap height
	file_mem+=4;
	*((short *) file_mem)=1;//bitmap planes
	file_mem+=2;
	*((short *) file_mem)=8;//bits / pixel
	file_mem+=26;//ok, now we are at the color pallete (BGRA)
	//now, we need gray shades
	for(i=0;i<256;i++)
		{
			*(file_mem++)=i;//b
			*(file_mem++)=i;//g
			*(file_mem++)=i;//r
			*(file_mem++)=0;//a
		}
	//ok, now, transfer each line from source to destination, in reverse order
	fwrite (file_mem_start, 1078, 1, f);//write the header
	raw_mem+=(y_size-1)*x_size;
	file_mem=file_mem_start;
	for(y=0;y<y_size;y++)
		{
			for(x=0;x<x_size;x++)*(file_mem++)=*(raw_mem++);
			fwrite (file_mem_start, x_size+x_padding, 1, f);
			raw_mem-=x_size*2;//go at the beginning of the previous line
			file_mem=file_mem_start;
		}



fclose (f);
free(file_mem);
}

//////////////////////////////////////////////////////////////////////////////////
bool load_bmp(char * FileName)
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
	x_size=*((int *) file_mem);
	file_mem+=4;
	y_size=*((int *) file_mem);
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

	WIDTH=x_size;
	HEIGHT=y_size;

	  colors_no=*((int *)file_mem);
	  if(!colors_no)colors_no=256;
	  file_mem+=8;//here comes the pallete
	  //if we have a 24 bit bmp, then we don't need the pallete stuff

	  if(is_24b)
	  		{
				allocate_mem();
				if(!terrain_height)return false;
				x_padding=x_size*3%4;
				if(x_padding)x_padding=4-x_padding;

				for(y=y_size-1;y>=0;y--)
					{
						fread (file_mem, 1, x_size*3+x_padding, f);
						//now, get the luminosity of each pixel
						for(x=0;x<x_size;x++)
						{
							current_color=*(file_mem+x*3);
							current_color+=*(file_mem+x*3+1);
							current_color+=*(file_mem+x*3+2);
							*(terrain_height+y*x_size+x)=current_color/3;
						}

					}

				free(file_mem);
				fclose (f);
				return true;
	  		}



	  color_pallete=file_mem+4;
	  fread (file_mem, 1, colors_no*4+4, f);//header only
	  file_mem+=colors_no*4;

	x_padding=x_size%4;
	if(x_padding)x_padding=4-x_padding;

	//now, allocate the memory for the new terrain
	allocate_mem();
	if(!terrain_height)return false;


	for(y=y_size-1;y>=0;y--)
		{
			fread (terrain_height+y*x_size, 1, x_size-x_padding, f);
			//now, get the luminosity of each pixel
			for(x=0;x<x_size;x++)
			{
				current_pallete_entry=*(terrain_height+y*x_size+x);
				current_color=*(color_pallete+current_pallete_entry*4);
				current_color+=*(color_pallete+current_pallete_entry*4+1);
				current_color+=*(color_pallete+current_pallete_entry*4+2);
				*(terrain_height+y*x_size+x)=current_color/3;
			}

		}

	free(file_mem);
	fclose (f);
	return true;
}

void LoadFile (char * FileName)
{
  int i;
  int file_header[25];
  FILE *f = NULL;
  change_cursor(cursor_wait);
//get the file extension
i=0;
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
      load_bmp(FileName);
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
    WIDTH = file_header[0];
    HEIGHT = file_header[1];

	allocate_mem();
	if(!terrain_height)return;

	fread (terrain_height, 1, WIDTH * HEIGHT, f);
	fclose (f);

  }
change_cursor(last_cursor);
}

void SaveFile (char * FileName)
{
  bool is_bmp=0;
  int file_header[25];
  int start_x,start_y,end_x,end_y,x,y,i,j;
  int MapLenght;
  FILE *f = NULL;
if(!terrain_height)return;//we don't have a terrain
change_cursor(cursor_wait);
//get the file extension
i=0;
while(1)
{
	if(*(FileName+i)==0)break;
	i++;
}
i-=3;
if((*(FileName+i)=='B' || *(FileName+i)=='b') &&
(*(FileName+i+1)=='M' || *(FileName+i+1)=='m') &&
(*(FileName+i+2)=='P' || *(FileName+i+2)=='p'))
is_bmp=1;
else
if((*(FileName+i)=='H' || *(FileName+i)=='h') &&
(*(FileName+i+1)=='M' || *(FileName+i+1)=='m') &&
(*(FileName+i+2)=='P' || *(FileName+i+2)=='p'))
is_bmp=0;
else
		{
			sprintf(error_msg_1,"Invalid file format!");
			sprintf(error_msg_2,"Please use only bmp or hmp extensions!");
			view_error_menu=1;
			change_cursor(last_cursor);
			return;
		}

if(is_bmp && selection_x_1==-1)
	{
	  //save the entire map
	  save_bmp(FileName,terrain_height,WIDTH,HEIGHT);
	  change_cursor(last_cursor);
	  return;
	}


	  if(selection_x_1!=-1)
	  	{
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
				MapLenght=(end_x-start_x)*(end_y-start_y);
				file_header[0] = end_x-start_x;
				file_header[1] = end_y-start_y;
				//ok, now move in the temp buffer the selection we want to save
				i=start_y*WIDTH+start_x;
				j=0;
				for(y=start_y;y<end_y;y++)
					{
						for(x=start_x;x<end_x;x++)
							{
								*(temp_buffer+j)=*(terrain_height+i);
								i++;
								j++;
							}
						i+=WIDTH-(end_x-start_x);
					}

	  		if(is_bmp)save_bmp(FileName,temp_buffer,end_x-start_x,end_y-start_y);
			else
			{
				f = fopen (FileName, "wb");
				if(!f)
				{
					sprintf(error_msg_1,"Unable to create file!");
					sprintf(error_msg_2,"File already in use, or bad permission!");
					view_error_menu=1;
					change_cursor(last_cursor);
					return;
				}
				fwrite (file_header, 100, 1, f);
    			fwrite (temp_buffer, MapLenght, 1, f);
    			fclose (f);
			}

    			for(i=0;i<WIDTH*HEIGHT;i++)*temp_buffer=0;
				return;
		}

    MapLenght = WIDTH * HEIGHT;
    file_header[0] = WIDTH;
    file_header[1] = HEIGHT;
	f = fopen (FileName, "wb");
	fwrite (file_header, 100, 1, f);
    fwrite (terrain_height, MapLenght, 1, f);
	fclose (f);
	change_cursor(last_cursor);
}

#ifdef WINDOWS
void
DoFileOpenSave (bool bSave)
{
  OPENFILENAME ofn;
  char szFileName[MAX_PATH];

  ZeroMemory (&ofn, sizeof (ofn));
  szFileName[0] = 0;

  ofn.lStructSize = sizeof (ofn);
  ofn.hwndOwner = 0;
  ofn.lpstrFilter = "Height Map (*.hmp)\0*.hmp\0BMP (*.bmp)\0*.bmp\0\0";
  ofn.lpstrFile = szFileName;
  ofn.nMaxFile = MAX_PATH;
  ofn.lpstrDefExt = "hmp";

  if (bSave)
  {
    ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY |
      OFN_OVERWRITEPROMPT;

    if (GetSaveFileName (&ofn))
    {
      SaveFile (szFileName);
    }
  }
  else
  {
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    if (GetOpenFileName (&ofn))
    {
	  if(load_object==1)do_load_object(szFileName,&current_object);
	  else
	  if(load_object==2)do_load_object(szFileName,&current_pattern);
	  else LoadFile(szFileName);
    }
  }

}

#else

// Not Windows, most probably POSIX
// Not implemented yet x.x

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int ReadDir();
void GetCD();
int ChangeDir(char *path);

int ReadDir()
{
  int d = 0;
  int n;
  int i = 0;
  char *path = cur_dir;
  struct dirent **namelist;
  start_file_offset = 0;

  for( d = 0; d < 1000; d++ )
    {
      sprintf(file_names[d].file_name, "");
      file_names[d].is_directory = 0;
    }

  for ( d = 0; d < 120; d++ )
    sprintf((char*)&cur_file_name[d], "");


  // n will become the number of files in the dir.
  n = scandir(path, &namelist, 0, alphasort);

  if (n < 0) // <- ? No files, if a dir the the files . and .. should exist.
	  {
	    if(namelist)free(namelist);
	    return -1;
      }
  no_of_files=n;

  while(n--)
    {

      struct stat fileinfo;
      stat(namelist[i]->d_name, &fileinfo);
      sprintf(file_names[i].file_name, "%s", (char*)namelist[i]->d_name);

      if ( S_ISDIR(fileinfo.st_mode))  // <- File is a dir
	file_names[i].is_directory = 1;
      else   // <- it's a file
	file_names[i].is_directory = 0;

      free(namelist[n]);
      i++;
    }
  if(namelist)
    free(namelist);
  return 0;
}


void GetCD()
{
  getcwd(cur_dir, 200);
}

int ChangeDir(char *path)
{
  if (chdir(path) == -1)
    return -1;
  GetCD();
  ReadDir();

    return 0;
}

void
DoFileOpenSave (bool bSave)
{
	if (bSave)save_file=1;
	else save_file=0;
	view_file_menu=1;
	sprintf(cur_file_name, "");
	GetCD();
	ReadDir();


}

#endif
