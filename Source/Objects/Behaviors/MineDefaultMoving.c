#include "../../MineInclude.h"
#include "MineDefaultMoving.h"
#include "../../MineObject.h"
#include "../../MineWorld.h"

void _MineBehavior_DefaultMoving_Perform( Object *object, unsigned int delta_time )
{
	MineObject_SetVelocityX(object, 0.0);
	
	if( MineObject_PerformedMoveLeft(object) )
	{
		MineObject_SetVelocityX(object, -2.0);
	}
	else if( MineObject_PerformedMoveRight(object) )
	{
		MineObject_SetVelocityX(object, 2.0);
	}
}

Behavior * MineBehavior_DefaultMoving_Create()
{
	Behavior *behavior = MineBehavior_Create();
	if( behavior )
	{
		behavior->perform = _MineBehavior_DefaultMoving_Perform;
		return behavior;
	}
	return NULL;
}

