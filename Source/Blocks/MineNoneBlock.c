#include "MineNoneBlock.h"
#include "MineBlockType.h"
#include "../MineInclude.h"
#include "../MineEngine.h"

Block * MineBlock_None_Create( World *world, unsigned int x, unsigned int y )
{
	Block *super = MineBlock_Create(world, x, y);
	if( super )
	{
		super->type = MINE_BLOCK_TYPE_NONE;
		return super;
	}
	return NULL;
}

int MineBlock_None_SpawnProbability( Block *left, Block *right, Block *top, Block *bottom )
{
	//int probability = 0;
	/*
	FOREACH(neighbor_blocks, Block, block)
		switch( MineBlock_GetType(block) )
		{
			case MINE_BLOCK_TYPE_NONE:
				probability = 80;
				break;
			case MINE_BLOCK_TYPE_DIRT:
				probability = 10;
				break;
			case MINE_BLOCK_TYPE_STONE:
				probability = 10;
				break;
		}
	ENDFOREACH
	*/
	
	if( MINE_BLOCK_IS(left, MINE_BLOCK_TYPE_NONE) )
		return 10;
	
	if( MINE_BLOCK_IS(top, MINE_BLOCK_TYPE_NONE) )
		return 5;
	
	return 0;
}

