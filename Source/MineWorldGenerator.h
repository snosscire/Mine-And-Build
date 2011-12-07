#ifndef MINE_WORLD_GENERATOR_H
#define MINE_WORLD_GENERATOR_H

#include "Blocks/MineBlockType.h"
#include "MineBlock.h"
#include "MineWorld.h"
#include "MineList.h"

void MineWorldGenerator_Startup();
void MineWorldGenerator_Shutdown();
void MineWorldGenerator_RegisterBlocks();
void MineWorldGenerator_RegisterBlock( BlockType type, Block * (*create)(World*,unsigned int,unsigned int), int (*spawn_probability)(Block*,Block*,Block*,Block*) );
World * MineWorldGenerator_CreateWorld( unsigned int width, unsigned int height );

#endif /* MINE_WORLD_GENERATOR */
