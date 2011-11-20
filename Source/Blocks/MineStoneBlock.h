#ifndef MINE_STONE_BLOCK_H
#define MINE_STONE_BLOCK_H

#include "../MineBlock.h"

Block * MineBlock_Stone_Create();
int MineBlock_Stone_SpawnProbability( Block **neighbor_blocks );

#endif /* MINE_STONE_BLOCK_H */
