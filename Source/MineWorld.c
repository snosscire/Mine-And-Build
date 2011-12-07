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

