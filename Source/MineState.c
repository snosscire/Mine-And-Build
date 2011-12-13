#include "MineInclude.h"
#include "MineState.h"

#include <stdlib.h>

State * MineState_Create()
{
	State *state = (State *)malloc(sizeof(State));
	if( state )
	{
		state->start = NULL;
		state->stop = NULL;
		state->update = NULL;
		state->draw = NULL;
		return state;
	}
	return NULL;
}

void MineState_Delete( State *state )
{
	if( state )
	{
		free(state);
	}
}

void MineState_Start( State *state )
{
	if( NOT state->running )
	{
		if( state->start )
		{
			state->start(state->data);
		}
		state->running = TRUE;
	}
}

void MineState_Stop( State *state )
{
	if( state->running )
	{
		if( state->stop )
		{
			state->stop(state->data);
		}
		state->running = FALSE;
	}
}

void MineState_Update( State *state, unsigned int delta_time )
{
	if( state->running )
	{
		if( state->update )
		{
			state->update(state->data, delta_time);
		}
	}
}

void MineState_Draw( State *state )
{
	if( state->running )
	{
		if( state->draw )
		{
			state->draw(state->data);
		}
	}
}

