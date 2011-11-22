#ifndef MINE_NONE_BLOCK_H
#define MINE_NONE_BLOCK_H

#include "../MineBlock.h"
#include "../MineList.h"

Block * MineBlock_None_Create( unsigned int x, unsigned int y );
int MineBlock_None_SpawnProbability( List *neighbor_blocks );

#endif /* MINE_NONE_BLOCK_H */
