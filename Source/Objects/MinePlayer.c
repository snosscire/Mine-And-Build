#include "../MineInclude.h"
#include "MinePlayer.h"
#include "Behaviors/MineDefaultMoving.h"
#include "Behaviors/MineDefaultJumping.h"
#include "Behaviors/MineDefaultFalling.h"
#include "Behaviors/MineDefaultColliding.h"

Object * MinePlayer_Create( World *world, unsigned int x, unsigned int y )
{
	Object *object = MineObject_Create(world, x, y);
	if( object )
	{
		object->moving_behavior = MineBehavior_DefaultMoving_Create();
		object->jumping_behavior = MineBehavior_DefaultJumping_Create();
		object->falling_behavior = MineBehavior_DefaultFalling_Create();
		object->colliding_behavior = MineBehavior_DefaultColliding_Create();
		return object;
	}
	return NULL;
}

