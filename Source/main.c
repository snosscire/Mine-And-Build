#include "MineGame.h"
#include "States/MineTestState.h"

int main( int argc, const char **argv ) {
	MineGame_SetState(MineTestState_Create());
	MineGame_Run();
	return 0;
}

