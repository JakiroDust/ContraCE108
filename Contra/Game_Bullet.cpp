#include "Game_Bullet.h"

#define CONVERT_DEGREE_TO_RAD 0.0174532925

void Game_Bullet::SetAngle(float degree)
{
	// Convert to rad
	float rad = CONVERT_DEGREE_TO_RAD * degree;

	_vx = cos(rad) * _moveSpd;
	_vy = -1.0f * sin(rad) * _moveSpd;
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

void Game_Bullet::Update(DWORD dt)
{
	_x += _vx * dt;
	_y += _vy * dt;
}