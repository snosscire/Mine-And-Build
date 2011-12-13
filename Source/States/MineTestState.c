#include "MineTestState.h"
#include "../MineInclude.h"
#include "../MineEngine.h"
#include "../MineEvent.h"
#include "../MineGame.h"
#include "../MineWorld.h"
#include "../MineWorldGenerator.h"
#include "../MineScrollCamera.h"
#include "../MinePlayerCamera.h"
#include "../MineObject.h"
#include "../MinePlayerController.h"

#include <stdlib.h>

typedef struct __mine_test_state TestState;

struct __mine_test_state
{
	World *world;
	Camera *camera;
	Object *player;
	Controller *controller;
};

void _MineTestState_OnKeyUp( SDL_Event *event, void *data )
{
	TestState *state = data;
	
	if( event->key.keysym.sym == SDLK_ESCAPE )
	{
		MineGame_Quit();
	}
	else if( event->key.keysym.sym == SDLK_r )
	{
		state->player->y -= 100.0;
	}
}

void _MineTestState_Start( void *data )
{
	TestState *self = (TestState *)data;
	
	int world_width = 512;
	int world_height = 256;
	
	MineWorldGenerator_Startup();
	
	self->world = MineWorldGenerator_CreateWorld(world_width, world_height);
	self->player = MineObject_Create(self->world, 100, 100);
	self->camera = MinePlayerCamera_Create(world_width * BLOCK_WIDTH, world_height * BLOCK_HEIGHT, self->player);
	self->controller = MinePlayerController_Create(self->player);
	
	MineWorldGenerator_Shutdown();
	
	MineEvent_RegisterCallback(SDL_KEYUP, _MineTestState_OnKeyUp, self);
}

void _MineTestState_Stop( void *data )
{
	TestState *self = (TestState *)data;
	MineController_Destroy(self->controller);
	MineWorld_Destroy(self->world);
	MineCamera_Destroy(self->camera);
	MineObject_Destroy(self->player);
	free(self);
	MineEvent_UnregisterCallback(_MineTestState_OnKeyUp);	
}

void _MineTestState_Update( void *data, unsigned int delta_time )
{
	TestState *self = (TestState *)data;
	MineObject_Update(self->player, delta_time);
}

void _MineTestState_Draw( void *data )
{
	TestState *self = (TestState *)data;
	MineWorld_Draw(self->world, self->camera);
	MineObject_Draw(self->player, self->camera);
}

State * MineTestState_Create()
{
	State *state = MineState_Create();
	if( state )
	{
		TestState *data = malloc(sizeof(TestState));
		data->world = NULL;
		data->camera = NULL;
		data->player = NULL;
		state->data = data;
		state->start = _MineTestState_Start;
		state->stop = _MineTestState_Stop;
		state->update = _MineTestState_Update;
		state->draw = _MineTestState_Draw;
		return state;
	}
	return NULL;
}

