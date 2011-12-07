#include "MineDirtBlock.h"
#include "MineBlockType.h"
#include "../MineInclude.h"
#include "../MineEngine.h"
#include "../MineCamera.h"

#include <SDL/SDL.h>

typedef struct __mine_block_dirt DirtBlock;

struct __mine_block_dirt
{
	SDL_Surface *image_grass_top;
};

void _MineBlock_Dirt_Draw( Block *super, Camera *camera )
{
	DirtBlock *self = super->data;
	
	SDL_Surface *image = super->image;
	
	Block *block_above = MineWorld_GetBlock(super->world, super->x, super->y - 1);
	if( NOT block_above )
	{
		image = self->image_grass_top;
	}
	
	SDL_Rect dst;
	dst.x = (super->x * BLOCK_WIDTH) - MineCamera_Left(camera);
	dst.y = (super->y * BLOCK_HEIGHT) - MineCamera_Top(camera);
	dst.w = BLOCK_WIDTH;
	dst.h = BLOCK_HEIGHT;
	
	SDL_BlitSurface(image, NULL, MineEngine_VideoSurface, &dst);
}

Block * MineBlock_Dirt_Create( World *world, unsigned int x, unsigned int y )
{
	Block *super = MineBlock_Create(world, x, y);
	if( super )
	{
		DirtBlock *self = malloc(sizeof(DirtBlock));
		self->image_grass_top = MineEngine_LoadImage("dirt-grass-top.png");
		super->data = self;
		super->type = MINE_BLOCK_TYPE_DIRT;
		super->image = MineEngine_LoadImage("dirt.png");
		super->draw = _MineBlock_Dirt_Draw;
		return super;
	}
	return NULL;
}

int MineBlock_Dirt_SpawnProbability( Block *left, Block *right, Block *top, Block *bottom )
{
	//int probability = 0;
	/*
	FOREACH(neighbor_blocks, Block, block)
		switch( MineBlock_GetType(block) )
		{
			case MINE_BLOCK_TYPE_NONE:
				break;
			case MINE_BLOCK_TYPE_DIRT:
				probability = 80;
				break;
			case MINE_BLOCK_TYPE_STONE:
				if( 40 > probability )
					probability = 40;
				break;
		}
	ENDFOREACH
	*/
	
	/*
	if( MINE_BLOCK_IS(left, MINE_BLOCK_TYPE_DIRT) OR MINE_BLOCK_IS(left, MINE_BLOCK_TYPE_STONE) )
		return 10;
	
	if( NOT MINE_BLOCK_IS(left, MINE_BLOCK_TYPE_NONE) AND (MINE_BLOCK_IS(top, MINE_BLOCK_TYPE_DIRT) OR MINE_BLOCK_IS(top, MINE_BLOCK_TYPE_STONE)) )
		return 10;
	
	if( MINE_BLOCK_IS(left, MINE_BLOCK_TYPE_NONE) )
		return 5;
	*/
	
	return 8;
}

