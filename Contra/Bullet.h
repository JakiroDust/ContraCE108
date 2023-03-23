/*
#pragma once
#include "GameObject.h"

#define BULLET_SPEED 0.1f


#define BULLET_BBOX_WIDTH 5
#define BULLET_BBOX_HEIGHT 5

#define BULLET_TIMEOUT 5000

#define BULLET_STATE_WALKING 100
#define BULLET_STATE_DIE 200

#define ID_ANI_BULLET_WALKING 12000

class CBullet : public CGameObject
{
protected:
	//float ax;
	//float ay;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CBullet(float x, float y);
	virtual void SetState(int state);
};
*/