#include "MineInclude.h"
#include "MineCamera.h"

#include <stdlib.h>

Camera * MineCamera_Create()
{
	Camera *camera = malloc(sizeof(Camera));
	if( camera )
	{
		camera->destroy = NULL;
		camera->update = NULL;
		camera->left = NULL;
		camera->right = NULL;
		camera->top = NULL;
		camera->bottom = NULL;
		camera->data = NULL;
		return camera;
	}
	return NULL;
}

void MineCamera_Destroy( Camera *camera )
{
	if( camera->destroy )
	{
		camera->destroy(camera);
	}
	free(camera);
}

void MineCamera_Update( Camera *camera )
{
	if( camera->update )
	{
		camera->update(camera);
	}
}

int MineCamera_Left( Camera *camera )
{
	if( camera->left )
	{
		return camera->left(camera);
	}
	return 0;
}

int MineCamera_Right( Camera *camera )
{
	if( camera->right )
	{
		return camera->right(camera);
	}
	return 0;
}

int MineCamera_Top( Camera *camera )
{
	if( camera->top )
	{
		return camera->top(camera);
	}
	return 0;
}

int MineCamera_Bottom( Camera *camera )
{
	if( camera->bottom )
	{
		return camera->bottom(camera);
	}
	return 0;
}

