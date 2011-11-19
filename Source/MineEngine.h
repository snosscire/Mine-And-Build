#ifndef MINE_ENGINE_H
#define MINE_ENGINE_H

#include <SDL/SDL.h>

SDL_Surface *MineEngine_VideoSurface;

char MineEngine_Startup( int screen_width, int screen_height, char full_screen );
void MineEngine_Shutdown();
void MineEngine_ClearScreen();
void MineEngine_UpdateScreen();
int MineEngine_RandomNumber( int min, int max );
#endif /* MINE_ENGINE_H */

