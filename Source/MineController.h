#ifndef MINE_CONTROLLER_H
#define MINE_CONTROLLER_H

#include "MineObject.h"

typedef struct __mine_controller Controller;

struct __mine_controller
{
	Object *object;
	void (*destroy)(Controller*);
	void *data;
};

Controller * MineController_Create( Object *object );
void MineController_Destroy( Controller *controller );

#endif /* MINE_CONTROLLER_H */
