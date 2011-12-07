#include "MineInclude.h"
#include "MineWorldGenerator.h"
#include "MineEngine.h"
#include "Blocks/MineNoneBlock.h"
#include "Blocks/MineDirtBlock.h"
#include "Blocks/MineStoneBlock.h"

typedef struct __mine_world_generator_registered_block RegisteredBlock;
typedef struct __mine_world_generator_probability      Probability;

struct __mine_world_generator_registered_block
{
	BlockType type;
	Block * (*create)(World*,unsigned int,unsigned int);
	int (*spawn_probability)(Block*,Block*,Block*,Block*);
};

struct __mine_world_generator_probability
{
	RegisteredBlock *block;
	int low;
	int high;
};

List *MineWorldGenerator_RegisteredBlocks = NULL;

void MineWorldGenerator_Startup()
{
	MineWorldGenerator_RegisteredBlocks = MineList_Create(NULL);
	MineWorldGenerator_RegisterBlocks();
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

void MineWorldGenerator_RegisterBlock( BlockType type, Block * (*create)(World*,unsigned int,unsigned int), int (*spawn_probability)(Block*,Block*,Block*,Block*) )
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

//World * MineWorldGenerator_CreateWorld_old( unsigned int width, unsigned int height )
//{
//	World *world = MineWorld_Create(width, height);
//	if( world )
//	{
//		/* World generation starts with the placing on one dirt block.
//		 * This is the seed that will create the whole world.
//		 */
//		int limit_up = MineWorld_GetHeight(world) * 0.75;
//		int limit_down = MineWorld_GetHeight(world) * 0.25;
//		
//		int x = 0;
//		int y = MineEngine_RandomNumber(limit_down, limit_up);
//		
//		MineWorld_SetBlock(world, x, y, MineBlock_Dirt_Create(x, y));
//		
//		/* Next we are going to go through each position in the world and ask
//		 * what the probability of a block spawning is based on
//		 * the surrounding neighbor blocks.
//		 * Then we are going to calculate which block to create.
//		 */
//		
//		Uint32 complete_start;
//		Uint32 complete_end;
//		Uint32 complete_time;
//		
//		Uint32 start;
//		Uint32 end;
//		Uint32 time;
//		
//		List *neighbor_blocks = NULL;
//		
//		complete_start = SDL_GetTicks();
//		
//		//unsigned int world_width = ;
//		//unsigned int world_height = ;
//		
//		for( x = 0; x < MineWorld_GetWidth(world); x++ )
//		{
//			for( y = 0; y < MineWorld_GetHeight(world); y++ )
//			{
//				//printf("Creating block: %d,%d\n", x, y);
//				
//				start = SDL_GetTicks();
//				
//				/* Empty the list of neighbor blocks */
//				//if( neighbor_blocks )
//				//	MineList_Destroy(neighbor_blocks);
//				//neighbor_blocks = MineList_Create(NULL);
//				
//				end = SDL_GetTicks();
//				time = end - start;
//				//printf("Clear list: %d\n", time);
//				
//				/* Get the neighbor blocks */
//				Block *neighbor_block = NULL;
//				
//				start = SDL_GetTicks();
//				
//				Block *neighbor_left = MineWorld_GetBlock(world, x - 1, y);
//				Block *neighbor_right = MineWorld_GetBlock(world, x + 1, y);
//				Block *neighbor_top = MineWorld_GetBlock(world, x, y - 1);
//				Block *neighbor_bottom = MineWorld_GetBlock(world, x, y + 1);
//				
//				/*
//				neighbor_block = MineWorld_GetBlock(world, x - 1, y - 1);
//				if( neighbor_block )
//					MineList_Append(neighbor_blocks, neighbor_block);
//				
//				neighbor_block = MineWorld_GetBlock(world, x - 1, y);
//				if( neighbor_block )
//					MineList_Append(neighbor_blocks, neighbor_block);
//				
//				neighbor_block = MineWorld_GetBlock(world, x - 1, y + 1);
//				if( neighbor_block )
//					MineList_Append(neighbor_blocks, neighbor_block);
//				
//				neighbor_block = MineWorld_GetBlock(world, x, y - 1);
//				if( neighbor_block )
//					MineList_Append(neighbor_blocks, neighbor_block);
//				
//				neighbor_block = MineWorld_GetBlock(world, x, y + 1);
//				if( neighbor_block )
//					MineList_Append(neighbor_blocks, neighbor_block);
//				
//				neighbor_block = MineWorld_GetBlock(world, x + 1, y - 1);
//				if( neighbor_block )
//					MineList_Append(neighbor_blocks, neighbor_block);
//				
//				neighbor_block = MineWorld_GetBlock(world, x + 1, y);
//				if( neighbor_block )
//					MineList_Append(neighbor_blocks, neighbor_block);
//				
//				neighbor_block = MineWorld_GetBlock(world, x + 1, y + 1);
//				if( neighbor_block )
//					MineList_Append(neighbor_blocks, neighbor_block);
//				*/
//				
//				end = SDL_GetTicks();
//				time = end - start;
//				//printf("Get neighbor blocks: %d\n", time);
//				
//				/* Go through the registered blocks */
//				
//				start = SDL_GetTicks();
//				
//				FOREACH(MineWorldGenerator_RegisteredBlocks, RegisteredBlock, block)
//					int probability = block->spawn_probability(neighbor_left, );
//					int random_number = MineEngine_RandomNumber(1, 100);
//					if( random_number <= probability )
//					{
//						//printf("Setting block: %d\n", block->type);
//						MineWorld_SetBlock(world, x, y, block->create(x, y));
//						break;
//					}
//				ENDFOREACH
//				
//				end = SDL_GetTicks();
//				time = end - start;
//				
//				//printf("Loop registered blocks: %d\n", time);
//			}
//		}
//		
//		complete_end = SDL_GetTicks();
//		complete_time = complete_end - complete_start;
//		
//		printf("Complete: %d\n", complete_time);
//	}
//	return world;
//}

World * MineWorldGenerator_CreateWorld( unsigned int width, unsigned int height )
{
	World *world = MineWorld_Create(width, height);
	if( world )
	{
		int limit_up = MineWorld_GetHeight(world) * 0.65;
		int limit_down = MineWorld_GetHeight(world) * 0.45;
		
		int x = 0;
		int y = MineEngine_RandomNumber(limit_down, limit_up);
		
		//MineWorld_SetBlock(world, x, y, MineBlock_Dirt_Create(x, y));
		
		int last_y = y;
		int blocks_in_row = 0;

		Uint32 complete_start;
		Uint32 complete_end;
		Uint32 complete_time;
		
		complete_start = SDL_GetTicks();
		
		for( x = 0; x < MineWorld_GetWidth(world); x++ )
		{
			int random_number = MineEngine_RandomNumber(1, 100);
			y = last_y;
			
			if( blocks_in_row >= 1 )
			{
				if( y >= limit_up )
				{
					y = last_y - 1;
					blocks_in_row = 0;
				}
				else if( y <= limit_down )
				{
					y = last_y + 1;
					blocks_in_row = 0;
				}
				else
				{
					if( random_number > 66 )
					{
						y = last_y + 1;
						blocks_in_row = 0;
					}
					else if( random_number < 33 )
					{
						y = last_y - 1;
						blocks_in_row = 0;
					} else {
						blocks_in_row++;
					}
				}
			} else {
				blocks_in_row++;
			}

			MineWorld_SetBlock(world, x, y, MineBlock_Dirt_Create(world, x, y));
			
			last_y = y;
		}
		
		/* Next we are going to go through each position in the world and ask
		 * what the probability of a block spawning is based on
		 * the surrounding neighbor blocks.
		 * Then we are going to calculate which block to create.
		 */
		
		Uint32 start;
		Uint32 end;
		Uint32 time;
		
		List *neighbor_blocks = NULL;
		char found_ground_start = FALSE;
		
		//unsigned int world_width = ;
		//unsigned int world_height = ;
		
		for( x = 0; x < MineWorld_GetWidth(world); x++ )
		{
			found_ground_start = FALSE;
			
			for( y = 0; y < MineWorld_GetHeight(world); y++ )
			{
				//printf("Creating block: %d,%d\n", x, y);
				
				if( NOT found_ground_start )
				{
					Block *block = MineWorld_GetBlock(world, x, y);
					if( block AND MineBlock_GetType(block) == MINE_BLOCK_TYPE_DIRT )
					{
						found_ground_start = TRUE;
						continue;
					}
					continue;
				}
				
				start = SDL_GetTicks();
				
				// Empty the list of neighbor blocks
				//if( neighbor_blocks )
				//	MineList_Destroy(neighbor_blocks);
				//neighbor_blocks = MineList_Create(NULL);
				
				end = SDL_GetTicks();
				time = end - start;
				//printf("Clear list: %d\n", time);
				
				// Get the neighbor blocks
				Block *neighbor_block = NULL;
				
				start = SDL_GetTicks();
				
				Block *neighbor_left = MineWorld_GetBlock(world, x - 1, y);
				Block *neighbor_right = MineWorld_GetBlock(world, x + 1, y);
				Block *neighbor_top = MineWorld_GetBlock(world, x, y - 1);
				Block *neighbor_bottom = MineWorld_GetBlock(world, x, y + 1);
				/*
				neighbor_block = MineWorld_GetBlock(world, x - 1, y - 1);
				if( neighbor_block )
					MineList_Append(neighbor_blocks, neighbor_block);
				
				neighbor_block = MineWorld_GetBlock(world, x - 1, y);
				if( neighbor_block )
					MineList_Append(neighbor_blocks, neighbor_block);
				
				neighbor_block = MineWorld_GetBlock(world, x - 1, y + 1);
				if( neighbor_block )
					MineList_Append(neighbor_blocks, neighbor_block);
				
				neighbor_block = MineWorld_GetBlock(world, x, y - 1);
				if( neighbor_block )
					MineList_Append(neighbor_blocks, neighbor_block);
				
				neighbor_block = MineWorld_GetBlock(world, x, y + 1);
				if( neighbor_block )
					MineList_Append(neighbor_blocks, neighbor_block);
				
				neighbor_block = MineWorld_GetBlock(world, x + 1, y - 1);
				if( neighbor_block )
					MineList_Append(neighbor_blocks, neighbor_block);
				
				neighbor_block = MineWorld_GetBlock(world, x + 1, y);
				if( neighbor_block )
					MineList_Append(neighbor_blocks, neighbor_block);
				
				neighbor_block = MineWorld_GetBlock(world, x + 1, y + 1);
				if( neighbor_block )
					MineList_Append(neighbor_blocks, neighbor_block);
				*/
				end = SDL_GetTicks();
				time = end - start;
				//printf("Get neighbor blocks: %d\n", time);
				
				// Go through the registered blocks
				
				start = SDL_GetTicks();
				
				/*
				FOREACH(MineWorldGenerator_RegisteredBlocks, RegisteredBlock, block)
					int probability = block->spawn_probability(neighbor_blocks);
					int random_number = MineEngine_RandomNumber(1, 100);
					if( random_number <= probability )
					{
						//printf("Setting block: %d\n", block->type);
						MineWorld_SetBlock(world, x, y, block->create(x, y));
						break;
					}
				ENDFOREACH
				*/
				
				List *probabilities = MineList_Create(free);
				int number = 0;
				
				FOREACH(MineWorldGenerator_RegisteredBlocks,  RegisteredBlock, block)
					Probability *probability = malloc(sizeof(Probability));
					probability->block = block;
					probability->low = number + 1;
					probability->high = number + block->spawn_probability(neighbor_left, neighbor_right, neighbor_top, neighbor_bottom);
					number = probability->high;
					MineList_Append(probabilities, probability);
				ENDFOREACH
				
				int random_number = MineEngine_RandomNumber(1, number);
				
				FOREACH(probabilities, Probability, probability)
					if( random_number >= probability->low AND random_number <= probability->high )
					{
						MineWorld_SetBlock(world, x, y, probability->block->create(world, x, y));
						break;
					}
				ENDFOREACH
				
				MineList_Destroy(probabilities);
				
				end = SDL_GetTicks();
				time = end - start;
				
				//printf("Loop registered blocks: %d\n", time);
			}
		}
		
		complete_end = SDL_GetTicks();
		complete_time = complete_end - complete_start;
		
		printf("Complete: %d\n", complete_time);
	}
	return world;
}

