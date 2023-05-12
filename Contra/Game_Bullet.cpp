#include "Game_Bullet.h"

#define CONVERT_DEGREE_TO_RAD 0.0174533f

void Game_Bullet::SetAngle(float degree)
{
	// Convert to rad
	float rad = CONVERT_DEGREE_TO_RAD * degree;

	_vx = cos(rad) * _moveSpd;
	_vy = sin(rad) * _moveSpd;
}

void Game_Bullet::SetTargetPos(float x, float y)
{
	float centerX, centerY;
	GetCenterPoint(centerX, centerY);
	float sideX = x - centerX;
	float sideY = y - centerY;
	float hypotenuse = sqrt(sideX*sideX + sideY*sideY);

	_vx = _moveSpd * sideX / hypotenuse;
	_vy = _moveSpd * sideY / hypotenuse;
}

void Game_Bullet::SetVector(float vx, float vy)
{
	float hypotenuse = sqrt(vx * vx + vy * vy);

	_vx = _moveSpd * vx / hypotenuse;
	_vy = _moveSpd * vy / hypotenuse;
}

void Game_Bullet::Render()
{
	RenderHitbox();
	CAnimations* animations = CAnimations::GetInstance();
	float x, y;
	GetCenterPoint(x, y);
	animations->Get(getAni()+10)->Render(x, y);
}

void Game_Bullet::Update(DWORD dt)
{
	_x += _vx * dt;
	_y += _vy * dt;
}