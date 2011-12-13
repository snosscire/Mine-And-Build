#ifndef MINE_OBJECT_H
#define MINE_OBJECT_H

#include "MineWorld.h"
#include "MineBehavior.h"
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
	Behavior *moving_behavior;
	Behavior *jumping_behavior;
	Behavior *falling_behavior;
	Behavior *colliding_behavior;
	SDL_Surface *image;
	void (*update)(Object*,unsigned int);
	void (*draw)(Object*,Camera*);
};

Object * MineObject_Create( World *world, unsigned int x, unsigned int y );
void MineObject_Destroy( Object *object );

World * MineObject_GetWorld( Object *object );

double MineObject_GetX( Object *object );
double MineObject_GetY( Object *object );
unsigned int MineObject_GetWidth( Object *object );
unsigned int MineObject_GetHeight( Object *object );
double MineObject_GetVelocityX( Object *object );
double MineObject_GetVelocityY( Object *object );

void MineObject_SetX( Object *object, double value );
void MineObject_SetY( Object *object, double value );
void MineObject_SetVelocityX( Object *object, double value );
void MineObject_SetVelocityY( Object *object, double value );

void MineObject_SetMoveLeft( Object *object, char state );
void MineObject_SetMoveRight( Object *object, char state );
void MineObject_SetJump( Object *object, char state );
void MineObject_SetJumping( Object *object, char state );
void MineObject_SetTouchingGround( Object *object, char state );

char MineObject_PerformedMoveLeft( Object *object );
char MineObject_PerformedMoveRight( Object *object );
char MineObject_PerformedJump( Object *object );

char MineObject_IsJumping( Object *object );
char MineObject_IsTouchingGround( Object *object );

void MineObject_Update( Object *object, unsigned int delta_time );
void MineObject_Draw( Object *object, Camera *camera );

#endif /* MINE_OBJECT_H */
