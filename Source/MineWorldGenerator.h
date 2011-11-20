#ifndef MINE_WORLD_GENERATOR_H
#define MINE_WORLD_GENERATOR_H

#include "Blocks/MineBlockType.h"
#include "MineBlock.h"
#include "MineWorld.h"

void MineWorldGenerator_RegisterBlocks();
void MineWorldGenerator_RegisterBlock( BlockType type, Block * (*create)(), int (*spawn_probability)(Block **) );
World * MineWorldGenerator_CreateWorld( unsigned int width, unsigned int height );

#endif /* MINE_WORLD_GENERATOR */
