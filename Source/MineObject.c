#include "MineInclude.h"
#include "MineObject.h"
#include "MineEngine.h"

#include <math.h>

Object * MineObject_Create( World *world, unsigned int x, unsigned int y )
{
	Object *object = malloc(sizeof(Object));
	if( object )
	{
		object->world = world;
		object->x = x;
		object->y = y;
		object->velocity_x = 0.0;
		object->velocity_y = 0.0;
		object->move_left = FALSE;
		object->move_right = FALSE;
		object->jump = FALSE;
		object->jumping = FALSE;
		object->touching_ground = FALSE;
		object->image = NULL;
		object->update = NULL;
		object->draw = NULL;
		return object;
	}
	return NULL;
}

void MineObject_Destroy( Object *object )
{
	if( object->image )
	{
		SDL_FreeSurface(object->image);
	}
	free(object);
}

unsigned int MineObject_GetX( Object *object )
{
	return object->x;
}

unsigned int MineObject_GetY( Object *object )
{
	return object->y;
}

unsigned int MineObject_GetWidth( Object *object )
{
	if( object->image )
	{
		return object->image->w;
	}
	return 32;
}

unsigned int MineObject_GetHeight( Object *object )
{
	if( object->image )
	{
		return object->image->h;
	}
	return 32;
}

void MineObject_SetMoveLeft( Object *object, char state )
{
	object->move_left = state;
}

void MineObject_SetMoveRight( Object *object, char state )
{
	object->move_right = state;
}

void MineObject_Update( Object *object, unsigned int delta_time )
{
	if( object->update )
	{
		object->update(object);
	}
	else
	{
		unsigned int object_width = MineObject_GetWidth(object);
		unsigned int object_height = MineObject_GetHeight(object);
		
		double old_x = object->x;
		double old_y = object->y;
		double new_x = object->x;
		double new_y = object->y;
		
		object->velocity_x = 0.0;
		//object->velocity_y = 0.0;
		
		if( object->move_left )
		{
			/*
			double speed = 2.0 * (delta_time / 10.0);
			double radian_angle = 180.0 * (PI / 180);
			new_x += (speed * cos(radian_angle));
			new_y += (speed * sin(radian_angle));
			*/
			object->velocity_x = -2.0;
		}
		else if( object->move_right )
		{
			/*
			double speed = 2.0 * (delta_time / 10.0);
			double radian_angle = 0.0 * (PI / 180);
			new_x += (speed * cos(radian_angle));
			new_y += (speed * sin(radian_angle));
			*/
			object->velocity_x = 2.0;
		}
		
		if( object->jump )
		{
			//printf("jump\n");
			object->jump = FALSE;
			if( /*object->touching_ground*/ NOT object->jumping )
			{
				/*
				double speed = 6.0 * (delta_time / 10.0);
				double radian_angle = 270.0 * (PI / 180);
				new_x += (speed * cos(radian_angle));
				new_y += (speed * sin(radian_angle));
			
				object->jump = FALSE;
				*/
				object->velocity_y = -8.0;
				object->jumping = TRUE;
				//printf("---------------------------------------\n");
				//printf("jump\n");
				//printf("velocity_y: %f\n", object->velocity_y);
			}
			else
			{
				//printf("not touching ground\n");
				object->velocity_y = 4.0;
			}
		}
		else if( object->jumping )
		{
			//printf("jumping\n");
			if( NOT object->touching_ground )
			{
				//printf("jumping\n");
				double change = (4.0 * (delta_time / 100.0));
				//printf("delta_time: %d\n", delta_time);
				//printf("change: %f\n", change);
				object->velocity_y += change;
				//printf("velocity_y: %f\n", object->velocity_y);
				if( object->velocity_y > 4.0 )
				{
					object->velocity_y = 4.0;
				}
			}
			else
			{
				object->jumping = FALSE;
				object->velocity_y = 4.0;
			}
		}
		else
		{
			object->velocity_y = 4.0;
			//printf("regular gravity\n");
		}
		
		// Gravity
		/*
		double gravity = 4.0 * (delta_time / 10.0);
		double radian_angle = 90 * (PI / 180);
		new_x += (gravity * cos(radian_angle));
		new_y += (gravity * sin(radian_angle));
		*/
		//new_x += 1;
		//new_y += 1;
		
		new_x += (object->velocity_x * (delta_time / 10.0));
		new_y += (object->velocity_y * (delta_time / 10.0));
		
		unsigned int old_left = old_x - (object_width / 2);
		unsigned int old_top = old_y - (object_width / 2);
		unsigned int new_left = new_x - (object_width / 2);
		unsigned int new_top = new_y - (object_height / 2);
		
		if( NOT MineWorld_HaveCollision(object->world, new_left, new_top, object_width, object_height) )
		{
			object->x = new_x;
			object->y = new_y;
			object->touching_ground = FALSE;
		}
		else
		{
			if( NOT MineWorld_HaveCollision(object->world, new_left, old_top, object_width, object_height) )
			{
				object->x = new_x;
				object->touching_ground = TRUE;
			}
			else
			{
				if( NOT MineWorld_HaveCollision(object->world, old_left, new_top, object_width, object_height) )
				{
					object->y = new_y;
					object->touching_ground = FALSE;
				}
				else
				{
					object->touching_ground = TRUE;
				}
			}

		}
		
		//object->x = new_x;
		//object->y = new_y;
	}
}

void MineObject_Draw( Object *object, Camera *camera )
{
	if( object->draw )
	{
		object->draw(object, camera);
	}
	else if( object->image )
	{
		unsigned int x = object->x - (object->image->w / 2);
		unsigned int y = object->y - (object->image->h / 2);
		SDL_Rect dst;
		dst.x = x - MineCamera_Left(camera);
		dst.y = y - MineCamera_Top(camera);
		SDL_BlitSurface(object->image, NULL, MineEngine_VideoSurface, &dst);
	}
	else
	{
		SDL_Rect rect;
		rect.x = (object->x - 16) - MineCamera_Left(camera);
		rect.y = (object->y - 16) - MineCamera_Top(camera);
		rect.w = 32;
		rect.h = 32;
		Uint32 white = SDL_MapRGB(MineEngine_VideoSurface->format, 255, 255, 255);
		SDL_FillRect(MineEngine_VideoSurface, &rect, white);
	}
}

