#include "MineInclude.h"
#include "MineEngine.h"
#include "Blocks/MineNoneBlock.h"
#include "MineWorld.h"

World * MineWorld_Create( unsigned int width, unsigned int height )
{
	World *world = malloc(sizeof(World));
	if( world )
	{
		int x;
		int y;
		
		world->width = width;
		world->height = height;
		world->blocks = malloc(sizeof(Block *) * width);
		
		for( x = 0; x < width; x++ )
		{
			world->blocks[x] = malloc(sizeof(Block *) * height);
			for( y = 0; y < height; y++ )
			{
				//Block *block = MineBlock_None_Create(x, y);
				//world->blocks[x][y] = block;
				world->blocks[x][y] = NULL;
			}
		}
	}
	return world;
}

void MineWorld_Destroy( World *world )
{
	int x;
	int y;
	for( x = 0; x < world->width; x++ )
	{
		for( y = 0; y < world->height; y++ )
		{
			free(world->blocks[x][y]);
		}
		free(world->blocks[x]);
	}
	free(world->blocks);
	free(world);
}

unsigned int MineWorld_GetWidth( World *world )
{
	return world->width;
}

unsigned int MineWorld_GetHeight( World *world )
{
	return world->height;
}

void MineWorld_SetBlock( World *world, unsigned int x, unsigned int y, Block *new_block )
{
	if( x >= 0 AND x < world->width AND y >= 0 AND y < world->height )
	{
		Block *old_block = MineWorld_GetBlock(world, x, y);
		if( old_block )
		{
			MineBlock_Destroy(old_block);
		}
		world->blocks[x][y] = new_block;
	}
}

Block * MineWorld_GetBlock( World *world, unsigned int x, unsigned int y )
{
	if( x >= 0 AND x < world->width AND y >= 0 AND y < world->height )
	{
		return world->blocks[x][y];
	}
	return NULL;
}

void MineWorld_Draw( World *world, Camera *camera )
{
	int left = MineCamera_Left(camera) / BLOCK_WIDTH;
	int right = MineCamera_Right(camera) / BLOCK_WIDTH;
	int top = MineCamera_Top(camera) / BLOCK_HEIGHT;
	int bottom = MineCamera_Bottom(camera) / BLOCK_HEIGHT;
	
	int x;
	int y;
	
	Block *block = NULL;
	
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = MineEngine_ScreenWidth();
	rect.h = MineEngine_ScreenHeight();
	SDL_FillRect(MineEngine_VideoSurface, &rect, SDL_MapRGB(MineEngine_VideoSurface->format, 50, 150, 200));
	
	for( x = left; x <= right; x++ )
	{
		for( y = top; y <= bottom; y++ )
		{
			block = MineWorld_GetBlock(world, x, y);
			if( block )
			{
				MineBlock_Draw(block, camera);
			}
		}
	}
}

char _MineWorld_HaveCollision( SDL_Rect *a, SDL_Rect *b )
{
	int a_left = a->x;
	int a_right = a->x + a->w;
	int a_top = a->y;
	int a_bottom = a->y + a->h;
	int b_left = b->x;
	int b_right = b->x + b->w;
	int b_top = b->y;
	int b_bottom = b->y + b->h;
	if( a_bottom <= b_top ) {
		return FALSE;
	}
	if( a_top >= b_bottom ) {
		return FALSE;
	}
	if( a_right <= b_left ) {
		return FALSE;
	}
	if( a_left >= b_right ) {
		return FALSE;
	}
	return TRUE;
}

char MineWorld_HaveCollision( World *world, unsigned int x, unsigned int y, unsigned int width, unsigned int height )
{
	//printf("MineWorld_HaveCollision\n");
	char collision = FALSE;
	List *blocks = MineList_Create(NULL);
	
	unsigned int i;
	unsigned int j;
	
	for( i = x; i <= (x + width); i++ )
	{
		unsigned int block_x = i / BLOCK_WIDTH;
		
		for( j = y; j <= (y + height); j++ )
		{
			unsigned int block_y = j / BLOCK_HEIGHT;
			
			//printf("block_x: %d\n", block_x);
			//printf("block_y: %d\n", block_y);
			
			Block *block = MineWorld_GetBlock(world, block_x, block_y);
			
			if( block )
			{
				//printf("Found block\n");
				MineList_Append(blocks, block);
			}
		}
	}
	
	SDL_Rect object_rect;
	object_rect.x = x;
	object_rect.y = y;
	object_rect.w = width;
	object_rect.h = height;
	
	FOREACH(blocks, Block, block)
		SDL_Rect block_rect;
		block_rect.x = block->x * BLOCK_WIDTH;
		block_rect.y = block->y * BLOCK_HEIGHT;
		block_rect.w = BLOCK_WIDTH;
		block_rect.h = BLOCK_HEIGHT;
		
		if( _MineWorld_HaveCollision(&object_rect, &block_rect) )
		{
			collision = TRUE;
			break;
		}
	ENDFOREACH
	
	MineList_Destroy(blocks);
	
	return collision;
}


