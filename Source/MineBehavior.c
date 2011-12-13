#include "MineInclude.h"
#include "MineBehavior.h"
#include "MineObject.h"
#include "MineWorld.h"

Behavior * MineBehavior_Create()
{
	Behavior *behavior = malloc(sizeof(Behavior));
	if( behavior )
	{
		behavior->perform = NULL;
		return behavior;
	}
	return NULL;
}

void MineBehavior_Destroy( Behavior *behavior )
{
	free(behavior);
}

void MineBehavior_Perform( Behavior *behavior, Object *object, unsigned int delta_time )
{
	if( behavior->perform )
	{
		behavior->perform(object, delta_time);
	}
}

