#ifndef MINE_OBJECT_H
#define MINE_OBJECT_H

#include "MineWorld.h"
#include "MineCamera.h"

#include <SDL/SDL.h>

typedef struct __mine_object Object;

struct __mine_object
{
	World *world;
	double x;
	double y;
	double velocity_x;
	double velocity_y;
	char move_left;
	char move_right;
	char jump;
	char jumping;
	char touching_ground;
	SDL_Surface *image;
	void (*update)(Object*);
	void (*draw)(Object*,Camera*);
};

Object * MineObject_Create( World *world, unsigned int x, unsigned int y );
void MineObject_Destroy( Object *object );
unsigned int MineObject_GetX( Object *object );
unsigned int MineObject_GetY( Object *object );
unsigned int MineObject_GetWidth( Object *object );
unsigned int MineObject_GetHeight( Object *object );
void MineObject_SetMoveLeft( Object *object, char state );
void MineObject_SetMoveRight( Object *object, char state );
void MineObject_Update( Object *object, unsigned int delta_time );
void MineObject_Draw( Object *object, Camera *camera );

#endif /* MINE_OBJECT_H */
