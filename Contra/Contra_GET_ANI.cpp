#include "Contra_GET_ANI.h"

int Get_CharANI_ID(int character, int behavior)
{
	unordered_map<int, int> arr;

	switch (character)
	{
	case CHAR_CONTRA:
	{
		arr[ACT_IDLE_LEFT] = ANI_IDLE_LEFT;
		arr[ACT_IDLE_RIGHT] = ANI_IDLE_RIGHT;
		arr[ACT_WALK_LEFT] = ANI_WALK_LEFT;
		arr[ACT_WALK_RIGHT] = ANI_WALK_RIGHT;
		arr[ACT_JUMP_LEFT] = ANI_JUMP_LEFT;
		arr[ACT_JUMP_RIGHT] = ANI_JUMP_RIGHT;
		arr[ACT_SWIM_LEFT] = ANI_SWIM_LEFT;
		arr[ACT_SWIM_RIGHT] = ANI_SWIM_RIGHT;
		arr[ACT_FALL_LEFT] = ANI_FALL_LEFT;
		arr[ACT_FALL_RIGHT] = ANI_FALL_RIGHT;
		arr[ACT_DIE_LEFT] = ANI_FALL_LEFT;
		arr[ACT_DIE_RIGHT] = ANI_FALL_RIGHT;
		break;
	}

	case RED_GUNNER:
	{
		arr[ACT_IDLE_LEFT] = ANI_IDLE_LEFT;
		arr[ACT_IDLE_RIGHT] = ANI_IDLE_RIGHT;
		arr[ACT_WALK_LEFT] = ANI_WALK_LEFT;
		arr[ACT_WALK_RIGHT] = ANI_WALK_RIGHT;
		arr[ACT_JUMP_LEFT] = ANI_JUMP_LEFT;
		arr[ACT_JUMP_RIGHT] = ANI_JUMP_RIGHT;
		arr[ACT_SWIM_LEFT] = ANI_SWIM_LEFT;
		arr[ACT_SWIM_RIGHT] = ANI_SWIM_RIGHT;
		arr[ACT_FALL_LEFT] = ANI_FALL_LEFT;
		arr[ACT_FALL_RIGHT] = ANI_FALL_RIGHT;
		arr[ACT_DIE_LEFT] = ANI_FALL_LEFT;
		arr[ACT_DIE_RIGHT] = ANI_FALL_RIGHT;
		break;
	}


	default:
		DebugOut(L"[ERROR] Character ID is undefined.\n");
		return -1;
	}

	return arr[behavior];
}