#pragma once

using namespace std;
#include <string>
#include "Contra_ANI_ID.h"
#include <unordered_map>
#include "debug.h"

#define ACT_IDLE_RIGHT 0
#define ACT_IDLE_LEFT 1
#define ACT_LOOK_UP_RIGHT 2
#define ACT_LOOK_UP_LEFT 3
#define ACT_LYING_RIGHT 4
#define ACT_LYING_LEFT 5
#define ACT_WALK_RIGHT 6
#define ACT_WALK_LEFT 7
#define ACT_WALK_RIGHT_LOOK_UP 8
#define ACT_WALK_LEFT_LOOK_UP 9
#define ACT_WALK_RIGHT_LOOK_DOWN 10
#define ACT_WALK_LEFT_LOOK_DOWN 11
#define ACT_SWIM_RIGHT 12
#define ACT_SWIM_LEFT 13
#define ACT_SWIM_RIGHT_LOOK_UP 14
#define ACT_SWIM_LEFT_LOOK_UP 15
#define ACT_DIVE 16
#define ACT_JUMP_RIGHT 17
#define ACT_JUMP_LEFT 18
#define ACT_FALL_RIGHT 19
#define ACT_FALL_LEFT 20

#define CHAR_CONTRA 1

int Get_CharANI_ID(int character, int behavior);