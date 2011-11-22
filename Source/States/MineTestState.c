#include "MineTestState.h"
#include "../MineInclude.h"
#include "../MineEngine.h"
#include "../MineEvent.h"
#include "../MineGame.h"
#include "../MineWorld.h"
#include "../MineWorldGenerator.h"
#include "../MineScrollCamera.h"

#include <stdlib.h>

typedef struct __mine_test_state TestState;

struct __mine_test_state
{
	World *world;
	Camera *camera;
};

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
	
	int world_width = 512;
	int world_height = 256;
	
	MineWorldGenerator_Startup();
	
	self->world = MineWorldGenerator_CreateWorld(world_width, world_height);
	self->camera = MineScrollCamera_Create(world_width * 16, world_height * 16);
	
	MineWorldGenerator_Shutdown();
	
	MineEvent_RegisterCallback(SDL_KEYUP, _MineTestState_OnKeyUp, NULL);
}

void _MineTestState_Stop( void *data )
{
	TestState *self = (TestState *)data;
	MineWorld_Destroy(self->world);
	MineCamera_Destroy(self->camera);
	free(self);
	MineEvent_UnregisterCallback(_MineTestState_OnKeyUp);	
}

void _MineTestState_Update( void *data )
{
}

void _MineTestState_Draw( void *data )
{
	TestState *self = (TestState *)data;
	MineWorld_Draw(self->world, self->camera);
}

State * MineTestState_Create()
{
	State *state = MineState_Create();
	if( state )
	{
		TestState *data = malloc(sizeof(TestState));
		data->world = NULL;
		data->camera = NULL;
		state->data = data;
		state->start = _MineTestState_Start;
		state->stop = _MineTestState_Stop;
		state->update = _MineTestState_Update;
		state->draw = _MineTestState_Draw;
		return state;
	}
	return NULL;
}

