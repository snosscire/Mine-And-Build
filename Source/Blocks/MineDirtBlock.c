#include "MineDirtBlock.h"
#include "../MineInclude.h"
#include "../MineEngine.h"

Block * MineDirtBlock_Create()
{
	Block *super = MineBlock_Create();
	if( super )
	{
		super->image = MineEngine_LoadImage("dirt.png");
		super->draw = _MineBlock_DefaultDraw;
		return super;
	}
	return NULL;
}

