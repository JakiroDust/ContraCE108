#include "spawnBulletHelper.h"
#include "State_Contra_Base.h"
#include "Contra_GET_ANI.h"
/*

	bool getContraCor(float& x, float& y,int&state,int&DIR)
	{
		switch (state)
		{
		case STATE_IDLE:
		case STATE_WALK:
		case STATE_JUMP:
		case STATE_SWIM:
		case STATE_FALL:
		case STATE_DIVE:
		case STATE_ACTIVE:
			switch (DIR)
			{
			case DIR_TOP_LEFT:
			case DIR_TOP:
			case DIR_TOP_RIGHT:
			case DIR_LEFT:
			case DIR_RIGHT:
			case DIR_BOTTOM_LEFT:
			case DIR_BOTTOM:
			case DIR_BOTTOM_RIGHT:
			default:
				break;
			}
			break;
		case STATE_LIE:
			break;
		default:

			return false;
			break;
		}
		return true;                       
	}
*/
namespace BULLETHELPER
{
	bool getTurretCor(float& x, float& y, int& DIR)
	{
		const float x_dis = 13;
		const float y_dis = 13;
		const float xxx_dis = 7, xxy_dis = 6;
		const float xyx_dis = 6, xyy_dis = 7;
		const float xy_dis = 7;
		bool applyNegativeX = false;
		bool applyNegativeY = false;

		switch (DIR)
		{
		case DIR_2_OCLOCK:x = 12; y = 8; break;
		case DIR_4_OCLOCK:x = 12; y = -8; break;
		case DIR_8_OCLOCK: x = -12; y = -8; break;
		case DIR_10_OCLOCK: x = -12; y = 8; break;

		case DIR_1_OCLOCK: x = 6; y = 12; break;
		case DIR_5_OCLOCK: x = 6; y = -12; break;
		case DIR_7_OCLOCK: x = -6; y = -12; break;
		case DIR_11_OCLOCK:x = -6; y = 12; break;

		case DIR_3_OCLOCK: x = 12; y = 0; break;
		case DIR_6_OCLOCK: y = -12; x = 0; break;
		case DIR_9_OCLOCK: x = -12; y = 0; break;
		case DIR_12_OCLOCK: x = 0; y = y_dis; break;
		default:
			x = 0;
			y = 0;
			return false;
		}
		return true;
	}

	bool getContraCor(float& x, float& y, int& state, int& DIR)
	{
		switch (state)
		{
		case ACT_IDLE_LEFT:
			x = -2;
			y = 4;
			break;
		case ACT_IDLE_RIGHT:
			x = -2;
			y = 4;
			break;
		case ACT_LOOK_UP_LEFT:
			x = -6;
			y = 10;
			break;
		case ACT_LOOK_UP_RIGHT:
			x = 6;
			y = 10;
			break;
		case ACT_JUMP_RIGHT:
			x = 6;
			y = 0;
			break;
		case ACT_JUMP_LEFT:
			x = 6;
			y = 0;
			break;
		case ACT_SWIM_LEFT_LOOK_UP:
			x = -10;
			y = 10;
			break;
		case ACT_SWIM_RIGHT_LOOK_UP:
			x = 10;
			y = 10;
			break; 
		case ACT_WALK_LEFT:
			x = -3;
			y = 3;
			break;
		case ACT_WALK_RIGHT:
			x = 3;
			y = 3;
			break;
		case ACT_WALK_LEFT_LOOK_UP:
			x = -5;
			y = 2;
			break;
		case ACT_WALK_RIGHT_LOOK_UP:
			x = 4;
			y = 2;
			break;
		case ACT_WALK_LEFT_LOOK_DOWN:
			x = -8;
			y = -4;
			break;
		case ACT_WALK_RIGHT_LOOK_DOWN:
			x = 8;
			y = -4;
			break;
		case ACT_SWIM_LOOK_UP_STAND_LEFT:
			x = -6;
			y = 10;
			break;
		case ACT_SWIM_LOOK_UP_STAND_RIGHT:
			x = 6;
			y = 10;
			break;
		/*case STATE_ACTIVE:
			switch (DIR)
			{
			case DIR_TOP_LEFT:      x = -1; y = 1;
			case DIR_TOP_RIGHT:     x *= 7; y *= 7; break;

			case DIR_BOTTOM:        y = -1;
			case DIR_TOP:           y *= 10; break;

			case DIR_LEFT:          x = -1;
			case DIR_RIGHT:         x *= 12; y = 5; break;

			case DIR_BOTTOM_LEFT:   x = -1;
			case DIR_BOTTOM_RIGHT:  x *= 7; y *= 7; break;
			default:
				x = 0; y = 0; return false;
			}break;
		case STATE_LIE:
		{
			switch (DIR)
			{
			case DIR_LEFT:          x = -1;
			case DIR_RIGHT:         x *= 10; break;
			}
		}*/
		break;
		default:
			x = 0;
			y = 0;
			return false;
			break;
		}
		return true;
	}
	bool getSneakyCor(float& x, float& y, int& state, int& DIR) {
		switch (state)
		{
		case ACT_LOOK_DOWN_LEFT:
			x = -20;
			break;
		default: x = 0; y = 0; return false; break;
		}
		return true;
	}
	bool getSniperCor(float& x, float& y, int& state, int& DIR) {
		switch (state)
		{
		case ACT_LOOK_UP_LEFT:
			x = -14; y = 28;
			break;
		case ACT_WALK_LEFT_LOOK_UP:
			x = -14; y = 28;
			break;
		case ACT_WALK_LEFT:
			x = -14; y = 8; break;
			//RIGHT
		case ACT_LOOK_UP_RIGHT:
			x = 14; y = 28;
			break;
		case ACT_WALK_RIGHT_LOOK_UP:
			x = 14; y = 28;
			break;
		case ACT_WALK_RIGHT:
			x = 14; y = 8;
			break;
		default: x = 0; y = 0; return false; break;
		}
		return true;
	}
	void getSpawnCor(float& _x, float& _y, int CHAR_ID, int state, int& DIR)
	{
		float x = 1,
			y = 1;

		switch (CHAR_ID)
		{
		case CHAR_CONTRA:getContraCor(x, y, state, DIR); break;
		case INFARY:
		case RED_GUNNER:
		case SNEAKY_SNIPER:
			getSneakyCor(x, y, state, DIR); break;
		case SNIPER: getSniperCor(x, y, state, DIR); break;
		case TURRET_BASE:
		case CANNON:
		case TURRET: getTurretCor(x, y, DIR); break;

		default:getContraCor(x, y, state, DIR);
		}
		_x += x;
		_y += y;
	}
};