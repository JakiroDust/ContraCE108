#pragma once
using namespace std;

class Game_ObjectBase
{
	protected:
		/// POS

		// horizonal position, base on current map
		int _x;
		// vertical position, base on current map
		int _y;
		// Value use to determine with object will be draw first
		// Object with lowest value will be drawn first.
		int _z;
		
		/// PROPERTIES
		
		int _width;
		int _height;
		
		/// FRAME CONTROL
		
		// First frame in charset (when frameCurrent at 0).
		// Use when there're multiple motions in one sprite.
		int _startFrame = 0;
		// max value of frameCurrent
		int _frameMax = 0;
		// Use to control which frame will be showed.
		int _frameCurrent = 0;
		// Interval for changing frame.
		int _frameInterval = 0;
		// Timer value for changing frame.
		// When reaching Interval value, frame will be changed.
		int _frameTimer = 0;

		// LOGIC
		
		// Game_Sprite *_sprite;
		// Rectangle realHitbox;
		// Rectangle visualHitbox;
		//

		/// PROTECTED FUNCTIONS
		
		// update frame control parameter
		virtual void updateFrame();

	public:
		Game_ObjectBase(int x = 0, int y = 0, int z = 0, int width = 0, int height = 0);
		
		// GET SET FUNCTIONS

		int x();
		int y();
		int z();

		// Teleport this object to destination.
		// Ignore collision detection phase.
		virtual void teleport(int x, int y);
		
		virtual bool isEntity() = 0;
		virtual bool isObject() = 0;
		
		/// UPDATE SPRITE
		
		// update sprite control parameter and sprite reference if needed
		virtual void updateSprite();
		
		/// FRAME CONTROL

		// draw this object's sprite
		virtual void draw();
};

