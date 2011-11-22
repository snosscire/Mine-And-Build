#ifndef MINE_DIRT_BLOCK_H
#define MINE_DIRT_BLOCK_H

#include "../MineBlock.h"
#include "../MineList.h"

Block * MineBlock_Dirt_Create( unsigned int x, unsigned int y );
int MineBlock_Dirt_SpawnProbability( List *neighbor_blocks );

#endif /* MINE_DIRT_BLOCK_H */
