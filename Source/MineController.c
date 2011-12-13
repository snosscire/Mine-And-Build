#include "MineInclude.h"
#include "MineController.h"
#include "MineObject.h"

Controller * MineController_Create( Object *object )
{
	Controller *controller = malloc(sizeof(Controller));
	if( controller )
	{
		controller->object = object;
		controller->destroy = NULL;
		return controller;
	}
	return NULL;
}

void MineController_Destroy( Controller *controller )
{
	if( controller->destroy )
	{
		controller->destroy(controller);
	}
	free(controller);
}

