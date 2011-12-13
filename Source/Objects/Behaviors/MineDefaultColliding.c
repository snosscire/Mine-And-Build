#include "../../MineInclude.h"
#include "MineDefaultColliding.h"
#include "../../MineObject.h"
#include "../../MineWorld.h"

void _MineBehavior_DefaultColliding_Perform( Object *object, unsigned int delta_time )
{
	unsigned int object_width = MineObject_GetWidth(object);
	unsigned int object_height = MineObject_GetHeight(object);
	
	double old_x = MineObject_GetX(object);
	double old_y = MineObject_GetY(object);
	double new_x = MineObject_GetX(object);
	double new_y = MineObject_GetY(object);
	
	new_x += (MineObject_GetVelocityX(object) * (delta_time / 10.0));
	new_y += (MineObject_GetVelocityY(object) * (delta_time / 10.0));
	
	unsigned int old_left = old_x - (object_width / 2);
	unsigned int old_top = old_y - (object_width / 2);
	unsigned int new_left = new_x - (object_width / 2);
	unsigned int new_top = new_y - (object_height / 2);
	
	if( NOT MineWorld_HaveCollision(MineObject_GetWorld(object), new_left, new_top, object_width, object_height) )
	{
		MineObject_SetX(object, new_x);
		MineObject_SetY(object, new_y);
		MineObject_SetTouchingGround(object, FALSE);
	}
	else
	{
		if( NOT MineWorld_HaveCollision(MineObject_GetWorld(object), new_left, old_top, object_width, object_height) )
		{
			MineObject_SetX(object, new_x);
			MineObject_SetTouchingGround(object, TRUE);
		}
		else
		{
			if( NOT MineWorld_HaveCollision(MineObject_GetWorld(object), old_left, new_top, object_width, object_height) )
			{
				MineObject_SetY(object, new_y);
				MineObject_SetTouchingGround(object, FALSE);
			}
			else
			{
				MineObject_SetTouchingGround(object, TRUE);
			}
		}

	}
}

Behavior * MineBehavior_DefaultColliding_Create()
{
	Behavior *behavior = MineBehavior_Create();
	if( behavior )
	{
		behavior->perform = _MineBehavior_DefaultColliding_Perform;
		return behavior;
	}
	return NULL;
}

