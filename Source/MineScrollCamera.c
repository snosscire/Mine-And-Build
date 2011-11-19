#include "MineInclude.h"
#include "MineScrollCamera.h"
#include "MineEngine.h"
#include "MineEvent.h"

typedef struct _mine_scroll_camera
{
	char holding_button;
	int left;
	int top;
	int world_width;
	int world_height;
} ScrollCamera;

void _MineScrollCamera_OnMouseButtonDown( SDL_Event *event, void *data )
{
	ScrollCamera *self = data;
	self->holding_button = TRUE;
}

void _MineScrollCamera_OnMouseButtonUp( SDL_Event *event, void *data )
{
	ScrollCamera *self = data;
	self->holding_button = FALSE;
}

void _MineScrollCamera_OnMouseMotion( SDL_Event *event, void *data )
{
	ScrollCamera *self = data;
	if( self->holding_button )
	{
		self->left -= event->motion.xrel;
		
		if( self->left < 0 )
		{
			self->left = 0;
		}
		else if( self->left > (self->world_width - MineEngine_ScreenWidth()) )
		{
			self->left = self->world_width - MineEngine_ScreenWidth();
			
			if( self->left < 0 )
			{
				self->left = 0;
			}
		}
		
		self->top -= event->motion.yrel;
		
		if( self->top < 0 )
		{
			self->top = 0;
		}
		else if( self->top > (self->world_height - MineEngine_ScreenHeight()) )
		{
			self->top = self->world_height - MineEngine_ScreenHeight();
			
			if( self->top < 0 )
			{
				self->top = 0;
			}
		}
	}
}

void _MineScrollCamera_Destroy( Camera *camera )
{
	ScrollCamera *self = camera->data;
	free(self);
	MineEvent_UnregisterCallback(_MineScrollCamera_OnMouseButtonDown);
	MineEvent_UnregisterCallback(_MineScrollCamera_OnMouseButtonUp);
	MineEvent_UnregisterCallback(_MineScrollCamera_OnMouseMotion);
}

int _MineScrollCamera_Left( Camera *camera )
{
	ScrollCamera *self = camera->data;
	return self->left;	
}

int _MineScrollCamera_Right( Camera *camera )
{
	ScrollCamera *self = camera->data;
	return self->left + MineEngine_ScreenWidth();
}

int _MineScrollCamera_Top( Camera *camera )
{
	ScrollCamera *self = camera->data;
	return self->top;
}

int _MineScrollCamera_Bottom( Camera *camera )
{
	ScrollCamera *self = camera->data;
	return self->top + MineEngine_ScreenHeight();
}

Camera * MineScrollCamera_Create( unsigned int world_width, unsigned int world_height )
{
	Camera *camera = MineCamera_Create();
	if( camera )
	{
		ScrollCamera *data = malloc(sizeof(ScrollCamera));
		data->left = 0;
		data->top = 0;
		data->world_width = world_width;
		data->world_height = world_height;
		data->holding_button = FALSE;
		
		camera->data = data;
		
		camera->destroy = _MineScrollCamera_Destroy;
		camera->left = _MineScrollCamera_Left;
		camera->right = _MineScrollCamera_Right;
		camera->top = _MineScrollCamera_Top;
		camera->bottom = _MineScrollCamera_Bottom;
		
		MineEvent_RegisterCallback(SDL_MOUSEBUTTONDOWN, _MineScrollCamera_OnMouseButtonDown, data);
		MineEvent_RegisterCallback(SDL_MOUSEBUTTONUP, _MineScrollCamera_OnMouseButtonUp, data);
		MineEvent_RegisterCallback(SDL_MOUSEMOTION, _MineScrollCamera_OnMouseMotion, data);
		
		return camera;
	}
	return NULL;
}
