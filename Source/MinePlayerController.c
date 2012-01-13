#include "MineInclude.h"
#include "MinePlayerController.h"
#include "MineObject.h"
#include "MineWorld.h"
#include "MineEvent.h"

#include <SDL/SDL.h>

typedef struct __mine_player_controller PlayerController;
struct __mine_player_controller
{
	Camera *camera;
}; 

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

void _MinePlayerController_OnMouseButtonDown( SDL_Event *event, void *data )
{
	printf("OnButtonDown\n");
	
	Controller *super = data;
	PlayerController *self = super->data;
	
	World *world = MineObject_GetWorld(super->object);
	
	unsigned int screen_x = event->button.x;
	unsigned int screen_y = event->button.y;
	unsigned int world_x;
	unsigned int world_y;
	
	MineWorld_GetWorldPositionFromScreenPosition(world, self->camera, screen_x, screen_y, &world_x, &world_y);
	
	printf("x: %d\n", world_x);
	printf("y: %d\n", world_y);
	
	Block *block = MineWorld_TakeBlock(world, world_x, world_y);
	if( block )
	{
		printf("Took block.\n");
		MineBlock_Destroy(block);
	}
}

void _MinePlayerController_Destroy( Controller *controller )
{
	PlayerController *self = controller->data;
	free(self);
	MineEvent_UnregisterCallback(_MinePlayerController_OnKeyDown);
	MineEvent_UnregisterCallback(_MinePlayerController_OnKeyUp);
}

Controller * MinePlayerController_Create( Object *object, Camera *camera )
{
	Controller *super = MineController_Create(object);
	if( super )
	{
		PlayerController *self = malloc(sizeof(PlayerController));
		self->camera = camera;
		super->data = self;
		super->destroy = _MinePlayerController_Destroy;
		MineEvent_RegisterCallback(SDL_KEYDOWN, _MinePlayerController_OnKeyDown, super);
		MineEvent_RegisterCallback(SDL_KEYUP, _MinePlayerController_OnKeyUp, super);
		MineEvent_RegisterCallback(SDL_MOUSEBUTTONDOWN, _MinePlayerController_OnMouseButtonDown, super);
		return super;
	}
	return NULL;
}

