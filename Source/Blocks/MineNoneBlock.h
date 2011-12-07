#ifndef MINE_NONE_BLOCK_H
#define MINE_NONE_BLOCK_H

#include "../MineBlock.h"
#include "../MineWorld.h"
#include "../MineList.h"

Block * MineBlock_None_Create( World *world, unsigned int x, unsigned int y );
int MineBlock_None_SpawnProbability( Block *left, Block *right, Block *top, Block *bottom );

#endif /* MINE_NONE_BLOCK_H */
