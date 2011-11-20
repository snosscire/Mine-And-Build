#include "MineInclude.h"
#include "MineWorldGenerator.h"
#include "MineList.h"
#include "MineEngine.h"
#include "Blocks/MineNoneBlock.h"
#include "Blocks/MineDirtBlock.h"
#include "Blocks/MineStoneBlock.h"

typedef struct __mine_world_generator_registered_block RegisteredBlock;

struct __mine_world_generator_registered_block
{
	BlockType type;
	Block * (*create)();
	int (*spawn_probability)(Block **);
};

List *MineWorldGenerator_RegisteredBlocks = NULL;

void MineWorldGenerator_Startup()
{
	MineWorldGenerator_RegisteredBlocks = MineList_Create(NULL);
}

void MineWorldGenerator_Shutdown()
{
	MineList_Destroy(MineWorldGenerator_RegisteredBlocks);
}

void MineWorldGenerator_RegisterBlocks()
{
	MineWorldGenerator_RegisterBlock(MINE_BLOCK_TYPE_NONE, MineBlock_None_Create, MineBlock_None_SpawnProbability);
	MineWorldGenerator_RegisterBlock(MINE_BLOCK_TYPE_DIRT, MineBlock_Dirt_Create, MineBlock_Dirt_SpawnProbability);
	MineWorldGenerator_RegisterBlock(MINE_BLOCK_TYPE_STONE, MineBlock_Stone_Create, MineBlock_Stone_SpawnProbability);
}

void MineWorldGenerator_RegisterBlock( BlockType type, Block * (*create)(), int (*spawn_probability)(Block **) )
{
	RegisteredBlock *block = malloc(sizeof(RegisteredBlock));
	if( block )
	{
		block->type = type;
		block->create = create;
		block->spawn_probability = spawn_probability;
		
		MineList_Append(MineWorldGenerator_RegisteredBlocks, block);
	}
}

World * MineWorldGenerator_CreateWorld( unsigned int width, unsigned int height )
{
	World *world = MineWorld_Create(width, height);
	if( world )
	{
		/* World generation starts with the placing on one dirt block.
		 * This is the seed that will create the whole world.
		 */
		int limit_up = MineWorld_GetHeight(world) * 0.75;
		int limit_down = MineWorld_GetHeight(world) * 0.25;
		
		int x = 0;
		int y = Engine_RandomNumber(limit_down, limit_up);
		
		MineWorld_SetBlock(world, x, y, MineBlock_Dirt_Create());
		
		/* Next we are going to go through each position in the world and ask
		 * what the probability of a block spawning is based on
		 * the surrounding neighbor blocks.
		 * Then we are going to calculate which block to create.
		 */
		
		List *neighbor_blocks = MineList_Create(NULL);
		
		for( x = 0; x < MineWorld_GetWidth(world); x++ )
		{
			for( y = 0; y < MineWOrld_GetHeight(world); y++ )
			{
				/* Empty the list of neighbor blocks */
				MineList_Clear(neighbor_blocks);
				
				/* Get the neighbor blocks */
				Block *neighbor_block = NULL;
				
				neighbor_block = MineWorld_GetBlock(world, x - 1, y - 1);
				if( neighbor_block )
					MineList_Append(neighbor_blocks, neighbor_block);

				neighbor_block = MineWorld_GetBlock(world, x - 1, y);
				if( neighbor_block )
					MineList_Append(neighbor_blocks, neighbor_block);

				
				/* Go through the registered blocks */
				
				
			}
		}
	}
	return world;
}

