#ifndef MINE_BLOCK_H
#define MINE_BLOCK_H

#include "MineCamera.h"
#include <SDL/SDL.h>

#define BLOCK_WIDTH 16
#define BLOCK_HEIGHT 16

typedef struct __mine_block Block;

struct __mine_block
{
	unsigned int x;
	unsigned int y;
	SDL_Surface *image;
	void (*destroy)(Block*);
	void (*update)(Block*);
	void (*draw)(Block*,Camera*);
	void *data;
};

Block * MineBlock_Create();
void MineBlock_Destroy( Block *self );
void MineBlock_Update( Block *self );
void MineBlock_Draw( Block *self, Camera *camera );
void MineBlock_SetX( Block *self, unsigned int x );
void MineBlock_SetY( Block *self, unsigned int y );

void _MineBlock_DefaultDraw( Block *self, Camera *camera );

#endif /* MINE_BLOCK_H */
