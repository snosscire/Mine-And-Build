#include "MineInclude.h"
#include "MineEvent.h"
#include "MineList.h"

List *MineEvent_RegisteredCallbacks = NULL;

EventCallback * MineEventCallback_Create()
{
	EventCallback *callback = (EventCallback *)malloc(sizeof(EventCallback));
	if( callback )
	{
		callback->type = 0;
		callback->invoke = NULL;
		callback->data = NULL;
		return callback;
	}
	return NULL;
}

void MineEventCallback_Destroy( EventCallback *callback )
{
	if( callback )
	{
		free(callback);
	}
}

void MineEventCallback_Invoke( EventCallback *callback, SDL_Event *event )
{
	if( callback->type == event->type )
	{
		callback->invoke(event, callback->data);
	}
}

void _MineEvent_DestroyRegisteredCallbacksItem( void *data )
{
	EventCallback *callback = (EventCallback *)data;
	MineEventCallback_Destroy(callback);
}

void MineEvent_Startup()
{
	MineEvent_RegisteredCallbacks = MineList_Create(_MineEvent_DestroyRegisteredCallbacksItem);
}

void MineEvent_Shutdown()
{
	MineList_Destroy(MineEvent_RegisteredCallbacks);
}

void MineEvent_RegisterCallback( Uint8 type, void (*function)(SDL_Event*,void*), void *data )
{
	EventCallback *callback = MineEventCallback_Create();
	if( callback )
	{
		callback->type = type;
		callback->invoke = function;
		callback->data = data;
		MineList_Append(MineEvent_RegisteredCallbacks, callback);
	}
}

ListNode * _MineEvent_FindCallbackByFunction( void (*function)(SDL_Event*,void*) )
{
	FOREACH(MineEvent_RegisteredCallbacks, EventCallback, callback)
		if( callback->invoke == function ) {
			return current_node;
		}
	ENDFOREACH
	return NULL;
}

void MineEvent_UnregisterCallback( void (*function)(SDL_Event*,void*) )
{
	ListNode *node = NULL;
	while( (node = _MineEvent_FindCallbackByFunction(function)) )
	{
		MineList_Remove(MineEvent_RegisteredCallbacks, node);
	}
}

void MineEvent_InvokeCallbacks()
{
	SDL_Event event;
	while( SDL_PollEvent(&event) )
	{
		FOREACH(MineEvent_RegisteredCallbacks, EventCallback, callback)
			MineEventCallback_Invoke(callback, &event);
		ENDFOREACH
	}
}

