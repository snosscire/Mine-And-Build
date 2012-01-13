#ifndef MINE_WORLD_H
#define MINE_WORLD_H

#include "MineBlock.h"
#include "MineCamera.h"

typedef struct __mine_world World;

struct __mine_world
{
	unsigned int width;
	unsigned int height;
	Block ***blocks;
};

World * MineWorld_Create( unsigned int width, unsigned int height );
void MineWorld_Destroy( World *world );
unsigned int MineWorld_GetWidth( World *world );
unsigned int MineWorld_GetHeight( World *world );
void MineWorld_SetBlock( World *world, unsigned int x, unsigned int y, Block *block );
Block * MineWorld_GetBlock( World *world, unsigned int x, unsigned int y );
void MineWorld_Draw( World *world, Camera *camera );
char MineWorld_HaveCollision( World *world, unsigned int x, unsigned int y, unsigned int width, unsigned int height );
void MineWorld_GetWorldPositionFromScreenPosition( World *world, Camera *camera, unsigned int screen_x, unsigned int screen_y, unsigned int *world_x, unsigned int *world_y );
Block * MineWorld_TakeBlock( World *world, unsigned int x, unsigned int y );

#endif /* MINE_WORLD_H */
