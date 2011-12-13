#include "MineInclude.h"
#include "MinePlayerCamera.h"
#include "MineEngine.h"

typedef struct _mine_player_camera
{
	Object *object;
	//int left;
	//int top;
	int world_width;
	int world_height;
} PlayerCamera;

void _MinePlayerCamera_Destroy( Camera *camera )
{
	PlayerCamera *self = camera->data;
	free(self);
}

int _MinePlayerCamera_Left( Camera *camera )
{
	PlayerCamera *self = camera->data;
	int left = MineObject_GetX(self->object) - (MineEngine_ScreenWidth() / 2);
	
	if( left < 0 )
	{
		left = 0;
	}
	else if( left > (self->world_width - MineEngine_ScreenWidth() ) )
	{
		left = self->world_width - MineEngine_ScreenWidth();
	}
	
	return left;
}

int _MinePlayerCamera_Right( Camera *camera )
{
	return _MinePlayerCamera_Left(camera) + MineEngine_ScreenWidth();
}

int _MinePlayerCamera_Top( Camera *camera )
{
	PlayerCamera *self = camera->data;
	int top = MineObject_GetY(self->object) - (MineEngine_ScreenHeight() / 2);
	
	if( top < 0 )
	{
		top = 0;
	}
	else if( top > (self->world_height - MineEngine_ScreenHeight() ) )
	{
		top = self->world_height - MineEngine_ScreenHeight();
	}
	
	return top;
}

int _MinePlayerCamera_Bottom( Camera *camera )
{
	return _MinePlayerCamera_Top(camera) + MineEngine_ScreenHeight();
}

Camera * MinePlayerCamera_Create( unsigned int world_width, unsigned int world_height, Object *object )
{
	Camera *camera = MineCamera_Create();
	if( camera )
	{
		PlayerCamera *data = malloc(sizeof(PlayerCamera));
		//data->left = 0;
		//data->top = 0;
		data->world_width = world_width;
		data->world_height = world_height;
		data->object = object;
		
		camera->data = data;
		
		camera->destroy = _MinePlayerCamera_Destroy;
		camera->left = _MinePlayerCamera_Left;
		camera->right = _MinePlayerCamera_Right;
		camera->top = _MinePlayerCamera_Top;
		camera->bottom = _MinePlayerCamera_Bottom;
		
		return camera;
	}
	return NULL;
}

