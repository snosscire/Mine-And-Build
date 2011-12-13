#include "../../MineInclude.h"
#include "MineDefaultJumping.h"
#include "../../MineObject.h"
#include "../../MineWorld.h"

void _MineBehavior_DefaultJumping_Perform( Object *object, unsigned int delta_time )
{
	if( MineObject_PerformedJump(object) )
	{
		MineObject_SetJump(object, FALSE);
		if( NOT MineObject_IsJumping(object) AND MineObject_IsTouchingGround(object) )
		{
			MineObject_SetVelocityY(object, -8.0);
			MineObject_SetJumping(object, TRUE);
		}
	}
	else if( MineObject_IsJumping(object) )
	{
		if( MineObject_IsTouchingGround(object) )
		{
			MineObject_SetJumping(object, FALSE);
		}
	}
}

Behavior * MineBehavior_DefaultJumping_Create()
{
	Behavior *behavior = MineBehavior_Create();
	if( behavior )
	{
		behavior->perform = _MineBehavior_DefaultJumping_Perform;
		return behavior;
	}
	return NULL;
}

