#include "MineStoneBlock.h"
#include "../MineInclude.h"
#include "../MineEngine.h"

Block * MineBlock_Stone_Create( unsigned int x, unsigned int y )
{
	Block *super = MineBlock_Create(x, y);
	if( super )
	{
		super->image = MineEngine_LoadImage("stone.png");
		super->draw = _MineBlock_DefaultDraw;
		return super;
	}
	return NULL;
}

int MineBlock_Stone_SpawnProbability( List *neighbor_blocks )
{
	return 33;
}

