#pragma once
#include "Game_ObjectBase.h"
#include <string>

class Game_Entity : public Game_ObjectBase
{
	protected:
		/// PROPERTIES

		// test value for x when enter simulation phase.
		// If World state is safe, it will replace original value.
		int _testX = 0;
		// test value for y when enter simulation phase.
		// If World state is safe, it will replace original value.
		int _testY = 0;
		// Moving speed of entity
		int _moveSpd = 1;
		// When value above 0, entity will float.
		int _jumpForce = 0;
		
		
		/// state
		
		bool _faceLeft = false;
		bool _swim = false;
		bool _immortal = false;
		bool _ghost = false;
		bool _onAir = false;
		bool _die = false;
		string _state = "idle";
		
		/// function

	public:
		/// STATIC

		// World variable to determine
		// how fast jumpForce will be modified.
		static const int jumpVector = 2;

		/// inherited

		bool isEntity();
		bool isObject();

		/// GET & SET

		// alternative horizonal position.
		// It will be determine based on the point in the middle of sprite footer.
		int entityX();
		// alternative vertical position.
		// It will be determine based on the point in the middle of sprite footer.
		int entityY();
		// Convert entityX to real x.
		int realX(int x);
		// Convert entityY to real y.
		int realY(int y);

		/// state

		virtual bool isDie();

		/// update

		virtual void updatePreCollisionTest();
		virtual void updateAction();
		virtual void updateTestMove();
		virtual void updateState();
		virtual void updateSprite();

		/// action

		// Override teleport function.
		// Use entity x,y pos instead of real x,y pos.
		virtual void teleport(int x, int y);
		virtual void moveLeft();
		virtual void moveRight();
		virtual void jump();
		virtual void forceDie();
};

