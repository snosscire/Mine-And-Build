#include "MineTestState.h"
#include "../MineInclude.h"
#include "../MineEngine.h"
#include "../MineEvent.h"
#include "../MineGame.h"
#include "../MineScrollCamera.h"
#include "../MineBlock.h"
#include "../Blocks/MineDirtBlock.h"

#include <stdlib.h>
#include <SDL/SDL_image.h>

typedef struct __mine_test_state TestState;

struct __mine_test_state
{
	unsigned int world_width;
	unsigned int world_height;
	Block ***blocks;
	Camera *camera;
};

struct __mine_block_dirt
{
	unsigned int time_since_creation;
};

SDL_Surface *block_surface = NULL;

void _MineTestState_OnKeyUp( SDL_Event *event, void *data )
{
	if( event->key.keysym.sym == SDLK_ESCAPE )
	{
		MineGame_Quit();
	}
	else if( event->key.keysym.sym == SDLK_SPACE )
	{
		MineGame_SetState(NULL);
	}
}

void _MineTestState_Start( void *data )
{
	TestState *self = (TestState *)data;
	
	int x = 0;
	int y = 0;
	
	int world_width = 4096 / BLOCK_WIDTH;
	int world_height = 2048 / BLOCK_HEIGHT;
	int limit_up = world_height * 0.75;
	int limit_down = world_height * 0.25;
	int start_y = MineEngine_RandomNumber(limit_down, limit_up);
	int last_y = start_y;
	int block_count = 0;
	int blocks_in_row = 0;
	
	MineEvent_RegisterCallback(SDL_KEYUP, _MineTestState_OnKeyUp, NULL);
	
	block_surface = IMG_Load("dirt.png");
	
	printf("World Width: %d\n", world_width);
	printf("World Height: %d\n", world_height);
	printf("Limit Up: %d\n", limit_up);
	printf("Limit Down: %d\n", limit_down);
	printf("Start Y: %d\n", start_y);
	
	self->world_width = world_width;
	self->world_height = world_height;
	self->blocks = malloc(sizeof(Block *) * world_width);
	self->camera = MineScrollCamera_Create(world_width * 16, world_height * 16);
	
	for( x = 0; x < world_width; x++ )
	{
		self->blocks[x] = malloc(sizeof(Block *) * world_height);
		for( y = 0; y < world_height; y++ )
		{
			/*
			self->blocks[x][y] = malloc(sizeof(Block));
			self->blocks[x][y]->x = x;
			self->blocks[x][y]->y = y;
			self->blocks[x][y]->r = 0;
			self->blocks[x][y]->g = 0;
			self->blocks[x][y]->b = 0;
			*/
			Block *block = MineBlock_Create();
			//Block *block = MineDirtBlock_Create();
			MineBlock_SetX(block, x);
			MineBlock_SetY(block, y);
			self->blocks[x][y] = block;
		}
	}
	
	for( x = 0; x < world_width; x++ )
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
		
		MineBlock_Destroy(self->blocks[x][y]);
		self->blocks[x][y] = MineDirtBlock_Create();
		MineBlock_SetX(self->blocks[x][y], x);
		MineBlock_SetY(self->blocks[x][y], y);
		
		/*
		self->blocks[x][y]->x = x * 16;
		self->blocks[x][y]->y = y * 16;
		self->blocks[x][y]->r = MineEngine_RandomNumber(0, 255);
		self->blocks[x][y]->g = MineEngine_RandomNumber(0, 255);
		self->blocks[x][y]->b = MineEngine_RandomNumber(0, 255);
		*/
		
		{
			int _y = y +1;
			for( ; _y < world_height; _y++ )
			{
				/*
				self->blocks[x][_y]->x = x * 16;
				self->blocks[x][_y]->y = _y * 16;
				self->blocks[x][_y]->r = MineEngine_RandomNumber(0, 255);
				self->blocks[x][_y]->g = MineEngine_RandomNumber(0, 255);
				self->blocks[x][_y]->b = MineEngine_RandomNumber(0, 255);
				*/
				MineBlock_Destroy(self->blocks[x][_y]);
				self->blocks[x][_y] = MineDirtBlock_Create();
				MineBlock_SetX(self->blocks[x][_y], x);
				MineBlock_SetY(self->blocks[x][_y], _y);
			}
		}
		
		block_count++;
		last_y = y;
	}
}

void _MineTestState_Stop( void *data )
{
	int x;
	int y;
	printf("Stop\n");
	TestState *self = (TestState *)data;
	for( x = 0; x < self->world_width; x++ )
	{
		for( y = 0; y < self->world_height; y++ )
		{
			free(self->blocks[x][y]);
		}
		free(self->blocks[x]);
	}
	free(self->blocks);
	MineCamera_Destroy(self->camera);
	free(self);
	SDL_FreeSurface(block_surface);
	MineEvent_UnregisterCallback(_MineTestState_OnKeyUp);	
}

void _MineTestState_Update( void *data )
{
}

void _MineTestState_Draw( void *data )
{
	TestState *self = (TestState *)data;
	SDL_Rect rect;
	//Uint32 red;
	//Uint32 green;
	//Uint32 blue;
	int x;
	int y;
	
	rect.x = 0;
	rect.y = 0;
	rect.w = MineEngine_ScreenWidth();
	rect.h = MineEngine_ScreenHeight();
	SDL_FillRect(MineEngine_VideoSurface, &rect, SDL_MapRGB(MineEngine_VideoSurface->format, 50, 150, 200));
	
	//for( x = 0; x < self->world_width; x++ )
	for( x = (MineCamera_Left(self->camera) / BLOCK_WIDTH); x < (MineCamera_Right(self->camera) / BLOCK_WIDTH) + 1; x++ )
	{
		//for( y = 0; y < self->world_height; y++ )
		for( y = (MineCamera_Top(self->camera) / BLOCK_HEIGHT); y < (MineCamera_Bottom(self->camera) / BLOCK_HEIGHT) + 1; y++ )
		{
			if( x >= self->world_width OR y >= self->world_height )
			{
				continue;
			}
			
			MineBlock_Draw(self->blocks[x][y], self->camera);
			
			//rect.x = x * BLOCK_WIDTH;
			//rect.y = y * BLOCK_HEIGHT;
			//rect.x = (x * BLOCK_WIDTH) - MineCamera_Left(self->camera);
			//rect.y = (y * BLOCK_HEIGHT) - MineCamera_Top(self->camera);
			//rect.x = self->blocks[x][y]->x;
			//rect.y = self->blocks[x][y]->y;
			//rect.w = BLOCK_WIDTH;
			//rect.h = BLOCK_HEIGHT;
			//red = self->blocks[x][y]->r;
			//green = self->blocks[x][y]->g;
			//blue = self->blocks[x][y]->b;
			/*
			SDL_FillRect(MineEngine_VideoSurface, &rect, SDL_MapRGB(MineEngine_VideoSurface->format, red, green, blue));
			*/
			//if( red > 0 OR blue > 0 OR green > 0 )
			//{
			//	SDL_BlitSurface(block_surface, NULL, MineEngine_VideoSurface, &rect);
			//} else {
			//	
			//}
		}
	}
}

State * MineTestState_Create()
{
	State *state = MineState_Create();
	if( state )
	{
		TestState *data = malloc(sizeof(TestState));
		data->blocks = NULL;
		state->data = data;
		state->start = _MineTestState_Start;
		state->stop = _MineTestState_Stop;
		state->update = _MineTestState_Update;
		state->draw = _MineTestState_Draw;
		return state;
	}
	return NULL;
}

