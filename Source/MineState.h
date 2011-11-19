#ifndef MINE_STATE_H
#define MINE_STATE_H

typedef struct __mine_state State;

struct __mine_state
{
	char running;
	void *data;
	void (*start)(void*);
	void (*stop)(void*);
	void (*update)(void*);
	void (*draw)(void*);
};

State * MineState_Create();
void MineState_Delete( State *state );
void MineState_Start( State *state );
void MineState_Stop( State *state );
void MineState_Update( State *state );
void MineState_Draw( State *state );

#endif /* MINE_STATE_H */
