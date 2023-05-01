#pragma once


#include <string>
#include "Contra_ANI_ID.h"
#include "debug.h"
#include "Enemies_ID.h"
using namespace std;
#define ACT_IDLE_RIGHT 0
#define ACT_IDLE_LEFT 1
#define ACT_LOOK_UP_RIGHT 2
#define ACT_LOOK_UP_LEFT 3
#define ACT_LOOK_DOWN_RIGHT 4
#define ACT_LOOK_DOWN_LEFT 5
#define ACT_LYING_RIGHT 6
#define ACT_LYING_LEFT 7
#define ACT_WALK_RIGHT 8
#define ACT_SHOOT_WALK_RIGHT 81
#define ACT_WALK_LEFT 9
#define ACT_SHOOT_WALK_LEFT 91
#define ACT_WALK_RIGHT_LOOK_UP 10
#define ACT_WALK_LEFT_LOOK_UP 11
#define ACT_WALK_RIGHT_LOOK_DOWN 12
#define ACT_WALK_LEFT_LOOK_DOWN 13
#define ACT_SWIM_RIGHT 14
#define ACT_SWIM_LEFT 15
#define ACT_SWIM_RIGHT_LOOK_UP 16
#define ACT_SWIM_LEFT_LOOK_UP 17
#define ACT_DIVE 18
#define ACT_JUMP_RIGHT 19
#define ACT_JUMP_LEFT 20
#define ACT_FALL_RIGHT 21
#define ACT_FALL_LEFT 22
#define ACT_DIE_RIGHT 23
#define ACT_DIE_LEFT 24

#define CHAR_CONTRA 10
#define CHAR_CONTRA_BASE 12

int Get_CharANI_ID(int character, int behavior);