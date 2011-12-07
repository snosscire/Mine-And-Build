#include "MineInclude.h"
#include "MineBlock.h"
#include "MineWorld.h"
#include "MineEngine.h"

Block * MineBlock_Create( World *world, unsigned int x, unsigned int y )
{
	Block *self = malloc(sizeof(Block));
	if( self )
	{
		self->world = world;
		self->x = x;
		self->y = y;
		self->destroy = NULL;
		self->update = NULL;
		self->draw = NULL;
		self->data = NULL;
		return self;
	}
	return NULL;
}

void MineBlock_Destroy( Block *self )
{
	if( self->destroy )
	{
		self->destroy(self);
	}
	free(self);
}

void MineBlock_Update( Block *self )
{
	if( self->update )
	{
		self->update(self);
	}
}

void MineBlock_Draw( Block *self, Camera *camera )
{
	if( self->draw )
	{
		self->draw(self, camera);
	}
}

void _MineBlock_DefaultDraw( Block *self, Camera *camera )
{
	SDL_Rect dst;
	dst.x = (self->x * BLOCK_WIDTH) - MineCamera_Left(camera);
	dst.y = (self->y * BLOCK_HEIGHT) - MineCamera_Top(camera);
	dst.w = BLOCK_WIDTH;
	dst.h = BLOCK_HEIGHT;
	
	SDL_BlitSurface(self->image, NULL, MineEngine_VideoSurface, &dst);
}

void MineBlock_SetX( Block *self, unsigned int x )
{
	self->x = x;
}

void MineBlock_SetY( Block *self, unsigned int y )
{
	self->y = y;
}

BlockType MineBlock_GetType( Block *self )
{
	return self->type;
}

