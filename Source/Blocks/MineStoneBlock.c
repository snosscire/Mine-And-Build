#include "MineStoneBlock.h"
#include "MineBlockType.h"
#include "../MineInclude.h"
#include "../MineEngine.h"

Block * MineBlock_Stone_Create( World *world, unsigned int x, unsigned int y )
{
	Block *super = MineBlock_Create(world, x, y);
	if( super )
	{
		super->type = MINE_BLOCK_TYPE_STONE;
		super->image = MineEngine_LoadImage("stone.png");
		super->draw = _MineBlock_DefaultDraw;
		return super;
	}
	return NULL;
}

int MineBlock_Stone_SpawnProbability( Block *left, Block *right, Block *top, Block *bottom )
{
	int probability = 0;
	/*
	FOREACH(neighbor_blocks, Block, block)
		switch( MineBlock_GetType(block) )
		{
			case MINE_BLOCK_TYPE_NONE:
				break;
			case MINE_BLOCK_TYPE_DIRT:
				if( 40 > probability )
					probability = 40;
				break;
			case MINE_BLOCK_TYPE_STONE:
				probability = 80;
				break;
		}
	ENDFOREACH
	*/
	return 4;
}

