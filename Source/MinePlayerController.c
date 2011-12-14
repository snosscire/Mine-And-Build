#include "MineInclude.h"
#include "MinePlayerController.h"
#include "MineObject.h"
#include "MineEvent.h"

#include <SDL/SDL.h>

void _MinePlayerController_OnKeyDown( SDL_Event *event, void *data )
{
	Controller *controller = data;
	
	if( event->key.keysym.sym == SDLK_a )
	{
		MineObject_SetMoveLeft(controller->object, TRUE);
	}
	else if( event->key.keysym.sym == SDLK_d )
	{
		MineObject_SetMoveRight(controller->object, TRUE);
	}
	else if( event->key.keysym.sym == SDLK_SPACE )
	{
		MineObject_SetJump(controller->object, TRUE);
	}
}

void _MinePlayerController_OnKeyUp( SDL_Event *event, void *data )
{
	Controller *controller = data;
	
	if( event->key.keysym.sym == SDLK_a )
	{
		MineObject_SetMoveLeft(controller->object, FALSE);
	}
	else if( event->key.keysym.sym == SDLK_d )
	{
		MineObject_SetMoveRight(controller->object, FALSE);
	}
}

void _MinePlayerController_Destroy( Controller *controller )
{
	MineEvent_UnregisterCallback(_MinePlayerController_OnKeyDown);
	MineEvent_UnregisterCallback(_MinePlayerController_OnKeyUp);
}

Controller * MinePlayerController_Create( Object *object )
{
	Controller *controller = MineController_Create(object);
	if( controller )
	{
		controller->destroy = _MinePlayerController_Destroy;
		MineEvent_RegisterCallback(SDL_KEYDOWN, _MinePlayerController_OnKeyDown, controller);
		MineEvent_RegisterCallback(SDL_KEYUP, _MinePlayerController_OnKeyUp, controller);
		return controller;
	}
	return NULL;
}

