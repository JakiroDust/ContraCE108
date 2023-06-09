#include "spawnBulletHelper.h"
#include "State_Contra_Base.h"
#include "Contra_GET_ANI.h"

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
			{
				switch (DIR)
				{
				case DIR_LEFT:
					x = -6;
					y = 0;
					break;
				case DIR_RIGHT:
					x = 6;
					y = 0;
					break;
				case DIR_TOP:
					x = 0;
					y = 6;
					break;
				case DIR_BOTTOM:
					x = 0;
					y = -6;
					break;
				case DIR_TOP_LEFT:
					x = -6;
					y = 6;
					break;
				case DIR_TOP_RIGHT:
					x = 6;
					y = 6;
					break;
				case DIR_BOTTOM_LEFT:
					x = -6;
					y = -6;
					break;
				case DIR_BOTTOM_RIGHT:
					x = 6;
					y = -6;
					break;
				default:
					x = 0;
					y = 0;
					break;
				}		
				break;
			}
		case ACT_JUMP_LEFT:
			{
				switch (DIR)
				{
				case DIR_LEFT:
					x = -6;
					y = 0;
					break;
				case DIR_RIGHT:
					x = 6;
					y = 0;
					break;
				case DIR_TOP:
					x = 0;
					y = 6;
					break;
				case DIR_BOTTOM:
					x = 0;
					y = -6;
					break;
				case DIR_TOP_LEFT:
					x = -6;
					y = 6;
					break;
				case DIR_TOP_RIGHT:
					x = 6;
					y = 6;
					break;
				case DIR_BOTTOM_LEFT:
					x = -6;
					y = -6;
					break;
				case DIR_BOTTOM_RIGHT:
					x = 6;
					y = -6;
					break;
				default:
					x = 0;
					y = 0;
					break;
				}
				break;
			}
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
			x = -14;
			y = -3;
			break;
		case ACT_WALK_RIGHT_LOOK_DOWN:
			x = 14;
			y = -3;
			break;
		case ACT_SWIM_LOOK_UP_STAND_LEFT:
			x = -6;
			y = 10;
			break;
		case ACT_SWIM_LOOK_UP_STAND_RIGHT:
			x = 6;
			y = 10;
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
			x = -17;
			y = -4;
			break;
		default: x = 0; y = 0; return false; break;
		}
		return true;
	}
	bool getRedGunnerCor(float& x, float& y, int& state, int& DIR) {
		switch (state)
		{
		case ACT_LYING_LEFT:
			y = 10; x = -12;
			break;
		case ACT_LYING_RIGHT:
			y = 10; x = 12;
			break;
		default: x = 0; y = 0; return false; break;
		}
		return true;
	}
	bool getCannonCor(float& x, float& y, int& state, int& DIR) {
		switch (state)
		{
		case ACT_ANGLE_10_OCLOCK:
			y = 9; x = -17;
			break;
		case ACT_ANGLE_11_OCLOCK:
			y = 17; x = -9;
			break;
		case ACT_ANGLE_9_OCLOCK:
			x = -17;
			break;
		default: x = 0; y = 0; return false; break;
		}
		return true;
	}
	bool getScubaCor(float& x, float& y, int& state, int& DIR) {
		switch (state)
		{
		case ACT_WALK_RIGHT:
			y = 18;
			break;
		
		default: x = 0; y = 0; return false; break;
		}
		return true;
	}
	bool getCannonBaseCor(float& x, float& y, int& state, int& DIR) {
		switch (state)
		{
		case ACT_WALK_LEFT:
			x = -8;
			break;

		default: x = 0; y = 0; return false; break;
		}
		return true;
	}
	bool getSniperCor(float& x, float& y, int& state, int& DIR) {
		switch (state)
		{
		case ACT_LOOK_UP_LEFT:
			x = -12; y = 24;
			break;
		case ACT_WALK_LEFT_LOOK_UP:
			x = -12; y = 24;
			break;
		case ACT_WALK_LEFT:
			x = -12; y = 11; break;
		case ACT_WALK_LEFT_LOOK_DOWN:
			x = -13; y = -4; break;
		case ACT_LOOK_DOWN_LEFT:
			x = -13; y = -4; break;
			//RIGHT
		case ACT_LOOK_UP_RIGHT:
			x = 14; y = 28;
			break;
		case ACT_WALK_RIGHT_LOOK_UP:
			x = 10; y = 23;
			break;
		case ACT_WALK_RIGHT:
			x = 13; y = 10;
			break;
		case ACT_WALK_RIGHT_LOOK_DOWN:
			x = 13; y = -4; break;
		case ACT_LOOK_DOWN_RIGHT:
			x = 13; y = -4; break;
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
		case RED_GUNNER: getRedGunnerCor(x, y, state, DIR); break;
		case SNEAKY_SNIPER: getSneakyCor(x, y, state, DIR); break;
		case SNIPER: getSniperCor(x, y, state, DIR); break;
		case BASE_CANNON_LEFT: getCannonBaseCor(x, y, state, DIR); break;
		case BASE_CANNON_RIGHT: getCannonBaseCor(x, y, state, DIR); break;
		case CANNON:  getCannonCor(x, y, state, DIR); break;
		case TURRET: getTurretCor(x, y, DIR); break;
		case SCUBA_DIVER: getScubaCor(x, y,state, DIR); break;

		default:getContraCor(x, y, state, DIR);
		}
		_x += x;
		_y += y;
	}
};