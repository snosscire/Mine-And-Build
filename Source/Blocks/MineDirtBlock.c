#include "MineDirtBlock.h"
#include "../MineInclude.h"
#include "../MineEngine.h"

/*
#include <SDL/SDL.h>

typedef struct __mine_block_dirt DirtBlock;

struct __mine_block_dirt
{
	SDL_Surface *grass_top_image;
};
*/

Block * MineBlock_Dirt_Create()
{
	Block *super = MineBlock_Create();
	if( super )
	{
		super->image = MineEngine_LoadImage("dirt.png");
		super->draw = _MineBlock_DefaultDraw;
		return super;
	}
	return NULL;
}

int MineBlock_Dirt_SpawnProbability( Block **neighbor_blocks )
{
	return 33;
}

