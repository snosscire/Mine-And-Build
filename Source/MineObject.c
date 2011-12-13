#include "MineInclude.h"
#include "MineObject.h"
#include "MineEngine.h"

#include <math.h>

Object * MineObject_Create( World *world, unsigned int x, unsigned int y )
{
	Object *object = malloc(sizeof(Object));
	if( object )
	{
		object->world = world;
		object->x = x;
		object->y = y;
		object->velocity_x = 0.0;
		object->velocity_y = 0.0;
		object->move_left = FALSE;
		object->move_right = FALSE;
		object->jump = FALSE;
		object->jumping = FALSE;
		object->touching_ground = FALSE;
		object->image = NULL;
		object->update = NULL;
		object->draw = NULL;
		return object;
	}
	return NULL;
}

void MineObject_Destroy( Object *object )
{
	if( object->image )
	{
		SDL_FreeSurface(object->image);
	}
	free(object);
}

World * MineObject_GetWorld( Object *object )
{
	return object->world;
}

double MineObject_GetX( Object *object )
{
	return object->x;
}

double MineObject_GetY( Object *object )
{
	return object->y;
}

unsigned int MineObject_GetWidth( Object *object )
{
	if( object->image )
	{
		return object->image->w;
	}
	return 32;
}

unsigned int MineObject_GetHeight( Object *object )
{
	if( object->image )
	{
		return object->image->h;
	}
	return 32;
}

double MineObject_GetVelocityX( Object *object )
{
	return object->velocity_x;
}

double MineObject_GetVelocityY( Object *object )
{
	return object->velocity_y;
}

void MineObject_SetX( Object *object, double value )
{
	object->x = value;
}

void MineObject_SetY( Object *object, double value )
{
	object->y = value;
}

void MineObject_SetVelocityX( Object *object, double value )
{
	object->velocity_x = value;
}

void MineObject_SetVelocityY( Object *object, double value )
{
	object->velocity_y = value;
}

void MineObject_SetMoveLeft( Object *object, char state )
{
	object->move_left = state;
}

void MineObject_SetMoveRight( Object *object, char state )
{
	object->move_right = state;
}

void MineObject_SetJump( Object *object, char state )
{
	object->jump = state;
}

void MineObject_SetJumping( Object *object, char state )
{
	object->jumping = state;
}

void MineObject_SetTouchingGround( Object *object, char state )
{
	object->touching_ground = state;
}

char MineObject_PerformedMoveLeft( Object *object )
{
	return object->move_left;
}

char MineObject_PerformedMoveRight( Object *object )
{
	return object->move_right;
}

char MineObject_PerformedJump( Object *object )
{
	return object->jump;
}

char MineObject_IsJumping( Object *object )
{
	return object->jumping;
}

char MineObject_IsTouchingGround( Object *object )
{
	return object->touching_ground;
}

void MineObject_Update( Object *object, unsigned int delta_time )
{
	if( object->update )
	{
		object->update(object, delta_time);
	}
	else
	{
		if( object->moving_behavior ) {
			MineBehavior_Perform(object->moving_behavior, object, delta_time);
		}
		if( object->jumping_behavior ) {
			MineBehavior_Perform(object->jumping_behavior, object, delta_time);
		}
		if( object->falling_behavior ) {
			MineBehavior_Perform(object->falling_behavior, object, delta_time);
		}
		if( object->colliding_behavior ) {
			MineBehavior_Perform(object->colliding_behavior, object, delta_time);
		}
	}
}

void MineObject_Draw( Object *object, Camera *camera )
{
	if( object->draw )
	{
		object->draw(object, camera);
	}
	else if( object->image )
	{
		unsigned int x = object->x - (object->image->w / 2);
		unsigned int y = object->y - (object->image->h / 2);
		SDL_Rect dst;
		dst.x = x - MineCamera_Left(camera);
		dst.y = y - MineCamera_Top(camera);
		SDL_BlitSurface(object->image, NULL, MineEngine_VideoSurface, &dst);
	}
	else
	{
		SDL_Rect rect;
		rect.x = (object->x - 16) - MineCamera_Left(camera);
		rect.y = (object->y - 16) - MineCamera_Top(camera);
		rect.w = 32;
		rect.h = 32;
		Uint32 white = SDL_MapRGB(MineEngine_VideoSurface->format, 255, 255, 255);
		SDL_FillRect(MineEngine_VideoSurface, &rect, white);
	}
}

