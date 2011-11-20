#include "MineStoneBlock.h"
#include "../MineInclude.h"
#include "../MineEngine.h"

Block * MineBlock_Stone_Create()
{
	Block *super = MineBlock_Create();
	if( super )
	{
		super->image = MineEngine_LoadImage("stone.png");
		super->draw = _MineBlock_DefaultDraw;
		return super;
	}
	return NULL;
}

int MineBlock_Stone_SpawnProbability( Block **neighbor_blocks )
{
	return 33;
}

