#include "MineNoneBlock.h"
#include "../MineInclude.h"
#include "../MineEngine.h"

Block * MineBlock_None_Create()
{
	Block *super = MineBlock_Create();
	if( super )
	{
		return super;
	}
	return NULL;
}

int MineBlock_None_SpawnProbability( Block **neighbor_blocks )
{
	return 66;
}

