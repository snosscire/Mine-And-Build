#ifndef MINE_DIRT_BLOCK_H
#define MINE_DIRT_BLOCK_H

#include "../MineBlock.h"

Block * MineBlock_Dirt_Create();
int MineBlock_Dirt_SpawnProbability( Block **neighbor_blocks );

#endif /* MINE_DIRT_BLOCK_H */
