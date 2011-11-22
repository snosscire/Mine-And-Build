#include "MineInclude.h"
#include "MineGame.h"
#include "MineEngine.h"
#include "MineEvent.h"
#include "MineFont.h"

#include <SDL/SDL.h>

char MineGame_IsRunning = FALSE;
State *MineGame_CurrentState = NULL;

void _MineGame_OnQuit( SDL_Event *event, void *data )
{
	MineGame_Quit();
}

void MineGame_Run()
{
	unsigned int frame_times[20] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	unsigned int frame_count = 0;
	unsigned int frame_index;
	unsigned int frame_temp_count = 0;
	float frames_per_second = 0.0;
	unsigned int i;
	
	unsigned int next_fps_print = 0;
	
	Uint32 current_time = 0;
	Uint32 last_time = 0;
	Uint32 delta_time = 0;
	
	MineEngine_Startup(640, 480, FALSE);
	
	MineEvent_RegisterCallback(SDL_QUIT, _MineGame_OnQuit, NULL);
	
	if( MineGame_CurrentState )
	{
		MineState_Start(MineGame_CurrentState);
	}
	
	current_time = SDL_GetTicks();
	last_time = current_time;
	delta_time = 0;
	
	MineGame_IsRunning = TRUE;
	while( MineGame_IsRunning )
	{
		current_time = SDL_GetTicks();
		delta_time = current_time - last_time;
		last_time = current_time;
		
		if( delta_time > 0 )
		{
			frame_index = frame_count % 20;
			frame_times[frame_index] = delta_time;
			frame_count++;

			if( frame_count < 20 )
			{
				frame_temp_count = frame_count;
			}
			else
			{
				frame_temp_count = 20;
			}
		
			frames_per_second = 0;
			
			
			if( current_time > next_fps_print )
			{
				//printf("---------------------------\n");
			}
			
			for( i = 0; i < frame_temp_count; i++ )
			{
				if( current_time > next_fps_print )
				{
					//printf("Frame time: %d\n", frame_times[i]);
				}
				frames_per_second += frame_times[i];
			}
		
			frames_per_second /= frame_temp_count;
			if( current_time > next_fps_print )
			{
				//printf("Avarage frame time: %f\n", frames_per_second);
			}
			if( frames_per_second > 0 )
			{
				frames_per_second = 1000 / frames_per_second;
			}
			else
			{
				frames_per_second = 0;
			}
		}
		
		if( current_time > next_fps_print )
		{
			printf("FPS: %f\n", frames_per_second);
			next_fps_print = current_time + 1000;
		}
				
		MineEvent_InvokeCallbacks();
		if( MineGame_CurrentState )
		{
			MineState_Update(MineGame_CurrentState);
		}
		MineEngine_ClearScreen();
		if( MineGame_CurrentState )
		{
			MineState_Draw(MineGame_CurrentState);
		}
		MineEngine_UpdateScreen();
	}
	
	if( MineGame_CurrentState )
	{
		MineState_Stop(MineGame_CurrentState);
		MineState_Delete(MineGame_CurrentState);
		MineGame_CurrentState = NULL;
	}
	
	MineEngine_Shutdown();
}

void MineGame_Quit()
{
	MineGame_IsRunning = FALSE;
}

void MineGame_SetState( State *state )
{
	if( MineGame_CurrentState )
	{
		MineState_Stop(MineGame_CurrentState);
		MineState_Delete(MineGame_CurrentState);
		MineGame_CurrentState = NULL;
	}
	MineGame_CurrentState = state;
	if( MineGame_IsRunning AND MineGame_CurrentState )
	{
		MineState_Start(MineGame_CurrentState);
	}
}

