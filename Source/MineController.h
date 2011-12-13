#ifndef MINE_CONTROLLER_H
#define MINE_CONTROLLER_H

#include "MineObject.h"

typedef struct __mine_controller Controller;

struct __mine_object;
struct __mine_controller
{
	struct __mine_object *object;
	void (*destroy)(Controller*);
};

Controller * MineController_Create( Object *object );
void MineController_Destroy( Controller *controller );

#endif /* MINE_CONTROLLER_H */
