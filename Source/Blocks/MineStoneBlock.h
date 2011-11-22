#ifndef MINE_STONE_BLOCK_H
#define MINE_STONE_BLOCK_H

#include "../MineBlock.h"
#include "../MineList.h"

Block * MineBlock_Stone_Create( unsigned int x, unsigned int y );
int MineBlock_Stone_SpawnProbability( List *neighbor_blocks );

#endif /* MINE_STONE_BLOCK_H */
