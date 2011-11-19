#ifndef MINE_EVENT_H
#define MINE_EVENT_H

#include <SDL/SDL.h>

typedef struct __mine_event_callback EventCallback;

struct __mine_event_callback
{
	Uint8 type;
	void (*invoke)(SDL_Event*,void*);
	void *data;
};

EventCallback * MineEventCallback_Create();
void MineEventCallback_Delete( EventCallback *callback );
void MineEventCallback_Invoke( EventCallback *callback, SDL_Event *event );

void MineEvent_Startup();
void MineEvent_Shutdown();
void MineEvent_RegisterCallback( Uint8 type, void (*callback)(SDL_Event*,void*), void *data );
void MineEvent_UnregisterCallback( void (*callback)(SDL_Event*,void*) );
void MineEvent_InvokeCallbacks();

#endif /* MINE_EVENT_H */
