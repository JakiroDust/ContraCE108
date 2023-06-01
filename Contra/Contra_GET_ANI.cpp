#include "Contra_GET_ANI.h"

int Get_CharANI_ID(int character, int behavior)
{
	unordered_map<int, int> arr;

	switch (character)
	{
	case CHAR_CONTRA:
	{
		arr[ACT_IDLE_LEFT] = CONTRA_ANI_IDLE_LEFT;
		arr[ACT_IDLE_RIGHT] = CONTRA_ANI_IDLE_RIGHT;
		arr[ACT_WALK_LEFT] = CONTRA_ANI_WALK_LEFT;
		arr[ACT_SHOOT_WALK_LEFT] = CONTRA_ANI_WALK_SHOOTING_LEFT;
		arr[ACT_WALK_LEFT_LOOK_UP] = CONTRA_ANI_WALK_UP_LEFT;
		arr[ACT_WALK_LEFT_LOOK_DOWN] = CONTRA_ANI_WALK_DOWN_LEFT;
		arr[ACT_WALK_RIGHT] = CONTRA_ANI_WALK_RIGHT;
		arr[ACT_SHOOT_WALK_RIGHT] = CONTRA_ANI_WALK_SHOOTING_RIGHT;
		arr[ACT_WALK_RIGHT_LOOK_UP] = CONTRA_ANI_WALK_UP_RIGHT;
		arr[ACT_WALK_RIGHT_LOOK_DOWN] = CONTRA_ANI_WALK_DOWN_RIGHT;
		arr[ACT_LYING_RIGHT] = CONTRA_ANI_LIE_RIGHT;
		arr[ACT_LYING_LEFT] = CONTRA_ANI_LIE_LEFT;
		arr[ACT_LOOK_UP_RIGHT] = CONTRA_ANI_LOOK_UP_RIGHT;
		arr[ACT_LOOK_UP_LEFT] = CONTRA_ANI_LOOK_UP_LEFT;
		arr[ACT_JUMP_LEFT] = CONTRA_ANI_JUMP_LEFT;
		arr[ACT_JUMP_RIGHT] = CONTRA_ANI_JUMP_RIGHT;
		arr[ACT_SWIM_LOOK_UP_STAND_LEFT] = CONTRA_ANI_SWIM_UP_STAND_LEFT;
		arr[ACT_SWIM_LOOK_UP_STAND_RIGHT] = CONTRA_ANI_SWIM_UP_STAND_RIGHT;
		arr[ACT_SWIM_LEFT_LOOK_UP] = CONTRA_ANI_SWIM_LEFT_UP;
		arr[ACT_SWIM_RIGHT_LOOK_UP] = CONTRA_ANI_SWIM_RIGHT_UP;
		arr[ACT_SWIM_LEFT] = CONTRA_ANI_SWIM_LEFT;
		arr[ACT_SWIM_RIGHT] = CONTRA_ANI_SWIM_RIGHT;
		arr[ACT_SWIM_SHOOT_LEFT] = CONTRA_ANI_SWIM_SHOOT_LEFT;
		arr[ACT_SWIM_SHOOT_RIGHT] = CONTRA_ANI_SWIM_SHOOT_RIGHT;
		arr[ACT_DIVE] = CONTRA_ANI_DIV;
		arr[ACT_FALL_LEFT] = CONTRA_ANI_FALL_LEFT;
		arr[ACT_FALL_RIGHT] = CONTRA_ANI_FALL_RIGHT;
		arr[ACT_DIE_LEFT] = CONTRA_ANI_DIE_LEFT;
		arr[ACT_DIE_RIGHT] = CONTRA_ANI_DIE_RIGHT;
		arr[ACT_DIE_JUMPING_LEFT] = CONTRA_ANI_DIE_JUMPING_LEFT;
		arr[ACT_DIE_JUMPING_RIGHT] = CONTRA_ANI_DIE_JUMPING_RIGHT;
		break;
	}

	case RED_GUNNER:
	{
		arr[ACT_IDLE_LEFT] = INFARY_ANI_WALK_LEFT;
		arr[ACT_IDLE_RIGHT] = INFARY_ANI_WALK_RIGHT;
		arr[ACT_WALK_LEFT] = INFARY_ANI_WALK_LEFT;
		arr[ACT_WALK_RIGHT] = INFARY_ANI_WALK_RIGHT;
		arr[ACT_JUMP_LEFT] = INFARY_ANI_JUMP_LEFT;
		arr[ACT_JUMP_RIGHT] = INFARY_ANI_JUMP_RIGHT;
		arr[ACT_SWIM_LEFT] = INFARY_ANI_DIE_LEFT;
		arr[ACT_SWIM_RIGHT] = INFARY_ANI_DIE_RIGHT;
		arr[ACT_FALL_LEFT] = INFARY_ANI_JUMP_LEFT;
		arr[ACT_FALL_RIGHT] = INFARY_ANI_JUMP_RIGHT;
		arr[ACT_LYING_RIGHT] = INFARY_ANI_AIM_RIGHT;
		arr[ACT_LYING_LEFT] = INFARY_ANI_AIM_LEFT;
		arr[ACT_DIE_LEFT] = INFARY_ANI_DIE_LEFT;
		arr[ACT_DIE_RIGHT] = INFARY_ANI_DIE_RIGHT;
		break;
	}

	case SNIPER:
	{
		arr[ACT_LOOK_UP_LEFT] = SNIPER_ANI_AIM_UP_LEFT;
		arr[ACT_LOOK_UP_RIGHT] = SNIPER_ANI_AIM_UP_RIGHT;
		arr[ACT_LOOK_DOWN_LEFT] = SNIPER_ANI_AIM_DOWN_LEFT;
		arr[ACT_LOOK_DOWN_RIGHT] = SNIPER_ANI_AIM_DOWN_RIGHT;
		arr[ACT_WALK_LEFT] = SNIPER_ANI_AIM_LEFT;
		arr[ACT_WALK_RIGHT] = SNIPER_ANI_AIM_RIGHT;
		arr[ACT_WALK_LEFT_LOOK_UP] = SNIPER_ANI_AIM_UP_LEFT;
		arr[ACT_WALK_RIGHT_LOOK_UP] = SNIPER_ANI_AIM_UP_RIGHT;
		arr[ACT_WALK_LEFT_LOOK_DOWN] = SNIPER_ANI_AIM_DOWN_LEFT;
		arr[ACT_WALK_RIGHT_LOOK_DOWN] = SNIPER_ANI_AIM_DOWN_RIGHT;
		arr[ACT_DIE_LEFT] = SNIPER_ANI_AIM_LEFT;
		arr[ACT_DIE_RIGHT] = SNIPER_ANI_AIM_RIGHT;
		break;
	}

	case SNEAKY_SNIPER:
	{
		arr[ACT_LOOK_DOWN_LEFT] = ANI_BUSH_SNIPER_SHOOT;
		arr[ACT_WALK_LEFT] = ANI_BUSH_SNIPER_WIND_UP;
		arr[ACT_IDLE_LEFT] = ANI_BUSH_SNIPER_HIDE;
		arr[ACT_DIE_LEFT] = SNIPER_ANI_AIM_LEFT;
		break;
	}

	case TURRET:
	{
		arr[ACT_HIDE_LEFT] = ANI_TURRET_360_IDLE;
		arr[ACT_HIDE_RIGHT] = ANI_TURRET_360_IDLE;
		arr[ACT_EMERGE_LEFT] = ANI_TURRET_360_WIND_UP;
		arr[ACT_EMERGE_RIGHT] = ANI_TURRET_360_WIND_UP;
		arr[ACT_ANGLE_1_OCLOCK] = ANI_TURRET_360_1;
		arr[ACT_ANGLE_2_OCLOCK] = ANI_TURRET_360_2;
		arr[ACT_ANGLE_3_OCLOCK] = ANI_TURRET_360_3;
		arr[ACT_ANGLE_4_OCLOCK] = ANI_TURRET_360_4;
		arr[ACT_ANGLE_5_OCLOCK] = ANI_TURRET_360_5;
		arr[ACT_ANGLE_6_OCLOCK] = ANI_TURRET_360_6;
		arr[ACT_ANGLE_7_OCLOCK] = ANI_TURRET_360_7;
		arr[ACT_ANGLE_8_OCLOCK] = ANI_TURRET_360_8;
		arr[ACT_ANGLE_9_OCLOCK] = ANI_TURRET_360_9;
		arr[ACT_ANGLE_10_OCLOCK] = ANI_TURRET_360_10;
		arr[ACT_ANGLE_11_OCLOCK] = ANI_TURRET_360_11;
		arr[ACT_ANGLE_12_OCLOCK] = ANI_TURRET_360_12;
		arr[ACT_DIE_LEFT] = ANI_TURRET_360_DIE;
		arr[ACT_DIE_RIGHT] = ANI_TURRET_360_DIE;
		break;
	}

	case CANNON:
	{
		arr[ACT_HIDE_LEFT] = ANI_EMPTY;
		arr[ACT_HIDE_RIGHT] = ANI_EMPTY;
		arr[ACT_EMERGE_LEFT] = ANI_CANNON_WIND_UP_LEFT;
		arr[ACT_EMERGE_RIGHT] = ANI_CANNON_WIND_UP_LEFT;
		arr[ACT_ANGLE_1_OCLOCK] = ANI_TURRET_360_1;
		arr[ACT_ANGLE_2_OCLOCK] = ANI_TURRET_360_2;
		arr[ACT_ANGLE_3_OCLOCK] = ANI_TURRET_360_3;
		arr[ACT_ANGLE_9_OCLOCK] = ANI_CANNON_9;
		arr[ACT_ANGLE_10_OCLOCK] = ANI_CANNON_10;
		arr[ACT_ANGLE_11_OCLOCK] = ANI_CANNON_11;
		arr[ACT_DIE_LEFT] = ANI_CANNON_9;
		arr[ACT_DIE_RIGHT] = ANI_CANNON_9;
		break;
	}

	case FALLING_STONE:
	{
		arr[ACT_STANDBY_LEFT] = ANI_FALLING_ROCK;
		arr[ACT_STANDBY_RIGHT] = ANI_FALLING_ROCK;
		arr[ACT_ACTIVE_LEFT] = ANI_FALLING_ROCK;
		arr[ACT_ACTIVE_RIGHT] = ANI_FALLING_ROCK;
		break;
	}

	default:
		DebugOut(L"[ERROR] Character ID is undefined.\n");
		return -1;
	}

	return arr[behavior];
}