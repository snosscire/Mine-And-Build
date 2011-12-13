#include "../../MineInclude.h"
#include "MineDefaultFalling.h"
#include "../../MineObject.h"
#include "../../MineWorld.h"

#define MINE_DEFAULT_GRAVITY 4.0

void _MineBehavior_DefaultFalling_Perform( Object *object, unsigned int delta_time )
{
	if( MineObject_IsJumping(object) )
	{
		if( NOT MineObject_IsTouchingGround(object) )
		{
			double velocity = MineObject_GetVelocityY(object);
			double change = (MINE_DEFAULT_GRAVITY * (delta_time / 100.0));
			velocity += change;
			MineObject_SetVelocityY(object, velocity);
			if( MineObject_GetVelocityY(object) > MINE_DEFAULT_GRAVITY )
			{
				MineObject_SetVelocityY(object, MINE_DEFAULT_GRAVITY);
			}
		}			
	} else {
		MineObject_SetVelocityY(object, MINE_DEFAULT_GRAVITY);
	}
}

Behavior * MineBehavior_DefaultFalling_Create()
{
	Behavior *behavior = MineBehavior_Create();
	if( behavior )
	{
		behavior->perform = _MineBehavior_DefaultFalling_Perform;
		return behavior;
	}
	return NULL;
}

