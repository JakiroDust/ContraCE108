#pragma once
class CGameObjectBase
{
protected:

	float x;
	float y;
	bool isDeleted;
public:
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	virtual void Delete() { isDeleted = true; }
	bool IsDeleted() { return isDeleted; }
	CGameObjectBase();
	CGameObjectBase(float x, float y) :CGameObjectBase() { this->x = x; this->y = y; }
	~CGameObjectBase();
};

