#ifndef MINE_STONE_BLOCK_H
#define MINE_STONE_BLOCK_H

#include "../MineBlock.h"
#include "../MineWorld.h"
#include "../MineList.h"

Block * MineBlock_Stone_Create( World *world, unsigned int x, unsigned int y );
int MineBlock_Stone_SpawnProbability( Block *left, Block *right, Block *top, Block *bottom );

#endif /* MINE_STONE_BLOCK_H */
