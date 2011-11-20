#include "MineInclude.h"
#include "MineEngine.h"
#include "MineEvent.h"
#include "MineList.h"

#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <SDL/SDL_image.h>

typedef struct __mine_engine_loaded_image LoadedImage;

struct __mine_engine_loaded_image
{
	const char *filename;
	SDL_Surface *surface;
};

List *MineEngine_LoadedImages = NULL;

void _MineEngine_DestroyLoadedImage( void *data )
{
	LoadedImage *image = data;
	SDL_FreeSurface(image->surface);
	free(image);
}

LoadedImage * _MineEngine_FindLoadedImageByFilename( const char *filename )
{
	FOREACH(MineEngine_LoadedImages, LoadedImage, image)
		if( strcmp(image->filename, filename) == 0 ) {
			return image;
		}
	ENDFOREACH
	return NULL;
}

char MineEngine_Startup( int screen_width, int screen_height, char full_screen )
{
	Uint32 flags = 0;
	
	if( SDL_Init(SDL_INIT_VIDEO) == -1 )
	{
		return FALSE;
	}
	
	flags |= SDL_HWPALETTE;
	flags |= SDL_HWSURFACE;
	flags |= SDL_HWACCEL;
	flags |= SDL_DOUBLEBUF;
	
	if( full_screen )
	{
		flags |= SDL_FULLSCREEN;
	}
	
	MineEngine_VideoSurface = SDL_SetVideoMode(screen_width, screen_height, 0, flags);
	if( NOT MineEngine_VideoSurface )
	{
		SDL_Quit();
		return FALSE;
	}
	
	MineEngine_LoadedImages = MineList_Create( _MineEngine_DestroyLoadedImage);
	if( NOT MineEngine_LoadedImages )
	{
		SDL_Quit();
		return FALSE;
	}
	
	MineEvent_Startup();
	
	srand(time(NULL));
	
	return TRUE;
}

void MineEngine_Shutdown()
{
	MineList_Destroy(MineEngine_LoadedImages);
	MineEvent_Shutdown();
	
	SDL_Quit();
}

void MineEngine_ClearScreen()
{
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = MineEngine_VideoSurface->w;
	rect.h = MineEngine_VideoSurface->h;
	SDL_FillRect(MineEngine_VideoSurface, &rect, SDL_MapRGB(MineEngine_VideoSurface->format, 0, 0, 0));
}

void MineEngine_UpdateScreen()
{
	SDL_Flip(MineEngine_VideoSurface);
}

int MineEngine_ScreenWidth()
{
	return MineEngine_VideoSurface->w;
}

int MineEngine_ScreenHeight()
{
	return MineEngine_VideoSurface->h;
}


int MineEngine_RandomNumber( int min, int max )
{
	return (rand() % (max - min + 1) + min);
}

SDL_Surface * MineEngine_LoadImage( const char *filename )
{
	LoadedImage *image = _MineEngine_FindLoadedImageByFilename(filename);
	if( NOT image )
	{
		SDL_Surface *surface = IMG_Load(filename);
		printf("Loading: %s\n", filename);
		if( NOT surface )
		{
			printf("Not Found!\n");
			return NULL;
		}
		image = malloc(sizeof(LoadedImage));
		if( NOT image )
		{
			SDL_FreeSurface(surface);
			return NULL;
		}
		image->filename = filename;
		image->surface = surface;
		MineList_Append(MineEngine_LoadedImages, image);
	}
	return image->surface;
}

