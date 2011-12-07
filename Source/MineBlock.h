#ifndef MINE_BLOCK_H
#define MINE_BLOCK_H

#include "Blocks/MineBlockType.h"
#include "MineCamera.h"
#include <SDL/SDL.h>

#define BLOCK_WIDTH 16
#define BLOCK_HEIGHT 16

typedef struct __mine_block Block;

struct __mine_world;

struct __mine_block
{
	BlockType type;
	unsigned int x;
	unsigned int y;
	SDL_Surface *image;
	void (*destroy)(Block*);
	void (*update)(Block*);
	void (*draw)(Block*,Camera*);
	void *data;
	struct __mine_world *world;
};


Block * MineBlock_Create( struct __mine_world *world, unsigned int x, unsigned int y );
void MineBlock_Destroy( Block *self );
void MineBlock_Update( Block *self );
void MineBlock_Draw( Block *self, Camera *camera );
void MineBlock_SetX( Block *self, unsigned int x );
void MineBlock_SetY( Block *self, unsigned int y );
BlockType MineBlock_GetType( Block *self );

void _MineBlock_DefaultDraw( Block *self, Camera *camera );

#define MINE_BLOCK_IS(BLOCK, TYPE) \
	(BLOCK AND MineBlock_GetType(BLOCK) == TYPE)

#endif /* MINE_BLOCK_H */
