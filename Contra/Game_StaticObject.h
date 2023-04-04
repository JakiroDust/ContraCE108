#pragma once
#include "Game_ObjectBase.h"
#include <string>

#define TYPE_TERRAIN 0
#define TYPE_LAYER 1

class Game_StaticObject : public Game_ObjectBase
{
protected:
public:
	Game_StaticObject(float x, float y, int z, int width, int height) : Game_ObjectBase(x, y, z, width, height) {};
	
	// Inherited
	int baseType() { return TYPE_STATIC; }
	virtual void Render() { Game_ObjectBase::Render(); }
	virtual void SetNeedRender(bool b) { _needRender = b; }
	virtual bool NeedRender() { return _needRender; }

	virtual int objectType() = 0;

	/// Update
	virtual void Update(DWORD dt) {};
};

