/*#include "Bullet.h"

CBullet::CBullet(float x, float y) :CGameObject(x, y)
{
	//this->ax = 0;
	//this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	SetState(BULLET_STATE_WALKING);
}

void CBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BULLET_BBOX_WIDTH / 2;
	top = y - BULLET_BBOX_HEIGHT / 2;
	right = left + BULLET_BBOX_WIDTH;
	bottom = top + BULLET_BBOX_HEIGHT;
}

void CBullet::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CBullet::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CBullet*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == BULLET_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CBullet::Render()
{
	int aniId = ID_ANI_GOOMBA_WALKING;
	if (state == GOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CBullet::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		live_time = GetTickCount64();
		break;
	}
}*/
