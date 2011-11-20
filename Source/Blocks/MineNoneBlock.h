#ifndef MINE_NONE_BLOCK_H
#define MINE_NONE_BLOCK_H

#include "../MineBlock.h"

Block * MineBlock_None_Create();
int MineBlock_None_SpawnProbability( Block **neighbor_blocks );

#endif /* MINE_NONE_BLOCK_H */
