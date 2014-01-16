#ifndef __LOAD_SAVE_H__
#define __LOAD_SAVE_H__

#include "global.h"

void SaveFile (char * FileName);
void LoadFile (char * FileName);
bool load_bmp(char * FileName);
void save_bmp(char * FileName, char * raw_mem, int x_size, int y_size);
void DoFileOpenSave (bool bSave);

#endif
