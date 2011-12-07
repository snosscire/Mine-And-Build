#ifndef MINE_DIRT_BLOCK_H
#define MINE_DIRT_BLOCK_H

#include "../MineBlock.h"
#include "../MineWorld.h"
#include "../MineList.h"

Block * MineBlock_Dirt_Create( World *world, unsigned int x, unsigned int y );
int MineBlock_Dirt_SpawnProbability( Block *left, Block *right, Block *top, Block *bottom );

#endif /* MINE_DIRT_BLOCK_H */
