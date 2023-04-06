#pragma once

using namespace std;
#include "Game_ObjectBase.h"
#include "Game_Collision.h"

class State_Base
{
	protected:
		Game_ObjectBase* _srcObj = NULL;
		
		// If this param is not NULL, source object
		// will change next state base on this param.
		int _nextState = -1;
	public:
		State_Base(Game_ObjectBase* src) { _srcObj = src; }
		Game_ObjectBase* srcObj() { return _srcObj; }
		int NextState() { return _nextState; }
		virtual int StateId() { return -1; }

		// When no collision has been detected (triggered by CCollision::Process)
		virtual void OnNoCollision(DWORD dt) {}
		// When collision with an object has been detected (triggered by CCollision::Process)
		virtual void OnCollisionWith(PCOLLISIONEVENT e) {}

		virtual void Render() {}
		virtual void Update(DWORD dt) {}

};

