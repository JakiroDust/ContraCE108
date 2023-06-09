#pragma once
#include "Game_SpecialObject.h"
#include "Equip_EnemyGun_AlienBase.h"

#define AB_HANDCELL_WIDTH 12
#define AB_HANDCELL_HEIGHT 12
#define AB_HANDCELL_MAIN_WIDTH 15
#define AB_HANDCELL_MAIN_HEIGHT 15
#define AB_HANDCELL_RAD_SPEED 4.0f

#define ABC_ACT_MOVE_TO_REAR 0
#define ABC_ACT_MOVE_CLOCKWISE 1
#define ABC_ACT_MOVE_COUNTERCLOCKWISE 2
#define ABC_ACT_MOVE_CLOCK_AUTO 3
#define ABC_ACT_WAIT 4

struct ABCell_Action
{
	int typeID;
	float value = 0;
	ABCell_Action(int typeID, float value)
	{
		this->typeID = typeID;
		this->value = fmod(value, 360);
	}
};

class Enemy_AlienBase_HandCell : public Game_SpecialObject
{
	protected:
		vector<ABCell_Action> _ABC_ActionQueue;
		float _radius = 0;
		float _currentDegree = 0;
		float _centerX = 0;
		float _centerY = 0;
		DWORD _WaitForInit = 0;
		void UpdateState() override;
		void UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects = NULL) override;
		void Cleaning() override
		{
			Game_SpecialObject::Cleaning();
			_ABC_ActionQueue.clear();
		}
	public:
		Enemy_AlienBase_HandCell(float x, float y, int z, float radius, DWORD wait) : Game_SpecialObject(x, y, z, AB_HANDCELL_WIDTH, AB_HANDCELL_HEIGHT)
		{
			_moveSpd = 0.15f;
			_centerX = x;
			_centerY = y;
			_radius = radius;
			_immortal = true;
			_moveSpd = 0.15f;
			_haveStandby = false;
			_HardBody = true;
			_BodyDamage = false;
			_faceLeft = true;
			_gravity = false;
			_ghost = false;
			_WaitForInit = wait;
		}
		~Enemy_AlienBase_HandCell() {
			Game_SpecialObject::~Game_SpecialObject();
			Cleaning();
		};

		void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) override;
		void Render() override;
		int CharID() override;
		// When no collision has been detected (triggered by CCollision::Process)
		void OnNoCollision(DWORD dt) override { Game_SpecialObject::OnNoCollision(dt); }
		// When collision with an object has been detected (triggered by CCollision::Process)
		void OnCollisionWith(PCOLLISIONEVENT e) override { Game_SpecialObject::OnCollisionWith(e); }
		
		void ABC_AddAction(int typeID, int value) { _ABC_ActionQueue.push_back(ABCell_Action(typeID, value)); }
		bool ABC_IsIdle() { return _ABC_ActionQueue.size() == 0; }
		void ABC_Set_Center(float x, float y)
		{
			SetCenterPoint(x, y);
			_centerX = _x;
			_centerY = _y;
		}
		int getSFXhitedID() override
		{
			return 40;
		}
		void Execute_BeforeDelete() override;
		void Execute_DieAction() override {}
};

class Enemy_AlienBase_HandCell_Main : public Enemy_AlienBase_HandCell
{
	private:
		bool _isLeftHand;
		int _bodyID;
		void Cleaning() override
		{
			Enemy_AlienBase_HandCell::Cleaning();
		}
	public:
		Enemy_AlienBase_HandCell_Main(float x, float y, int z, float radius, DWORD wait, int bodyID, bool isLeftHand) : Enemy_AlienBase_HandCell(x, y, z, radius, wait)
		{
			_weapon = new Equip_EnemyGun_AlienBase();
			_width = AB_HANDCELL_MAIN_WIDTH;
			_height = AB_HANDCELL_MAIN_HEIGHT;
			_hp = 30;
			_immortal = false;
			_isLeftHand = isLeftHand;
			_bodyID = bodyID;
		}

		~Enemy_AlienBase_HandCell_Main()
		{
			Cleaning();
		};

		int CharID() override;

		void Execute_DieAction() override;
};