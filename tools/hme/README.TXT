Version 1.2.2

Author: Radu Privantu <chaos_rift@yahoo.com>

Height Map Editor is a free (GPL) program, meant to create and manipulate 8 bit height maps,
usually useful for terrain generators.
Read /man/man.htm to see what it can do.
Currently, it runs under Windows and Linux only, but, being written in SDL, it should be relatively easily
ported to other OSes.
Commenting the  #define WINDOWS part in global.h should make it compile on any OS that supports
SDL, however, it won't work for little endian machines (such as Mac).

The source code is also available, but it is badly written (I am learning C, with this project), 
so try to bear with me :p

The format used (HMP) is very simple, and, starting with version 0.9.0, it can also import/export
BMP files, and, since BMP files can be converted to/from virtually any graphical format, by image viewers/editors,
you can practically use any image format desired.
For a description of the HMP format, please read hmp_format.htm .

CHANGES:

1.3.0
- Added a pseudo isometric preview (nothing VERY impressive, but it's better than nothing)
  Press Tab to switch between standard and isometric view.
- Fixed a small bug, that sometimes caused a crash, when resizing the window to very small
  sizes. Note that the bug that randomly crashes the program when arbitrary resizing the window,
  on Linux, hasn't been fixed yet (need some help on that).


1.2.2
- Fixed a bug that caused the cursor to remain forever in the hourglass shape, whenever the 
  terrain was saved as BMP
- Fixed a bug that caused the program to save the configuration file in the last use directory,
  instead of the home directory.

1.2.0
- Added a "Global Replace" tool, that works exactly like the magic wand, the only exception
  being the fact that, instead of changing only the neighbour heights that match the tolerance
  factor, it changes ALL the heights that match the tolerance factor, on the entire map.
  So, now, you can do things like: Increase all the heights on the map between 0 and 15, with
  20 pixels.

1.1.5
- Improved the "Replace" (Magic Wand) tool, so now it can also add/dig into the terrain,
  and added a Pattern fill mode.

1.1.0
- Added a new tool, the "embed object in terrain" tool. Now, you can customise your terrains
  even more, by adding rivers, craters, mountains, etc. The posibilities are unlimited :)
- Fixed a bug, that didn't change the cursor properly, when the minimap/tool bar/staus bar
  were turned off, and the cusor was on their previous position.

1.0.0
- Cursors, for different tools, so you can't possibly forget you are using the Flood tool.
  and accidentally flood the terrain again :)
- Added tool tips (run the mouse over the tool icons, to see what they do)

0.9.8
- Finally added the UNDO buffer!!! Press ctrl+z for Undo.
- Added the rotation and flip menu, so now you can rotate the map 90 degrees CW/CCW,
  180 degrees, and also flip (invert) the map on x,y, and z (depth).
- Added a nice icon (icon.bmp) to the program.
- Finally made the replace (magic wand) and flood tools non recursive, and they take 
  much less memory than the previous recursive versions, not to mention that, even 
  tho they are a little slower, especially for big maps, they will never stop, until 
  they fill/replace till the last pixel.
- Now it REALLY compiles on Linux, and also fixed a bug, that, sometimes, prevented 
  typing in the file open/save menu.
- Fixed a bug that caused the program to crash, when creating/loading a smaller than
  the current map, and trying to draw on it.
- Fixed a bug that prevented the last bottom line of the map to be displayed.

  
0.9.2
- Full support for Linux, and other Posix compliant OSes 
  (now you can load/save files properly)
- Added error notification, whenever something goes wrong.
- Fixed a bug that crashed the program, when you closed it, on Linux.


0.9.0
- Added the ability to save height maps as BMPs (8 bit, uncompressed)
- Added the ability to load BMPs (8/24 bit, uncompressed)
- Option to display the height map in shades of gray, rather than colors.
- Fixed a few bugs.


0.8.5 Alpha 

- Added the selection tool
- Improved the smooth algorithm, so now it won't progressively sink the map
- Fixed a few relatively minor bugs


--------------------------------------------------------------------
KNOWN BUGS:
None

--------------------------------------------------------------------   
TO DO:
1. Make an option to resize the current existing terrain.
2. Add the ability to rotate/resize the objects you want to embed, in the terrain.
3. Add a 3D view, on the entire terrain.
4. Add more object patterns, such as rivers, craters, explosion holes, volcanos, etc.

--------------------------------------------------------------------
CREDITS:
- Bussman Alexander <zorax@linux.nu> for helping me with the file load/save, on Linux, and other 
  Posix compliant OSes.

- Stefan Hellkvist <stefan@hellkvist.org> for writing sdlplasma (I used/modified some of his code
  for the terrain generation)

- Bloodshed Dev-C++ team, for making the DevC++ IDE.

- Sam Lantinga <slouken@libsdl.org> for SDL, a great library :)

- Juan Soulié <jsoulie@cplusplus.com>, for writing a nice, compressive tutorial on C/C++.   



     
