#pragma once
#include "Game_SpecialObject.h"

#define ALIENBASE_WIDTH 256
#define ALIENBASE_HEIGHT 212
#define AB_HANDCELL_RADIUS_BASE 16.0f
#define AB_HANDCELL_WAIT_INIT_INTERVAL 250
#define AB_HANDCELL_PART_WAIT_INTERVAL 50
#define AB_LEFTHAND_SHOOT_INTERVAL 2500
#define AB_RIGHTHAND_SHOOT_INTERVAL 2500
#define AB_HAND_SHOOT_OFFSET 400
#define AB_MOUTH_SHOOT_NOHAND_INTERVAL 2000
#define AB_WAIT_FOR_CLOSE_MOUTH 500
#define AB_AIMING_DELAY 200
#define AB_WAIT_INFINITE 9999999

enum AlienBase_Action
{
	AB_ACT_INIT,
	AB_ACT_WAVING,
	AB_ACT_SPINNING,
	AB_ACT_COVERING,
	AB_ACT_AIMING,
	AB_ACT_AIMING_AUTO,
	AB_ACT_STANDBY_FOR_AIMING,
	AB_ACT_MOUTH_SHOOT
};

class Enemy_AlienBase_Body : public Game_SpecialObject
{
	private:

		// body part id
		int _head = -1;
		int _leftHand[5];
		int _rightHand[5];
		int _currentActionIndex = 0;
		bool _start = false;
		bool _init = false;
		bool _leftHand_Die = false;
		bool _rightHand_Die = false;
		DWORD _AimingDelay = 0;

		vector<int> _MoveSet =
		{
			AB_ACT_WAVING, AB_ACT_SPINNING, AB_ACT_COVERING, AB_ACT_MOUTH_SHOOT, AB_ACT_STANDBY_FOR_AIMING,
			AB_ACT_AIMING, AB_ACT_AIMING_AUTO, AB_ACT_AIMING_AUTO,
			AB_ACT_AIMING_AUTO, AB_ACT_AIMING_AUTO, AB_ACT_AIMING_AUTO
		};

		void UpdateState() override;
		void UpdateBehavior(DWORD dt, vector<PGAMEOBJECT>* coObjects = NULL) override;
		void Cleaning() override
		{
			Game_SpecialObject::Cleaning();
			_MoveSet.clear();
		}

		// Behavior

		DWORD _LeftHand_WaitToShoot = AB_LEFTHAND_SHOOT_INTERVAL * 3;
		DWORD _RightHand_WaitToShoot = AB_RIGHTHAND_SHOOT_INTERVAL * 3 + AB_HAND_SHOOT_OFFSET;
		DWORD _Mouth_WaitToShoot = AB_WAIT_INFINITE;
		DWORD _WaitForCloseMouth = 0;

		void Act_Init();
		void Act_Spinning();
		void Act_Waving();
		void Act_Aiming();
		void Act_Aiming_Auto();
		void Act_StandbyForAiming();
		void Act_Covering();
		void Act_LeftHand_Shooting();
		void Act_RightHand_Shooting();
		void Act_Mouth_Shooting();
		bool CheckParts_IsIdle();
	public:
		Enemy_AlienBase_Body(float x, float y, int z);
		~Enemy_AlienBase_Body() {
			Game_SpecialObject::~Game_SpecialObject();
			Cleaning();
		};

		void Update(DWORD dt, vector<PGAMEOBJECT>* coObjects) override;
		int CharID() override;
		// When no collision has been detected (triggered by CCollision::Process)
		void OnNoCollision(DWORD dt) override { Game_MovableObject::OnNoCollision(dt); }
		// When collision with an object has been detected (triggered by CCollision::Process)
		void OnCollisionWith(PCOLLISIONEVENT e) override { Game_MovableObject::OnCollisionWith(e); }
		int IsCollidable() override { return 0; }
		void StartBoss() { _start = true; }
		void Kill_LeftHand();
		void Kill_RightHand();

		void Execute_DieAction() override {}

		void GetSpriteOffset(int state, float& x, float& y) override
		{
			x = 0;
			y = -4;
		}
};