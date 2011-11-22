#include "MineNoneBlock.h"
#include "../MineInclude.h"
#include "../MineEngine.h"

Block * MineBlock_None_Create( unsigned int x, unsigned int y )
{
	Block *super = MineBlock_Create(x, y);
	if( super )
	{
		return super;
	}
	return NULL;
}

int MineBlock_None_SpawnProbability( List *neighbor_blocks )
{
	return 66;
}

