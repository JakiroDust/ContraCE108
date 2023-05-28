#include "Game_SweeperBlock.h"
#include "Game_Enemy.h"

bool Game_SweeperBlock::BlockingCondition(DWORD dt, PCOLLISIONEVENT e)
{
	if (dynamic_cast<Game_Enemy*>(e->src_obj))
	{
		if (!e->src_obj->NeedRender())
			e->src_obj->DeleteThis();
		return false;
	}
	return true;
}